#pragma once
#include "Parser.h"
#include "Tokenizer.h"
#include <iostream>
#include <functional>
#include <vector>




class Compiler
{


public:


	struct InfinityCheck {
		std::string ToCheck;
		double Location;
		bool Mod;
	};
	static ERROR_HANDLE error_handle;
	static ASTNODE* ParseExpression(std::string Text);
	static std::string GetGpuPlotShader(ASTNODE* tree);
	static std::string GenerateGPUFunction(ASTNODE* equation, std::string name);
	static std::string OperationCompilationGPU(ASTNODE* equation);
	static std::vector<InfinityCheck> InfinityChecks;
};

