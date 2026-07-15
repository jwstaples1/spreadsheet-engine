#pragma once
#include <string>

using namespace std;

namespace Cell {

	class CellAddress {

	public:
		CellAddress(string col, int row);

		string getColumn();
		int getRow();

		// Returns a cell address in a displayable format, i.e. "A4"
		string toString();

	private:
		string m_col;
		int m_row;

	};

}