#include "Parser.h"

#include <iostream>
#include <format>
#include <optional>
#include <stack>

#include "../core/cell/types/NumericValue.h"
#include "rules/Rules.h"
#include "rules/RuleTree.h"
#include "rules/tree/RuleTreeNode.h"

// AI Generated print code
	void printNode(const Parser::RuleTreeNode& node,
		const std::string& prefix,
		bool isLast)
	{
		std::cout << prefix;

		if (!prefix.empty())
			std::cout << (isLast ? "└── " : "├── ");

		std::cout << (int) node.getValue();

		if (node.getTerminalRule().has_value())
		{
			std::cout << "  => "
				<<  (int) *node.getTerminalRule();
		}

		std::cout << '\n';

		const auto& children = node.getChildren();

		std::size_t index = 0;
		for (const auto& [type, child] : children)
		{
			++index;

			printNode(
				*child,
				prefix + (prefix.empty()
					? ""
					: (isLast ? "    " : "│   ")),
				index == children.size());
		}
	}

namespace Parser {

	Parser::Parser() {
		RuleTree& tree = RuleTree::getInstance();
		std::cout << "num root node children: " << tree.getRoot().getChildren().size() << std::endl;

		printNode(tree.getRoot(), "", true);
		std::cout << std::endl << std::endl;
	};

	Cell::ConstantValue& Parser::evaluate(const Spreadsheet::Formula& formula) {

		// parse the formula and extract all of the relevant basic tokens
		std::vector<Token> tokens = _parse(formula);
		
		std::cout << formula.toString() << std::endl;
		for (int i = 0; i < tokens.size(); i++) {
			std::cout << (int)tokens[i].getType() << std::endl;
		}

		std::cout << std::format("Num tokens: {}", tokens.size()) << std::endl;

		if (tokens.size() == 0) {
			std::cout << std::endl;
			Cell::NumericValue val(0);
			return val;
		}

		return _evaluate(tokens);
	}

	Cell::ConstantValue& Parser::_evaluate(std::vector<Token> tokens) {

		// read through the tokens that we evaluated and simplify some of the obvious things, like string, num -> address
		std::vector<Token> workingTokens = tokens;

		RuleTree& tree = RuleTree::getInstance();
		const RuleTreeNode& root = tree.getRoot();

		/*
			Iterate over the tokens and check if any match the rule tree
				- if they do, merge them in place and trigger rerun
				- if they dont, ignore and continue
		*/

		const RuleTreeNode* current;
		bool rerun;
		int startingIndex;

		do {
			// make sure the starting state is always reset in each rerun
			rerun = false;
			current = &root;
			startingIndex = -1;

			for (int i = 0; i < workingTokens.size(); i++) {
				Token currentTok = workingTokens[i];

				// if we hit an empty type, just skip it
				if (currentTok.getType() == TokenType::Empty) continue;

				// if the type of the current token matches some token in the rule tree
				if (current->getChildren().contains(currentTok.getType())) {

					// if the current is still the root, i.e. this is the first token in this rule we're checking
					if (current == &root) {
						startingIndex = i;

					}

					// set current to the next node in the tree and check if thats the terminal
					current = current->getChildren().at(currentTok.getType()).get();

					// if it is the terminal, we've reached the end of this complex token.
					// we can merge from startingIndex -> i, set the flag to rerun since we've made a change, and mark the extra spaces as empty
					if (current->getTerminalRule().has_value()) {

						// fill the in between space with null tokens
						for (int j = startingIndex + 1; j <= i; j++) {
							workingTokens[j] = Token::getNull();
						}

						workingTokens[startingIndex] = Token(current->getTerminalRule().value(), " Complex ! ");

						// reset everything back to the starting state, except we want to rerun
						startingIndex = -1;
						rerun = true;
						current = &root;
					}
				}
				else {
					if (current != &root) {
						i = startingIndex + 1;
						current = &root;
					}
				}
			}
		} while (rerun);
		

		// remove all of the empty tokens that were populated
		std::erase_if(workingTokens, [](Token tok) { return tok.getType() == TokenType::Empty; });

		// LOG POST CLEANUP
		for (int i = 0; i < workingTokens.size(); i++) {
			Token token = workingTokens[i];
			if (token.getType() == TokenType::Numeric) {
				std::cout << std::format("Token: {} | Type {}\n", std::to_string(std::get<double>(token.getValue())), (int)token.getType());
			}
			else {
				std::cout << std::format("Token: {} | Type {} \n", std::get<std::string>(token.getValue()), (int)token.getType());
			}
		}

		std::cout << std::format("Num tokens: {}", workingTokens.size()) << std::endl;
		std::cout << std::endl;


		Cell::NumericValue val(0);
		return val;
	}

