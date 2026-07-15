#include "Spreadsheet.h"

namespace Spreadsheet {

	Spreadsheet::Spreadsheet(std::string name) : m_name(name) {};

	std::string Spreadsheet::getName() {
		return m_name;
	}

	void Spreadsheet::setName(std::string name) {
		m_name = name;
	}

}