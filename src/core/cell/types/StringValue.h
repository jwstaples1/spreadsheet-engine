#pragma once
#include "../ConstantValue.h"

namespace Cell {

	class StringValue : public ConstantValue {

	public:
		StringValue(std::string value);

		std::string getValue();
		std::string toString();

	private:
		std::string m_value;

	};

}