#pragma once
#include <string>
class Token {

public:



	
	static std::string tokenTypes[5];
	static std::string keywordTypes[34];
	static std::string operatorTypes[11];
	enum TokenType {
		EMPTY = 0, NODE = 0, CONST, IDENTIFIER, KEYWORD, OPERATOR
	};	
	TokenType type = EMPTY;
	std::string data = "";
	
	std::string toString();
};
