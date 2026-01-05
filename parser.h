#pragma once
#include "lexer.h"

struct ASTNode {
    virtual ~ASTNode() = default;
};

struct ScreenNode : ASTNode {
    std::string name;
    std::vector<ASTNode*> children;
};

struct StateNode : ASTNode {
    std::string name;
};

struct ButtonNode : ASTNode {
    std::string label;
    std::vector<ASTNode*> actions;
};

// ... Many more AST node types for each feature/keyword!

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    ASTNode* Parse();
private:
    // Implementation details
};