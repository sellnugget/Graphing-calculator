#pragma once
#include "Tokenizer.h"
#include <fstream>
#include "Parser.h"
class GS_COMPILER
{
	public:
		ASTNODE* Compile(std::string text);
		ASTNODE* globalSpace(std::vector<Token> tokens);
		ASTNODE* funcSpace(std::vector<Token> tokens);


		ASTNODE* blockSpace(std::vector<Token> tokens, int& index);

		ASTNODE* findParameters(std::vector<Token> tokens, int& index);
		Token FindCheckNext(std::vector<Token> tokens, int &current, Token::TokenType should_be);
		int FindToken(std::vector<Token> tokens, int& index, Token token);

};

