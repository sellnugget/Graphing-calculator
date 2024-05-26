#include "Tokenizer.h"
std::vector<Token> Tokenizer::GetTokens(std::string Text)
{
	std::vector<Token> Output;
	std::string ActiveID = "";

	for (int i = 0; i < Text.length(); i++) {

		if (CheckIsOP(Text[i])) {
			PushDynamicToken(ActiveID, Output);
			ActiveID = "";

			std::string character = "";
			character += Text[i];
			Output.push_back({ Token::OPERATOR,character });
			continue;
		}
		if (Text[i] == ' ' || Text[i] == '\t') {

			PushDynamicToken(ActiveID, Output);
			ActiveID = "";
			continue;
		}
		//checks if it its number constant
		if ((Text[i] <= '9' && Text[i] >= '0') || Text[i] == '.') {

			PushDynamicToken(ActiveID, Output);
			ActiveID = "";
			std::string Number = "";
			//keeps track if we have hit a decimal yet (for error checking)
			bool decimalHit = false;
			bool DidEnd = false;
			for (i; ((Text[i] <= '9' && Text[i] >= '0') || Text[i] == '.'); i++) {
				if (Text[i] == '.') {
					
					if (decimalHit) {
						throw ERROR{ "const value cannot have multiply decimal points", ERROR::SYNTAX };
					}

					decimalHit = true;
				}
				Number += Text[i];
				if (i + 1 >= Text.length()) {
					DidEnd = true;
					break;
				}
			}
			Output.push_back({ Token::CONST, Number });
			if (!DidEnd) {
				i--;
			}
			
			continue;
		}
		ActiveID += Text[i];
		if (i + 1 >= Text.length()) {
			PushDynamicToken(ActiveID, Output);
		}
	}

	return Output;
}

bool Tokenizer::CheckIsOP(char NewChar)
{
	for (int i = 0; i < std::size(Token::operatorTypes); i++) {
		if (NewChar == Token::operatorTypes[i][0]) {
			return true;
		}
	}
	return false;
}
#include <map>
std::map<std::string, std::string> Constants = {
	{"pi", "3.14159265359"}, {"tau", "6.28318530718"}, {"e", "2.71828182846"}, {"infty", "infty"}
};

void Tokenizer::PushDynamicToken(std::string token, std::vector<Token>& array)
{
	//check if it is a 
	if (token.empty()) {
		return;
	}

	//check if it is a keyword
	for (int i = 0; i < std::size(Token::keywordTypes); i++) {
		if (token == Token::keywordTypes[i]) {
			array.push_back({ Token::KEYWORD ,token });
			return;
		}
	}
	if (Constants.find(token) != Constants.end()) {
		array.push_back({ Token::CONST, Constants[token] });
	}
	else {
		//other wise we know that this is a identifier
		array.push_back({ Token::IDENTIFIER, token });
	}


}
