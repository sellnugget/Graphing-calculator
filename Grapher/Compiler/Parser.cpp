#include "Parser.h" 



std::map<std::string, int> Priorities =
{
    {",", COMMA}, {"=", COMPARISON}, {"+", ADD_SUB}, {"-", ADD_SUB}, {"/", DIV_MUL}, {"*", DIV_MUL}

};

std::map<int, std::string> priorityToString =
{
    {COMPARISON, "COMPARISON"}, {ADD_SUB, "ADD_SUB"}, {DIV_MUL, "DIV_MUL"}, {Preops, "Preops" }, {Postops, "Postops"},
    {BRK_VALS,"VALUE"}

};
ASTNODE* Parser::Operation(const std::vector<Token>& tokens, int presidence)
{
    std::vector<Token> tokensInOperation;

    ASTNODE* node = new ASTNODE();
    node->priority = (PRIORITY)presidence;
    /*
    if (tokens.size() == 1) {
        node->tokens.push_back(tokens[0]);
        return node;
    }
    else if (tokens[0].data == "(" && tokens[tokens.size() - 1].data == ")") {
        tokensInOperation.assign(tokens.begin() + 1, tokens.end() - 1);
        return Operation(tokensInOperation);
    }
    
    */
    

    if (presidence == Preops) {
        
        if ((tokens[0].type == Token::OPERATOR || tokens[0].type == Token::KEYWORD) && tokens[0].data != "(") {
            node->tokens.push_back(tokens[0]);
            std::vector<Token> tokenbuff;
            tokenbuff.assign(tokens.begin() + 1, tokens.end());
            node->Nodes.push_back(Operation(tokenbuff, Preops));
            return node;
        }
        else {
            delete node;
            return Operation(tokens, presidence + 1);
        }
    }
    if (presidence == Postops) {

        int i = 0;
        int depth = 0;
        if (tokens[0].data == "(") {
            tokensInOperation.push_back(tokens[i]);
            depth++;
            i++;
        }
        while (i < tokens.size() && (tokens[i].type != Token::OPERATOR || depth > 0)) {
            tokensInOperation.push_back(tokens[i]);
        
            if (tokens[i].data == "(") {
                depth++;
            }
            if (tokens[i].data == ")") {
                depth--;
            }
            i++;
        }

        if (depth != 0) {
            throw ERROR{ "Missing \")\"", ERROR::SYNTAX };
        }
        if (tokensInOperation.size() != tokens.size()) {
            node->tokens.push_back(tokens[i]);
            node->Nodes.push_back(Operation(tokensInOperation, presidence + 1));
            std::vector<Token> tokenbuff;
            
            if (i + 1 >= tokens.size() || (tokens[i + 1].type == Token::OPERATOR && tokens[i + 1].data != ")")) {
                throw ERROR{ "post operation contains nothing", ERROR::SYNTAX };
            }

            tokenbuff.assign(tokens.begin() + i + 1, tokens.end());
            node->Nodes.push_back(Operation(tokenbuff, presidence - 1));
            return node;
        }
        else {

           
            delete node;
            return Operation(tokens, presidence + 1);
        }  
    }
    if (presidence == BRK_VALS) {
        if (tokens[0].data == "(") {
            delete node;
            std::vector<Token> tokenbuff;
            if (tokens[tokens.size() - 1].data != ")") {
                throw ERROR{ "Missing \")\"", ERROR::SYNTAX };
            }
            if (tokens.size() == 2) {
                throw ERROR{ "Cannot have empty ( )", ERROR::SYNTAX };
            }
            tokenbuff.assign(tokens.begin() + 1, tokens.end() - 1);
            return Operation(tokenbuff);
        }
        else {
            node->tokens.assign(tokens.begin(), tokens.end());
            
            return node;
        }
    }

    int depth = 0;
    bool noneOperator = false;
    for (int i = 0; i < tokens.size(); i++) {



        if (tokens[i].data == "(") {
            depth++;
            noneOperator = true;
        }
        else if (tokens[i].data == ")")
            depth--;
        else if (depth == 0) {

            if (tokens[i].type != Token::OPERATOR) {
                noneOperator = true;
            }

            if (Priorities[tokens[i].data] == presidence && tokensInOperation.size() > 0 && noneOperator) {
                node->Nodes.push_back(Operation(tokensInOperation, presidence + 1));
                node->tokens.push_back(tokens[i]);
                tokensInOperation.clear();
                noneOperator = false;
                continue;
            }
        }
        tokensInOperation.push_back(tokens[i]);
    }
    if (depth != 0) {
        throw ERROR{ "Missing \")\"", ERROR::SYNTAX };
    }
    if (node->tokens.size() == 0) {
        delete node;
        return Operation(tokens, presidence + 1);
    }
    else {
        node->Nodes.push_back(Operation(tokensInOperation, presidence + 1));
    }
    return node;
}

std::string Parser::NodetoString(ASTNODE* node, int depth)
{
    std::string output = "";

    for (int i = 0; i < depth; i++) {
        output += "\t";
    }
    output += priorityToString[node->priority] + "\n";
  
    for (int i = 0; i < node->tokens.size(); i++) {
    
        for (int i = 0; i < depth + 1; i++) {
            output += "\t";
        }

        output += node->tokens[i].toString();
    }
  

    for (int i = 0; i < node->Nodes.size(); i++) {

        output += NodetoString(node->Nodes[i], depth + 1);
        continue;
    }
    return output;
}


 