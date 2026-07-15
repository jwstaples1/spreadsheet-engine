#pragma once
#include "CellValue.h"

namespace Cell {

	class ConstantValue : public CellValue {

	public:
		virtual ~ConstantValue() = default;
	};

}