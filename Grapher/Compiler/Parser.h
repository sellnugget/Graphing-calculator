#include <vector>
#include <map>
#include "Tokens.h"
#include "ERROR_HANDLE.h"

enum PRIORITY {
	COMMA = 1,COMPARISON, ADD_SUB, DIV_MUL, Preops, Postops, BRK_VALS
};



//abstract syntax tree node
struct ASTNODE {


	std::vector<ASTNODE*> Nodes;
	std::vector<Token> tokens;
	PRIORITY priority;
};

#pragma once
class Parser
{
public:
	
	static ASTNODE* Operation(const std::vector<Token>& tokens, int presidence = 1);


	static std::string NodetoString(ASTNODE* node, int depth = 0);
};

