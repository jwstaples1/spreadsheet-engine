#pragma once

enum class TokenType {
	Equals, // signifies the beginning of a formula
	
	// Tokens which are dynamic size
	Numeric, // numbers like 1, 1.0, 1.235, -1
	String, // any character or series of characters
	
	Plus, // addition operator
};