#include "flow_tokenizer.h"
#include <cctype>

char Tokenizer::peek() { return (pos < src.size()) ? src[pos] : '\0'; }
char Tokenizer::get() { char c = peek(); if(c == '\n'){ line++; col=1; } else { col++; } pos++; return c; }
bool Tokenizer::eof() { return pos >= src.size(); }

Tokenizer::Tokenizer(const std::string& _src) : src(_src) {}

std::vector<Token> Tokenizer::tokenize() {
    std::vector<Token> tokens;
    while (!eof()) {
        Token tk = nextToken();
        if (tk.kind != TokenKind::Unknown)
            tokens.push_back(tk);
    }
    Token eofTk = {TokenKind::Eof, "", line, col};
    tokens.push_back(eofTk);
    return tokens;
}

Token Tokenizer::nextToken() {
    // Skipping whitespace, simple string/identifier/numbers for brevity
    while (!eof() && std::isspace(peek())) get();
    if (eof()) return {TokenKind::Eof, "", line, col};

    int tline = line, tcol = col;
    char c = peek();
    // Keywords/types/identifiers
    if (std::isalpha(c) || c == '_') {
        std::string word;
        while (!eof() && (std::isalnum(peek()) || peek() == '_')) word += get();
        if (keywordTable.count(word))
            return {TokenKind::Keyword, word, tline, tcol, keywordTable.at(word), FlowType::None};
        if (typeTable.count(word))
            return {TokenKind::Type, word, tline, tcol, FlowKeyword::None, typeTable.at(word)};
        return {TokenKind::Identifier, word, tline, tcol};
    }
    // Numbers
    if (std::isdigit(c)) {
        std::string num;
        while (!eof() && std::isdigit(peek())) num += get();
        return {TokenKind::Number, num, tline, tcol};
    }
    // Strings
    if (c == '"') {
        get(); // "
        std::string val;
        while (!eof() && peek() != '"') val += get();
        get(); // closing "
        return {TokenKind::String, val, tline, tcol};
    }
    // Symbols
    if (std::ispunct(c)) {
        std::string sym;
        sym += get();
        return {TokenKind::Symbol, sym, tline, tcol};
    }
    // Unknown
    get();
    return {TokenKind::Unknown, "", tline, tcol};
}