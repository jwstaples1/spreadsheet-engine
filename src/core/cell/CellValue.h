#pragma once
#include <string>

namespace Cell {

	class CellValue {

	public:
		virtual ~CellValue() = default;

		// virtual evaluate();
		// virtual applyOptions();

		// returns a basic string of the cell value
		virtual std::string toString() = 0;
	};

}