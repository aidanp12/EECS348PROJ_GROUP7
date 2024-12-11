#ifndef PARSER_H
#define PARSER_H

#include <string>

class Parser {
private: 
	// variables
	std::string expression;
	std::string result;
	
	// function prototypes
	void remove_spaces(std::string &expression);
	void check_parens(const std::string &expression);
	void check_invalid_char(const std::string &expression);
	std::string simplify(std::string expression);
	std::string combine_subexpressions(std::string operand1, std::string operation, std::string operand2);
	
public: 
	// constructor
	Parser(std::string s);
	
	// Function prototypes
	std::string convert();
};

#endif

