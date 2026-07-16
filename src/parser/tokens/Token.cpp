#include "Token.h"

namespace Parser {

	Token::Token(std::string value) : Token(TokenType::String, value) {};

	Token::Token(double value) : Token(TokenType::Numeric, value) {};

	Token::Token(TokenType type, std::variant<std::string, double> value) : m_type(type), m_value(value) {};

	TokenType Token::getType() {
		return m_type;
	}

	std::variant<std::string, double> Token::getValue() {
		return m_value;
	}
}