#include "flow_lexer.h"
#include <cctype>

char Lexer::peek() { return (pos < src.size()) ? src[pos] : '\0'; }
char Lexer::get() { char c = peek(); if(c == '\n'){ line++; col=1; } else { col++; } pos++; return c; }
bool Lexer::eof() { return pos >= src.size(); }

Lexer::Lexer(const std::string& _src) : src(_src) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (!eof()) {
        Token tk = nextToken();
        if (tk.kind != TokenKind::Unknown)
            tokens.push_back(tk);
    }
    tokens.push_back({TokenKind::Eof, "", line, col});
    return tokens;
}

Token Lexer::nextToken() {
    while (!eof() && std::isspace(peek())) get();
    if (eof()) return {TokenKind::Eof, "", line, col};
    int tline = line, tcol = col;
    char c = peek();
    if (std::isalpha(c) || c == '_') {
        std::string word;
        while (!eof() && (std::isalnum(peek()) || peek() == '_' || peek() == ' ')) word += get();
        auto it = keywordTable.find(word);
        if (it != keywordTable.end())
            return {TokenKind::Keyword, word, tline, tcol, it->second};
        return {TokenKind::Identifier, word, tline, tcol};
    }
    if (std::isdigit(c)) {
        std::string num;
        while (!eof() && std::isdigit(peek())) num += get();
        return {TokenKind::Number, num, tline, tcol};
    }
    if (c == '"') {
        get();
        std::string val;
        while (!eof() && peek() != '"') val += get();
        get();
        return {TokenKind::String, val, tline, tcol};
    }
    if (std::ispunct(c)) {
        std::string sym;
        sym += get();
        return {TokenKind::Symbol, sym, tline, tcol};
    }
    get();
    return {TokenKind::Unknown, "", tline, tcol};
}