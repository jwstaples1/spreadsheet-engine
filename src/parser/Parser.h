#pragma once
#include "../core/Formula.h"
#include "../core/cell/ConstantValue.h"

namespace Parser {

	class Parser {

	public:		
		Parser();

		Cell::ConstantValue& evaluate(const Spreadsheet::Formula& formula);

	};

}