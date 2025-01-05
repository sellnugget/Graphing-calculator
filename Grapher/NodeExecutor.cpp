#include "NodeExecutor.h"
double NodeExecutor::ExecuteNode(ASTNODE* startNode)
{



	if (startNode == NULL) {
		return NULL;
	}
	Token token = startNode->tokens[0];
	if (token.type == Token::OPERATOR || token.type == Token::KEYWORD) {

		if (startNode->priority == Preops) {
			if (token.data == "-") {
				return -ExecuteNode(startNode->Nodes[0]);
			}
			else if (token.data == "sin") {
				return sin(ExecuteNode(startNode->Nodes[0]));
			}
			else if (token.data == "cos") {
				return cos(ExecuteNode(startNode->Nodes[0]));
			}
			else if (token.data == "tan") {
				return tan(ExecuteNode(startNode->Nodes[0]));
			}
			else if (token.data == "csc") {
				return 1.0f/sin(ExecuteNode(startNode->Nodes[0]));
			}
			else if (token.data == "sec") {
				return 1.0f / cos(ExecuteNode(startNode->Nodes[0]));
			}
			else if (token.data == "cot") {
				return 1.0f / tan(ExecuteNode(startNode->Nodes[0]));
			}
			else if (token.data == "arcsin") {
				return asin(ExecuteNode(startNode->Nodes[0]));
			}
			else if (token.data == "arccos") {
				return acos(ExecuteNode(startNode->Nodes[0]));
			}
			else if (token.data == "arctan") {
				return atan(ExecuteNode(startNode->Nodes[0]));
			}
			else if (token.data == "sinh") {
				return sinh(ExecuteNode(startNode->Nodes[0]));
			}
			else if (token.data == "cosh") {
				return cosh(ExecuteNode(startNode->Nodes[0]));
			}
			else if (token.data == "tanh") {
				return tanh(ExecuteNode(startNode->Nodes[0]));
			}
			else if (token.data == "sqrt") {
				return sqrt(ExecuteNode(startNode->Nodes[0]));
			}
			else if (token.data == "log") {
				return log10(ExecuteNode(startNode->Nodes[0]));
			}
			else if (token.data == "ln") {
				return log(ExecuteNode(startNode->Nodes[0]));
			}
			else if (token.data == "exp") {
				return exp(ExecuteNode(startNode->Nodes[0]));
			}
			else if (token.data == "abs") {
				return abs(ExecuteNode(startNode->Nodes[0]));
			}
			else if (token.data == "mod") {
				double node0 = ExecuteNode(startNode->Nodes[0]->Nodes[0]);
				double node1 = ExecuteNode(startNode->Nodes[0]->Nodes[1]);

				double integral;
				double value = modf(node0 / node1, &integral);

				return value * node1;
			}
			else if (token.data == "round") {
				return round(ExecuteNode(startNode->Nodes[0]));
			}
			else if (token.data == "sign") {
				double node = ExecuteNode(startNode->Nodes[0]);
				if (node > 0) {
					return 1;
				}
				if (node < 0) {
					return -1;
				}
				return 0;
			}
			else if (token.data == "floor") {
				return floor(ExecuteNode(startNode->Nodes[0]));
			}
			else if (token.data == "ceil") {
				return ceil(ExecuteNode(startNode->Nodes[0]));
			}
			else if (token.data == "max") {
				return std::max(ExecuteNode(startNode->Nodes[0]->Nodes[0]), ExecuteNode(startNode->Nodes[0]->Nodes[1]));
			}
			else if (token.data == "min") {
				return std::min(ExecuteNode(startNode->Nodes[0]->Nodes[0]), ExecuteNode(startNode->Nodes[0]->Nodes[1]));
			}

		}
		if (startNode->priority == Postops) {
			if (token.data == "^") {
				double Number = pow(ExecuteNode(startNode->Nodes[0]), ExecuteNode(startNode->Nodes[1]));
				return Number;
			}
		}

		if(startNode->priority == Postops){}
		double Total = ExecuteNode(startNode->Nodes[0]);
		for (int i = 0; i < startNode->tokens.size(); i++) {

			switch (startNode->tokens[i].data[0]) {
			case '+':
				Total += ExecuteNode(startNode->Nodes[i + 1]);
				continue;
			case '-':
				Total -= ExecuteNode(startNode->Nodes[i + 1]);
				continue;
			case '*':
				Total *= ExecuteNode(startNode->Nodes[i + 1]);
				continue;
			case '/':
				Total /= ExecuteNode(startNode->Nodes[i + 1]);
				continue;
			}
		}
		return Total;
		
	}
	else if(token.type == Token::IDENTIFIER) {
		if (Identifiers.find(startNode->tokens[0].data) != Identifiers.end()) {
			return ExecuteNode(Identifiers[startNode->tokens[0].data]);
		}
		else {
			return NAN;
		}
	
	}
	else if (token.type == Token::CONST) {
		return stod(token.data);
	}
}
