#include "Tokens.h"

//all different types of tokens
std::string Token::tokenTypes[] =
{
	"empty","const", "identifier", "keyword","operator",
};
std::string Token::keywordTypes[] =
{
	//triganometric functions
	"sin","cos", "tan", "csc", "sec", "cot",
	"arcsin","arccos", "arctan", "arccsc", "arcsec", "arccot",
	"sinh","cosh","tanh","csch","sech","coth",
	//logerithmic functions
	"sqrt", "log", "ln", "exp",
	//other functions
	"abs", "mod", "round", "sign", "floor", "ceil","max","min",

};
std::string Token::operatorTypes[] = {
	"(",")", "^","/","*","-","+","=", ","
};

std::string Token::toString()
{

	std::string output = "";

	output += Token::tokenTypes[type];
	output += ": ";
	output += data + "\n";
	return output;
}
