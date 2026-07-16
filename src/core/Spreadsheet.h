#pragma once
#include <string>
#include <unordered_map>
#include <memory>

#include "cell/CellAddress.h"
#include "cell/CellValue.h"

using SpreadsheetEntries = std::unordered_map < Cell::CellAddress, std::unique_ptr<Cell::CellValue>, Cell::CellAddressHasher>;

namespace Spreadsheet {

	class Spreadsheet {

	public:
		Spreadsheet(std::string name);

		std::string getName() const;
		void setName(std::string newName);

		const SpreadsheetEntries& getEntries() const;
		void setValue(Cell::CellAddress cellAddress, std::unique_ptr<Cell::CellValue> cellValue);
		void clearValue(Cell::CellAddress cellAddress);

	private:
		std::string m_name;
		SpreadsheetEntries m_entries;
	};

}