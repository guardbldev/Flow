#pragma once
#include <string>
#include "flow_vocab.h"

enum class TokenKind {
    Identifier, Keyword, Number, String, Symbol, Indent, Dedent, Newline, Eof, Unknown
};

struct Token {
    TokenKind kind;
    std::string text;
    int line, col;
    FlowKeyword keyword = FlowKeyword::None;
};