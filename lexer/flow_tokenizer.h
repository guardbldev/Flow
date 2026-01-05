#pragma once
#include <vector>
#include <string>
#include "flow_keywords.h"
#include "flow_types.h"

enum class TokenKind {
    Identifier, Keyword, Type, Number, String, Symbol, Indent, Dedent, Newline, Eof, Unknown
};

struct Token {
    TokenKind kind;
    std::string text;
    int line, col;
    FlowKeyword keyword = FlowKeyword::None;
    FlowType type = FlowType::None;
};

class Tokenizer {
public:
    Tokenizer(const std::string& src);
    std::vector<Token> tokenize();
private:
    std::string src;
    size_t pos = 0;
    int line = 1, col = 1;
    char peek();
    char get();
    bool eof();
    Token nextToken();
};