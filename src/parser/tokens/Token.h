#include "TokenType.h"

#include <variant>
#include <string>

namespace Parser {

	class Token {

	public:
		Token();

		TokenType getType();
		std::variant<std::string, double> getValue();

	private:
		TokenType m_type;
		std::variant<std::string, double> m_value;

	};

}