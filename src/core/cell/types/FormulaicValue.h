#pragma once
#include "../CellValue.h"
#include "../../Formula.h"

namespace Cell {

	class FormulaicValue : public CellValue {

	public:
		FormulaicValue(Spreadsheet::Formula value);

		Spreadsheet::Formula getValue();
		std::string toString();

	private:
		Spreadsheet::Formula m_value;

	};

}