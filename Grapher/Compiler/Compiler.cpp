#include "Compiler.h"

ERROR_HANDLE Compiler::error_handle;
std::vector<Compiler::InfinityCheck> Compiler::InfinityChecks;
ASTNODE* Compiler::ParseExpression(std::string Text)
{
	Compiler::error_handle.errorList.clear();
	std::vector<Token> tokens;
	try {
		tokens = Tokenizer::GetTokens(Text);
	}
	catch (ERROR error) {
		error_handle.errorList.push_back(error);
		return NULL;
	}
	ASTNODE* node;
	try {
		if (tokens.size() == 0) {
			throw ERROR{"nothing written", ERROR::SYNTAX};
		}
		node = Parser::Operation(tokens);
		
	}
	catch(ERROR error){
		error_handle.errorList.push_back(error);
		return NULL;
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
		std::string Output = "";

		if (equation->tokens[0].data == "tan") {
			InfinityChecks.push_back({OperationCompilationGPU(equation->Nodes[0]) + " - 3.14159/2.0", 3.14159, true});
		}
		return Output + equation->tokens[0].data + "(" + OperationCompilationGPU(equation->Nodes[0]) + ")";
	}
	
	if (equation->tokens[0].data == "^") {
		return "pow(" + OperationCompilationGPU(equation->Nodes[0]) + "," + OperationCompilationGPU(equation->Nodes[1]) + ")";
	}

	std::string Chunk = "";
	if(equation->tokens[0].data != ",")
	{
		Chunk = "(";
	}
	Chunk += OperationCompilationGPU(equation->Nodes[0]);
	for (int i = 0; i < equation->tokens.size(); i++)	{
		Chunk += equation->tokens[i].data;
		Chunk += OperationCompilationGPU(equation->Nodes[i + 1]);
	}
	if (equation->tokens[0].data == ",")
	{
		return Chunk;
	}
	return Chunk + ")";
}

std::string Compiler::GenerateGPUFunction(ASTNODE* equation, std::string name)
{

	InfinityChecks.clear();
	std::string Function= "int " + name + "(vec2 Point) { \n";


	
	std::string ToAdd = "";
	if (equation->tokens[0].data == "=") {

		ToAdd += "if(" + OperationCompilationGPU(equation->Nodes[0]) + "<=" + OperationCompilationGPU(equation->Nodes[1]) + ") { \n";
	}
	else {
		ToAdd += "if( Point.y <=" + OperationCompilationGPU(equation) + ") { \n";
	}
	for (int i = 0; i < InfinityChecks.size(); i++) {
		if (InfinityChecks[i].Mod) {
			Function += "if(abs(mod(" + InfinityChecks[i].ToCheck + "," + std::to_string(InfinityChecks[i].Location) + ")) < pow(10, ZoomFactor - 2.5)) {return 2;}\n";
		}
		else {
			Function += "float value = " + InfinityChecks[i].ToCheck;+ "\n";
			Function += "if(abs(value - " + std::to_string(InfinityChecks[i].Location) + ") < 0.00001) {return 2;}\n";
		}
		
	}
	Function += ToAdd;
	Function += "return 0; \n } \n return 1;\n }";
	return Function;
}
