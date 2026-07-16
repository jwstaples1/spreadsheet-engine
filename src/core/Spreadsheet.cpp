#include "Spreadsheet.h"

using namespace Cell;

namespace Spreadsheet {

	Spreadsheet::Spreadsheet(std::string name) : m_name(name) {};

	std::string Spreadsheet::getName() const {
		return m_name;
	}

	void Spreadsheet::setName(std::string name) {
		m_name = name;
	}

	const SpreadsheetEntries& Spreadsheet::getEntries() const {
		return m_entries;
	}

	void Spreadsheet::setValue(CellAddress cellAddress, std::unique_ptr<CellValue> cellValue) {
		m_entries.insert_or_assign(cellAddress, std::move(cellValue));
	}

	void Spreadsheet::clearValue(CellAddress cellAddress) {
		m_entries.erase(cellAddress);
	}

}