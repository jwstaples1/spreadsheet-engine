#pragma once
#include <string>

namespace Spreadsheet {

	class Formula {

	public:
		Formula(std::string rawFormula);

		std::string toString();

	private:
		std::string m_rawFormula;

	};

}