#pragma once
#include "Parser.h"
#include "Tokenizer.h"
#include <iostream>
class Compiler
{
public:
	static ASTNODE* ParseExpression(std::string Text);
	static std::string GetGpuPlotShader(ASTNODE* tree);
	static std::string GenerateGPUFunction(ASTNODE* equation, std::string name);
	static std::string OperationCompilationGPU(ASTNODE* equation);
};

