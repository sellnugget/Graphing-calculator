#pragma once
#include "Tokens.h"
#include <vector>
#include "ERROR_HANDLE.h"
class Tokenizer
{
public:

	static std::vector<Token> GetTokens(std::string Text);


private:

	//checks if current char is operators
	static bool CheckIsOP(char NewChar);
	static void PushDynamicToken(std::string token, std::vector<Token>& array);

};

