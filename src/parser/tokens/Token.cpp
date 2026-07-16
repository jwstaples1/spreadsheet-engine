#include "Token.h"

namespace Parser {

	Token::Token() {};

	TokenType Token::getType() {
		return m_type;
	}

	std::variant<std::string, double> Token::getValue() {
		return m_value;
	}
}