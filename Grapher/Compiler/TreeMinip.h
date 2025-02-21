#pragma once
#include "Parser.h"
//different tree manipulations





class TreeMinip
{
public:

	ASTNODE* ComputeConstants(ASTNODE* tree);


	ASTNODE* IsolateVar(ASTNODE* tree, std::string IdentiferName);
public:
};

