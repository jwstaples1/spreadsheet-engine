#include "Rules.h"
#include "../tokens/Token.h"

#include <iostream>

namespace Parser {

	Token fromStringNumericToAddress(TransformationFunctionArgs values) {
		return Token(TokenType::CellAddress, " Complex ! ");
	}

	Token fromAddressesToRange(TransformationFunctionArgs values) {
		return Token(TokenType::Range, " Complex ! ");
	}

	Token fromNameAndArgsToFormula(TransformationFunctionArgs values) {
		return Token(TokenType::ExternalFormula, " Complex ! ");
	}

	Token fromRangeToArguments(TransformationFunctionArgs values) {
		return Token(TokenType::Arguments, " Complex ! ");
	}

}