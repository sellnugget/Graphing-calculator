#pragma once
#include "Compiler/Compiler.h"
#include <functional>
#include <math.h>
class NodeExecutor
{
public:
	
	std::map<std::string, ASTNODE*> Identifiers;

	double ExecuteNode(ASTNODE* startNode);
};

