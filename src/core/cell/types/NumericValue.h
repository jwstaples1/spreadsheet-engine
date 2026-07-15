#pragma once
#include "../ConstantValue.h"

namespace Cell {

	class NumericValue : public ConstantValue {

	public:
		NumericValue(double val);

		double getValue();
		std::string toString();

	private:
		double m_value;

	};

}