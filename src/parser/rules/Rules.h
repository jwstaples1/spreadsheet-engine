#pragma once

#include "../tokens/TokenType.h"
#include "../tokens/Token.h"

#include <unordered_map>
#include <vector>
#include <functional>

namespace Parser {

	using TransformationFunctionArgs = const std::vector<TokenValue>&;

	extern Token fromStringNumericToAddress(TransformationFunctionArgs values);
	extern Token fromAddressesToRange(TransformationFunctionArgs values);
	extern Token fromNameAndArgsToFormula(TransformationFunctionArgs values);
	extern Token fromRangeToArguments(TransformationFunctionArgs values);

	using RuleTransformFunction = std::function<Token(TransformationFunctionArgs)>;

	using RulesMap = std::unordered_map<TokenType, const std::vector<std::pair<std::vector<TokenType>, RuleTransformFunction>>>;

	using enum TokenType;

	inline const RulesMap RULES = {

		{CellAddress, {
			{ std::vector<TokenType>{String, Numeric}, fromStringNumericToAddress }
		}},
		{Range, {
			{ std::vector<TokenType>{CellAddress, Colon, CellAddress}, fromAddressesToRange }
		}},
		{ExternalFormula, {
			{ std::vector<TokenType>{String, LeftParenthesis, Arguments, RightParenthesis}, fromNameAndArgsToFormula }
		}},
		{Arguments, {
			{ std::vector<TokenType>{ Range }, fromRangeToArguments }
		}}

	};
}