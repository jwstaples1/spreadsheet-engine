#pragma once
#include <string>
#include <functional>

using namespace std;

namespace Cell {

	class CellAddress {

	public:
		CellAddress(string col, int row);

		string getColumn();
		int getRow();

		// Returns a cell address in a displayable format, i.e. "A4"
		string toString() const;

		bool operator==(const CellAddress&) const = default;

	private:
		string m_col;
		int m_row;

	};

	// Defines how we hash a cell address - it can just be a hash of the stringified version
	struct CellAddressHasher {
		std::size_t operator()(const Cell::CellAddress & address) const noexcept {
			return std::hash<string>{}(address.toString());
		}
	};
	

}