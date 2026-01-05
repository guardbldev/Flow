#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "flow_vocab.h"

// Each language construct gets a unique ASTKind.
enum class ASTKind {
    VarDecl,          // mutable variable declaration
    LetDecl,          // immutable variable declaration
    StateDecl,        // reactive UI state declaration
    FuncDecl,         // function declaration
    AsyncFuncDecl,    // async function declaration
    AwaitExpr,        // await expression
    ReturnStmt,       // return statement
    IfStmt,           // conditional
    // ...
    WebsocketBlock,   // websocket networking block
    // (add all 200 constructs)
    Block,            // generic statement block
    Expr              // generic expression
};

struct ASTNode {
    ASTKind kind;
    std::vector<ASTNode*> children;
    std::string text;
    FlowKeyword keyword = FlowKeyword::None;
    std::unordered_map<std::string, std::string> props; // extensible
    ~ASTNode() { for (auto c : children) delete c; }
};