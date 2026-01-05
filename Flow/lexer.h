#pragma once
#include <string>
#include <vector>

enum class TokenType {
    Identifier, Number, String,
    Keyword, Symbol,
    Newline, Indent, Dedent, 
    LBrace, RBrace, LParen, RParen,
    Comma, Colon, Eof,
    // ... add all symbols/keywords needed
};

struct Token {
    TokenType type;
    std::string text;
    int line, col;
};

class Lexer {
public:
    Lexer(const std::string& src);
    std::vector<Token> Tokenize();
private:
    // Implementation details
};