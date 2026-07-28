#include "Token.h"

namespace Parser {

	// STATIC
	TokenType Token::getTokenTypeFromChar(char value) {
		switch (value) {
		case '=':
			return TokenType::Equals;
		case '+':
			return TokenType::Plus;
		case '*':
			return TokenType::Times;
		case '-':
			return TokenType::Minus;
		case '/':
			return TokenType::Divide;
		case '(': 
			return TokenType::LeftParenthesis;
		case ')': 
			return TokenType::RightParenthesis;
		case ':':
			return TokenType::Colon;
		case ',':
			return TokenType::Comma;
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