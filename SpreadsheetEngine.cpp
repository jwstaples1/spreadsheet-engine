// SpreadsheetEngine.cpp : Defines the entry point for the application.
//

#include "SpreadsheetEngine.h"
#include "src/core/cell/CellAddress.h"
#include "src/core/cell/types/NumericValue.h"
#include "src/core/cell/types/StringValue.h"

using namespace std;

void mockSpreadsheet();

int main()
{
	cout << "Hello CMake." << endl;

	mockSpreadsheet();

	return 0;
}

void mockSpreadsheet() {

	Cell::CellAddress addr("A", 4);
	cout << addr.toString() << endl;

	Cell::NumericValue numVal(1234.1234);
	cout << numVal.toString() << endl;

	Cell::StringValue stringVal("hello world!");
	cout << stringVal.toString() << endl;
}