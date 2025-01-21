#include "GS_COMPILER.h"

ASTNODE* GS_COMPILER::Compile(std::string text)
{
	std::vector<Token> tokens = Tokenizer::GetTokens(text);
	ASTNODE* node = globalSpace(tokens);
	return node;
}

ASTNODE* GS_COMPILER::globalSpace(std::vector<Token> tokens)
{

	ASTNODE* node = new ASTNODE();

	int index = 0;
	while (FindToken(tokens, index, { Token::KEYWORD, "fn" }) != -1) {
		ASTNODE* funcnode = new ASTNODE();
		funcnode->tokens.push_back({ Token::KEYWORD, "fn" });
		funcnode->tokens.push_back(FindCheckNext(tokens, index, Token::IDENTIFIER));
		funcnode->Nodes.push_back(findParameters(tokens, index));
		funcnode->Nodes.push_back(blockSpace(tokens, index));
		node->Nodes.push_back(funcnode);

	}
	return node;
}

ASTNODE* GS_COMPILER::funcSpace(std::vector<Token> tokens)
{
	return nullptr;
}


ASTNODE* GS_COMPILER::blockSpace(std::vector<Token> tokens, int& start)
{
	ASTNODE* output = new ASTNODE();
	std::vector<Token> blockTokens;
	start++;
	start++;
	Token token = tokens[start];
	int depth = 0;
	while (token.data != "}" && depth == 0) {
		
		if (token.data == "{") {
			depth++;
		}
		if (token.data == "}") {
			depth--;
		}
		blockTokens.push_back(token);
		start++;
		token = tokens[start];
	}

	for (int i = 0; i < blockTokens.size(); i++) {
		if (blockTokens[i].data == "var") {
			Token identifier;
		}
	}
	return output;
}

ASTNODE* GS_COMPILER::findParameters(std::vector<Token> tokens, int& index)
{
	index++;
	Token token = tokens[index];

	ASTNODE* mainNode = new ASTNODE();
	ASTNODE* subNode = new ASTNODE();
	while (token.data != ")") {

		if (token.data == ",") {
			mainNode->Nodes.push_back(subNode);
			subNode = new ASTNODE();
		}
		else {
			subNode->tokens.push_back(token);
		}

		index++;
		token = tokens[index];
		if (token.data == ")") {
			mainNode->Nodes.push_back(subNode);
		}
	}
	return mainNode;
}

Token GS_COMPILER::FindCheckNext(std::vector<Token> tokens, int &current, Token::TokenType should_be)
{
	current++;
	Token a = tokens[current];
	if (a.type != should_be) {
		throw;
	}
	else {
		current++;
		return tokens[current - 1];
	}
}

int GS_COMPILER::FindToken(std::vector<Token> tokens, int& index, Token token)
{
	for (int i = index; i < tokens.size(); i++) {
		if (tokens[i].data == token.data && tokens[i].type == token.type) {
			index = i;
			return i;
		}
	}
	return -1;
}
