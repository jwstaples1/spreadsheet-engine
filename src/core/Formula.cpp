#include "Formula.h"

namespace Spreadsheet {

	Formula::Formula(std::string rawFormula) : m_rawFormula(rawFormula) {};

	std::string Formula::toString() {
		return m_rawFormula;
	}

}