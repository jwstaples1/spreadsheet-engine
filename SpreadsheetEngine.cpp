// SpreadsheetEngine.cpp : Defines the entry point for the application.
//

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

	Spreadsheet::Spreadsheet spreadsheet("New spreadsheet!");
	cout << spreadsheet.getName() << endl;

	Cell::CellAddress addr("A", 4);
	cout << addr.toString() << endl;

	Cell::NumericValue numVal(1234.12345);
	cout << numVal.toString() << endl;

	Cell::StringValue stringVal("hello world!");
	cout << stringVal.toString() << endl;
}