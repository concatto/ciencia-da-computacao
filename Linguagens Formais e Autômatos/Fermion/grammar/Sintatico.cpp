#include "Sintatico.h"
#include <iostream>

void Sintatico::parse(Lexico *scanner, Semantico *semanticAnalyser) throw (AnalysisError)
{
    this->scanner = scanner;
    this->semanticAnalyser = semanticAnalyser;

    //Limpa a pilha
    while (! stack.empty())
        stack.pop();

    stack.push(0);

    if (previousToken != 0 && previousToken != currentToken)
        delete previousToken;
    previousToken = 0;

    if (currentToken != 0)
        delete currentToken;
    currentToken = scanner->nextToken();

    while ( ! step() ) {

    }

//    while (!nodeStack.empty()) {
//        printTree(nodeStack.top());

//        nodeStack.pop();
//    }

    printTree(*nodeStack.top());
}

void Sintatico::printTree(const TreeNode& node, int depth)
{
    std::cout << std::string(depth * 2, ' ');
    if (node.token.isEmpty()) {
        std::cout << "No token / " << node.id << "\n";
    } else {
        std::cout << node.token.getId() << " => Lexeme: " << node.token.getLexeme() << "\n";
    }

    for (TreeNode* child : node.children) {
        printTree(*child, depth + 1);
    }
}

bool Sintatico::step() throw (AnalysisError)
{
    if (currentToken == 0) //Fim de Sentensa
    {
        int pos = 0;
        if (previousToken != 0)
            pos = previousToken->getPosition() + previousToken->getLexeme().size();

        currentToken = new Token(DOLLAR, "$", pos);
    }

    int token = currentToken->getId();
    int state = stack.top();

    const int* cmd = PARSER_TABLE[state][token-1];

    if (cmd[0] != 2) {
        std::cout << "Lexeme: " << currentToken->getLexeme() << "\n";
    }
    switch (cmd[0])
    {
        case SHIFT:
        {
            std::cout << "Shifted " << cmd[1] << "\n";
            stack.push(cmd[1]);
            nodeStack.push(new TreeNode(*currentToken));

            if (previousToken != 0)
                delete previousToken;
            previousToken = currentToken;
            currentToken = scanner->nextToken();
            return false;
        }
        case REDUCE:
        {
            const int* prod = PRODUCTIONS[cmd[1]];

            std::stack<TreeNode*> temp;
            std::cout << "Reducing " << prod[1] << " items.\n";
            for (int i=0; i<prod[1]; i++) {
                std::cout << "R: " << stack.top() << "\n";
                stack.pop();
                if (!nodeStack.empty()) {
                    temp.push(nodeStack.top());
                    nodeStack.pop();
                }
            }

            TreeNode* node = new TreeNode(prod[0]);
            while (!temp.empty()) {
                node->addChild(temp.top());
                temp.pop();
            }

            nodeStack.push(node);

            int oldState = stack.top();
            stack.push(PARSER_TABLE[oldState][prod[0]-1][1]);
            return false;
        }
        case ACTION:
        {
            int action = FIRST_SEMANTIC_ACTION + cmd[1] - 1;
            stack.push(PARSER_TABLE[state][action][1]);
            semanticAnalyser->executeAction(cmd[1], previousToken);
            return false;
        }
        case ACCEPT:
            return true;

        case ERROR:
            throw SyntaticError(PARSER_ERROR[state], currentToken->getPosition());
    }
    return false;
}

