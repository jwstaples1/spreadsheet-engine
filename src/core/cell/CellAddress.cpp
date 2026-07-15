#include "CellAddress.h"
#include <format>

namespace Cell {

	CellAddress::CellAddress(string column, int row) : m_col(column), m_row(row) {};

	string CellAddress::getColumn() {
		return m_col;
	}

	int CellAddress::getRow() {
		return m_row;
	}

	string CellAddress::toString() {
		string address = std::format("{}{}", m_col, m_row);

		return address;
	}

}