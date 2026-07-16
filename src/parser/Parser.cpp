#include "Parser.h"

#include "../core/cell/types/NumericValue.h"

namespace Parser {

	Parser::Parser() {};

	Cell::ConstantValue& Parser::evaluate(const Spreadsheet::Formula& formula) {

		Cell::NumericValue val(0);
		return val;

	}

}