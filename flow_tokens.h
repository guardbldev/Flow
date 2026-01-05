#pragma once
#include <string>
#include "flow_keywords.h"

enum class FlowTokenKind {
    Identifier,
    Keyword,
    Type,
    Number,
    String,
    Symbol,
    Indent,
    Dedent,
    Newline,
    Eof
    // Extend as needed
};

struct FlowToken {
    FlowTokenKind kind;
    std::string text;
    int line;
    int col;
    FlowKeyword keyword;   // if kind==Keyword
    FlowType type;         // if kind==Type
};