	std::vector<Token> Parser::_parse(const Spreadsheet::Formula& formula) {
		
		// extract the actual formula string to parse
		std::string formulaString = formula.toString();

		// if the string is empty or the first character isnt an equals, return an empty vector
		if (formulaString.size() > 0 && formulaString.at(0) != '=') {
			return {};
		}

		std::vector<Token> parsedTokens;
		parsedTokens.reserve(formulaString.size() / 2);

		// we can add the '=' token since we already read it above
		parsedTokens.emplace_back(TokenType::Equals, "=");

		// store the last token we looked at if it's either numeric or string
		struct IncompleteToken {
			TokenType tokenType;
			int startIndex;
		};

		std::optional<IncompleteToken> partialToken;

		// takes a given incomplete token and completes it by getting the proper value and parsing it correctly into a token
		auto completePartialToken = [&formulaString, &partialToken, &parsedTokens](IncompleteToken incompleteToken, int endIndex) -> void {
			std::string stringifiedTokenVal = formulaString.substr(incompleteToken.startIndex, endIndex - incompleteToken.startIndex);

			TokenValue tokenValue = incompleteToken.tokenType == TokenType::Numeric
				? TokenValue(std::stod(stringifiedTokenVal))
				: TokenValue(stringifiedTokenVal);

			parsedTokens.emplace_back(incompleteToken.tokenType, tokenValue);
		};
		
		// loop through the string to parse the tokens
		for (int i = 1; i < formulaString.size(); i++) {
			char formulaChar = formulaString[i];
			
			// skip any whitespace
			if (formulaChar == ' ') continue;

			bool isNumeric = formulaChar >= '0' && formulaChar <= '9' || formulaChar == '.';

			TokenType type = isNumeric ? TokenType::Numeric : Token::getTokenTypeFromChar(formulaChar);
			bool isDynamicTokenType = Token::isDynamicTokenType(type);
			
			// for non-dynamic tokens, we can just mark them as parsed since we know what we see is what we get. 
			// We also need to end a partial token and push it if we have one
			if (!isDynamicTokenType) {
				if (partialToken.has_value()) {
					completePartialToken(partialToken.value(), i);
					partialToken.reset();
				}
				parsedTokens.emplace_back(type, std::string(1, formulaChar));
			}
			/*
				for dynamic tokens, we need to check against the token we've been reading in to see if its the same type
				- if it is, we just continue until its not
				- if its not, we end the partial token and push it
			*/
			else {
				// if we dont already have a partial token, create one starting at this index
				if (!partialToken.has_value()) {
					partialToken = { .tokenType = type, .startIndex = i };
				}
				// if we do have a partial token, check if the types match. if they dont, end the token and create a new one, continue
				else if(partialToken.value().tokenType != type) {
					completePartialToken(partialToken.value(), i);
					partialToken = { .tokenType = type, .startIndex = i };
				}

			}
		}

		// if we have an active partial token at the end of the formula, close it and push it to the back
		if (partialToken.has_value()) {
			completePartialToken(partialToken.value(), formulaString.size());
		}


		return parsedTokens;

	}

}