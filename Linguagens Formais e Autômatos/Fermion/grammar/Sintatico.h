#ifndef Sintatico_H
#define Sintatico_H

#include "Constants.h"
#include "Token.h"
#include "Lexico.h"
#include "Semantico.h"
#include "SyntaticError.h"

#include <stack>
#include <vector>
#include <algorithm>

struct TreeNode {
    Token token;
    int id;
    std::vector<TreeNode*> children;

    TreeNode(const Token& token) : token(token), id(token.getId()) {}
    TreeNode(int id) : id(id) {}

    void addChild(TreeNode* child) {
        children.push_back(child);
    }
};

class Sintatico
{
public:
    Sintatico() : previousToken(0), currentToken(0) { }

    ~Sintatico()
    {
        if (previousToken != 0 && previousToken != currentToken) delete previousToken;
        if (currentToken != 0)  delete currentToken;
    }

    void parse(Lexico *scanner, Semantico *semanticAnalyser) throw (AnalysisError);

private:
    std::stack<TreeNode*> nodeStack;
    std::stack<int> stack;
    Token *currentToken;
    Token *previousToken;
    Lexico *scanner;
    Semantico *semanticAnalyser;

    bool step() throw (AnalysisError);
    void printTree(const TreeNode &node, int depth = 0);
};

#endif
