#include "NumericValue.h"
#include <format>

namespace Cell {

	NumericValue::NumericValue(float val) : m_value(val) {}

	float NumericValue::getValue() {
		return m_value;
	}

	// eventually apply options here too
	std::string NumericValue::toString() {
		return std::format("{}", m_value);
	}

}