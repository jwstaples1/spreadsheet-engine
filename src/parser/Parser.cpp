#include "Parser.h"

#include <iostream>
#include <format>
#include <optional>
#include <stack>

#include "../core/cell/types/NumericValue.h"


namespace Parser {

	Parser::Parser() {};

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
		std::vector<Token> postCleanupTokens;
		postCleanupTokens.reserve(tokens.size());

		for (int i = 0; i < tokens.size(); i++) {
			Token currentTok = tokens[i];
			
			bool isAddressToken =
				currentTok.getType() == TokenType::String &&
				i < tokens.size() - 1 &&
				tokens[i + 1].getType() == TokenType::Numeric;

			if (isAddressToken) {
				// create the address value and emplace a new address token, make sure to skip the next token
				std::string col = std::get<std::string>(currentTok.getValue());
				double row = std::get<double>(tokens[i + 1].getValue());

				if (row - floor(row) > 0) {
					throw std::exception();
				} 

				postCleanupTokens.emplace_back(TokenType::CellAddress, col + std::to_string((int)row));
				i += 1;
			}
			else {
				postCleanupTokens.push_back(currentTok);
			}

		}

		// LOG POST CLEANUP
		for (int i = 0; i < postCleanupTokens.size(); i++) {
			Token token = postCleanupTokens[i];
			if (token.getType() == TokenType::Numeric) {
				std::cout << std::format("Token: {} | Type {}\n", std::to_string(std::get<double>(token.getValue())), (int)token.getType());
			}
			else {
				std::cout << std::format("Token: {} | Type {} \n", std::get<std::string>(token.getValue()), (int)token.getType());
			}
		}

		std::cout << std::format("Num tokens: {}", postCleanupTokens.size()) << std::endl;
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