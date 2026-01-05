#include "flow_parser.h"
#include <stdexcept>
#include <iostream>

Parser::Parser(const std::vector<Token>& toks) : tokens(toks), pos(0) {}

Token Parser::peek(int offset) { size_t p = pos + offset; return p < tokens.size() ? tokens[p] : tokens.back(); }
Token Parser::get() { if (pos < tokens.size()) return tokens[pos++]; return tokens.back(); }
bool Parser::accept(TokenKind kind) { if (peek().kind == kind) { get(); return true; } return false; }
bool Parser::expect(TokenKind kind) { if (peek().kind == kind) { get(); return true; } throw std::runtime_error("Parse error"); }

ASTKind Parser::astKindFromKeyword(FlowKeyword kw) {
    switch (kw) {
        case FlowKeyword::Var:           return ASTKind::VarDecl;          // mutable variable declaration
        case FlowKeyword::Let:           return ASTKind::LetDecl;          // immutable variable declaration
        case FlowKeyword::State:         return ASTKind::StateDecl;        // reactive UI state
        case FlowKeyword::Func:          return ASTKind::FuncDecl;         // function declaration
        case FlowKeyword::Async:         return ASTKind::AsyncFuncDecl;    // async function
        case FlowKeyword::Await:         return ASTKind::AwaitExpr;        // await
        case FlowKeyword::Return:        return ASTKind::ReturnStmt;       // return value
        case FlowKeyword::If:            return ASTKind::IfStmt;
        // ... (continue EVERY keyword → ASTKind mapping, for ALL 200)
        case FlowKeyword::Websocket:     return ASTKind::WebsocketBlock;   // websocket networking
        default:                         return ASTKind::Expr;
    }
}

ASTNode* Parser::parse() {
    auto root = new ASTNode{ASTKind::Block, {}, ""};
    while (peek().kind != TokenKind::Eof)
        root->children.push_back(parseStatement());
    return root;
}

ASTNode* Parser::parseStatement() {
    Token tk = peek();
    if (tk.kind == TokenKind::Keyword) {
        ASTKind kind = astKindFromKeyword(tk.keyword);
        get(); // consume keyword

        if (kind == ASTKind::VarDecl || kind == ASTKind::LetDecl || kind == ASTKind::StateDecl) {
            std::string name = "";
            if (accept(TokenKind::Identifier)) name = tokens[pos-1].text;
            if (accept(TokenKind::Symbol) && peek().text == ":") get();
            ASTNode* typeNode = parseTypeExpr();
            ASTNode* valueNode = nullptr;
            if (accept(TokenKind::Symbol) && peek().text == "=") get();
            if (peek().kind != TokenKind::Newline && peek().kind != TokenKind::Eof)
                valueNode = parseExpr();
            auto node = new ASTNode{kind, {}, name, tk.keyword};
            if (typeNode) node->children.push_back(typeNode);
            if (valueNode) node->children.push_back(valueNode);
            return node;
        }

        if (kind == ASTKind::FuncDecl || kind == ASTKind::AsyncFuncDecl) {
            std::string name = "";
            if (accept(TokenKind::Identifier)) name = tokens[pos-1].text;
            accept(TokenKind::Symbol); // (
            std::vector<std::string> params;
            while (!accept(TokenKind::Symbol) || peek().text != ")") {
                if (accept(TokenKind::Identifier)) params.push_back(tokens[pos-1].text);
                if (accept(TokenKind::Symbol) && peek().text == ",") get();
            }
            expect(TokenKind::Symbol); // )
            accept(TokenKind::Symbol); // :
            ASTNode* typeNode = parseTypeExpr();
            ASTNode* blockNode = parseBlock();
            auto node = new ASTNode{kind, {typeNode, blockNode}, name, tk.keyword};
            return node;
        }

        // For ALL other blocks (UI, layout, styling, events, state, animation, networking, etc)
        if (kind != ASTKind::Expr && kind != ASTKind::NumberLiteral && kind != ASTKind::StringLiteral && kind != ASTKind::Identifier) {
            std::string label = "";
            if (accept(TokenKind::Identifier)) label = tokens[pos-1].text;
            accept(TokenKind::Symbol);
            auto blockNode = parseBlock();
            auto node = new ASTNode{kind, {blockNode}, label, tk.keyword};
            return node;
        }
    }
    return parseExpr();
}

ASTNode* Parser::parseBlock() {
    auto block = new ASTNode{ASTKind::Block, {}, ""};
    while (peek().kind != TokenKind::Dedent && peek().kind != TokenKind::Eof && peek().kind != TokenKind::Symbol)
        block->children.push_back(parseStatement());
    if (peek().kind == TokenKind::Dedent) get();
    return block;
}

ASTNode* Parser::parseTypeExpr() {
    Token tk = peek();
    if (tk.kind == TokenKind::Keyword) {
        get();
        auto node = new ASTNode{ASTKind::TypeExpr, {}, tk.text, tk.keyword};
        if (accept(TokenKind::Symbol) && peek().text == "<") {
            get();
            while (!accept(TokenKind::Symbol) || peek().text != ">") {
                node->children.push_back(parseTypeExpr());
                if (accept(TokenKind::Symbol) && peek().text == ",") get();
            }
            expect(TokenKind::Symbol); // '>'
        }
        return node;
    }
    throw std::runtime_error("Type expected");
}

ASTNode* Parser::parseExpr() {
    Token tk = get();
    if (tk.kind == TokenKind::Number)    return new ASTNode{ASTKind::NumberLiteral, {}, tk.text};
    if (tk.kind == TokenKind::String)    return new ASTNode{ASTKind::StringLiteral, {}, tk.text};
    if (tk.kind == TokenKind::Identifier)return new ASTNode{ASTKind::Identifier, {}, tk.text};
    return new ASTNode{ASTKind::Expr, {}, tk.text};
}

void Parser::dumpAST(ASTNode* node, int indent) {
    std::string spaces(indent * 2, ' ');
    std::cout << spaces << "Node: " << static_cast<int>(node->kind) << " (" << node->text << ")\n";
    for(auto* child : node->children)
        dumpAST(child, indent + 1);
}