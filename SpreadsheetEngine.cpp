// SpreadsheetEngine.cpp : Defines the entry point for the application.
//
#include <memory>
#include <vector>
#include <format>
#include <variant>

#include "SpreadsheetEngine.h"
#include "src/core/Spreadsheet.h"
#include "src/core/Formula.h"
#include "src/core/cell/CellAddress.h"
#include "src/core/cell/types/NumericValue.h"
#include "src/core/cell/types/StringValue.h"
#include "src/core/cell/types/FormulaicValue.h"

#include "src/parser/Parser.h"
#include "src/parser/tokens/Token.h"
#include "src/parser/tokens/TokenType.h"

using namespace std;

void mockSpreadsheet();
void mockParser();

int main()
{
	mockSpreadsheet();
	mockParser();

	return 0;
}

void mockSpreadsheet() {
	cout << "CORE SPREADSHEET TEST" << endl << "------------" << endl;
	
	// Create the spreadsheet
	Spreadsheet::Spreadsheet spreadsheet("New spreadsheet!");
	cout << spreadsheet.getName() << endl;

	// define 3 cell addresses
	Cell::CellAddress addr("A", 4);
	cout << addr.toString() << endl;

	Cell::CellAddress addr2("B", 3);
	cout << addr2.toString() << endl;

	Cell::CellAddress addr3("C", 2);
	cout << addr3.toString() << endl;

	// define 3 cell values
	Cell::NumericValue numVal(1234.12345);

	Cell::StringValue stringVal("hello world!");

	Cell::FormulaicValue formulaicVal(Spreadsheet::Formula("=1+2"));

	// add entries, and check they persist
	spreadsheet.setValue(addr, std::make_unique<Cell::NumericValue>(numVal));
	spreadsheet.setValue(addr2, std::make_unique<Cell::StringValue>(stringVal));
	spreadsheet.setValue(addr3, std::make_unique<Cell::FormulaicValue>(formulaicVal));

	const SpreadsheetEntries& entries = spreadsheet.getEntries();

	cout << entries.at(addr)->toString() << endl;
	cout << entries.at(addr2)->toString() << endl;
	cout << entries.at(addr3)->toString() << endl;

	// try to clear the first address and check the data is cleared out
	spreadsheet.clearValue(addr);

	if (!entries.contains(addr)) {
		cout << addr.toString() + " cleared successfully" << endl;
	}
}

void mockParser() {
	cout << endl << endl << "PARSER TEST" << endl << "------------" << endl;
	
	// create a few different types of tokens to test the values and types persist correctly
	Parser::Token tok1(4.5);
	Parser::Token tok2("test");
	Parser::Token tok3(TokenType::Equals, "=");

	std::vector<Parser::Token> tokens = { tok1, tok2, tok3 };
	constexpr std::string_view formatString = "Idx: {} | Type: {} | Val: {}";
	for (int i = 0; i < tokens.size(); i++) {
		Parser::Token tok = tokens.at(i);
		std::variant <std::string, double> value = tok.getValue();

		// AI written code to convert from std::variant<string, double> to string
		std::string stringifiedValue = std::visit([](auto&& arg) -> std::string {
			using T = std::decay_t<decltype(arg)>;
			if constexpr (std::is_same_v<T, std::string>) {
				return arg;
			}
			else {
				return std::to_string(arg);
			}
			}, tok.getValue());

		cout << std::format(formatString, i, (int)tok.getType(), stringifiedValue) << endl;
	}

	// create a formula and test evaluate it to ensure it evaluates correctly
	Spreadsheet::Formula formula("=123+245");
	Spreadsheet::Formula formula2("=A4+B8");
	Spreadsheet::Formula errorFormula("2+3");
	Spreadsheet::Formula complexFormula("=A4*3+2+SUM(B3:N9)+SUM(1, 3+G6)");

	Parser::Parser testParser;

	testParser.evaluate(formula);
	testParser.evaluate(formula2);
	testParser.evaluate(errorFormula);
	testParser.evaluate(complexFormula);

}