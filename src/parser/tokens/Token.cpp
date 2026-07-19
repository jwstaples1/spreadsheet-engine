#include "Token.h"

namespace Parser {

	// STATIC
	TokenType Token::getTokenTypeFromChar(char value) {
		switch (value) {
		case '=':
			return TokenType::Equals;
		case '+':
			return TokenType::Plus;
		default:
			return TokenType::String;
		}
	}

	bool Token::isDynamicTokenType(TokenType type) {
		return type == TokenType::Numeric || type == TokenType::String;
	}

	// NOT STATIC
	Token::Token(std::string value) : Token(TokenType::String, value) {};

	Token::Token(double value) : Token(TokenType::Numeric, value) {};

	Token::Token(TokenType type, TokenValue value) : m_type(type), m_value(value) {};

	TokenType Token::getType() {
		return m_type;
	}

	TokenValue Token::getValue() {
		return m_value;
	}
}