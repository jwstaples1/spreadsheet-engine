#pragma once

enum class TokenType {
	Empty,

	Equals, // signifies the beginning of a formula

	// Tokens which are dynamic size
	Numeric, // numbers like 1, 1.0, 1.235, -1
	String, // any character or series of characters

	LeftParenthesis,
	RightParenthesis,
	Comma,
	Colon,
	Period,

	Plus,
	Minus,
	Times,
	Divide,
	Exponent,

	// Complex Tokens -- only used during evaluation step
	CellAddress,
	Arguments,
	Expression,
	Range,
	ExternalFormula,
};