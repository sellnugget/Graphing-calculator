#include "Compiler.h"

ASTNODE* Compiler::ParseExpression(std::string Text)
{
	ERROR_HANDLE errorhandle;
	std::vector<Token> tokens;
	try {
		tokens = Tokenizer::GetTokens(Text);
	}
	catch (ERROR error) {
		errorhandle.errorList.push_back(error);
		throw errorhandle;

	}
	ASTNODE* node;
	try {
		node = Parser::Operation(tokens);
	}
	catch(ERROR error){
		errorhandle.errorList.push_back(error);
		throw errorhandle;
	}
	return node;
	
}

std::string Compiler::GetGpuPlotShader(ASTNODE* tree)
{
	return "";
}

std::string Compiler::OperationCompilationGPU(ASTNODE* equation)
{
	if (equation->priority == BRK_VALS) {
		
		if (equation->tokens[0].data == "x") {
			return "Point.x";
		}
		if (equation->tokens[0].data == "y") {
			return "Point.y";
		}
		return equation->tokens[0].data;
	}

	if (equation->priority == Preops) {
		return equation->tokens[0].data + "(" + OperationCompilationGPU(equation->Nodes[0]) + ")";
	}
	if (equation->tokens[0].data == "^") {
		return "pow(" + OperationCompilationGPU(equation->Nodes[0]) + "," + OperationCompilationGPU(equation->Nodes[1]) + ")";
	}
	std::string Chunk = "(" + OperationCompilationGPU(equation->Nodes[0]);
	for (int i = 0; i < equation->tokens.size(); i++)	{
		Chunk += equation->tokens[i].data;
		Chunk += OperationCompilationGPU(equation->Nodes[i + 1]);
	}
	return Chunk + ")";
}

std::string Compiler::GenerateGPUFunction(ASTNODE* equation, std::string name)
{
	std::string Function= "int " + name + "(vec2 Point) { \n";

	if (equation->tokens[0].data == "=") {
		Function += "if(" + OperationCompilationGPU(equation->Nodes[0]) + "<" + OperationCompilationGPU(equation->Nodes[1]) + ") { \n";
	}
	else {
		Function += "if( Point.y <" + OperationCompilationGPU(equation) + ") { \n";
	}
	Function += "return 0; \n } \n return 1;\n }";
	return Function;
}
