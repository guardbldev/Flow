#pragma once
#include <vector>
#include <string>
#include "flow_vocab.h"
#include "flow_ast.h"

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    ASTNode* parse();
    void dumpAST(ASTNode* node, int indent = 0); // AST dump routine
private:
    const std::vector<Token>& tokens;
    size_t pos;
    Token peek(int offset = 0);
    Token get();
    bool accept(TokenKind kind);
    bool expect(TokenKind kind);

    ASTNode* parseStatement();
    ASTNode* parseBlock();
    ASTNode* parseTypeExpr();
    ASTNode* parseExpr();

    ASTKind astKindFromKeyword(FlowKeyword kw);
};