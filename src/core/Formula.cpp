#include "Formula.h"

namespace Spreadsheet {

	Formula::Formula(std::string rawFormula) : m_rawFormula(rawFormula) {};

	std::string Formula::toString() const {
		return m_rawFormula;
	}

}