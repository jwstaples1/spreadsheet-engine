#pragma once

#include "TokenType.h"

#include <variant>
#include <string>

namespace Parser {

	using TokenValue = std::variant<std::string, double>;

	class Token {

	public:
		Token(std::string value);
		Token(double value);

		Token(TokenType type, TokenValue value);

		TokenType getType();
		TokenValue getValue();

		static TokenType getTokenTypeFromChar(char value);

	private:
		TokenType m_type;
		TokenValue m_value;

	};

}