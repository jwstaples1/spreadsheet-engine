#include "FormulaicValue.h"

namespace Cell {

	FormulaicValue::FormulaicValue(Spreadsheet::Formula formula) : m_value(formula) {};

	Spreadsheet::Formula FormulaicValue::getValue() {
		return m_value;
	}

	std::string FormulaicValue::toString() {
		return m_value.toString();
	}

}