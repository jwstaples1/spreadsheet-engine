#pragma once

#include <vector>

#include "../core/Formula.h"
#include "../core/cell/ConstantValue.h"

#include "tokens/Token.h"


namespace Parser {

	class Parser {

	public:		
		Parser();

		Cell::ConstantValue& evaluate(const Spreadsheet::Formula& formula);

	private:
		std::vector<Token> parse(const Spreadsheet::Formula& formula);
	};

}