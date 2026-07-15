// SpreadsheetEngine.cpp : Defines the entry point for the application.
//
#include <memory>

#include "SpreadsheetEngine.h"
#include "src/core/Spreadsheet.h"
#include "src/core/cell/CellAddress.h"
#include "src/core/cell/types/NumericValue.h"
#include "src/core/cell/types/StringValue.h"

using namespace std;

void mockSpreadsheet();

int main()
{
	mockSpreadsheet();

	return 0;
}

void mockSpreadsheet() {

	// Create the spreadsheet
	Spreadsheet::Spreadsheet spreadsheet("New spreadsheet!");
	cout << spreadsheet.getName() << endl;

	// define 2 cell addresses
	Cell::CellAddress addr("A", 4);
	cout << addr.toString() << endl;

	Cell::CellAddress addr2("B", 3);
	cout << addr2.toString() << endl;

	// define 2 cell values
	Cell::NumericValue numVal(1234.12345);

	Cell::StringValue stringVal("hello world!");

	// add entries, and check they persist
	spreadsheet.addEntry(addr, std::make_unique<Cell::NumericValue>(numVal));
	spreadsheet.addEntry(addr2, std::make_unique<Cell::StringValue>(stringVal));

	const SpreadsheetEntries& entries = spreadsheet.getEntries();

	cout << entries.at(addr)->toString() << endl;
	cout << entries.at(addr2)->toString() << endl;

	// try to clear the first address and check the data is cleared out
	spreadsheet.clearEntry(addr);

	if (!entries.contains(addr)) {
		cout << addr.toString() + " cleared successfully" << endl;
	}
}