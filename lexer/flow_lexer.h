#pragma once
#include <vector>
#include <string>
#include "flow_token.h"

class Lexer {
public:
    Lexer(const std::string& src);
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