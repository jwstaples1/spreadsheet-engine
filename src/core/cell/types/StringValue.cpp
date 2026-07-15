#include "StringValue.h"
#include <format>

namespace Cell {

	StringValue::StringValue(std::string value) : m_value(value) {};

	std::string StringValue::getValue() {
		return m_value;
	}

	std::string StringValue::toString() {
		return m_value;
	}

}