#pragma once
#include "../ConstantValue.h"

namespace Cell {

	class NumericValue : public ConstantValue {

	public:
		NumericValue(float val);

		float getValue();
		std::string toString();

	private:
		float m_value;

	};

}