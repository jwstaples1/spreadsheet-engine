#pragma once

#include "../tokens/TokenType.h"

#include <unordered_map>
#include <vector>

namespace Parser {

	using RulesMap = std::unordered_map<TokenType, const std::vector<std::vector<TokenType>>>;

	using enum TokenType;

	inline const RulesMap RULES = {

		{CellAddress, {
			{String, Numeric}
		}},
		{Range, {
			{CellAddress, Colon, CellAddress}
		}},
		{ExternalFormula, {
			{String, LeftParenthesis, Arguments, RightParenthesis}
		}}

	};
	

}