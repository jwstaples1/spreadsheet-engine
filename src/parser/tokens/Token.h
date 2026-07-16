#include "TokenType.h"

#include <variant>
#include <string>

namespace Parser {

	class Token {

	public:
		Token(std::string value);
		Token(double value);

		Token(TokenType type, std::variant<std::string, double> value);

		TokenType getType();
		std::variant<std::string, double> getValue();

	private:
		TokenType m_type;
		std::variant<std::string, double> m_value;

	};

}