#pragma once
#include <string>
#include <unordered_map>

enum class FlowKeyword {
    Var, Let, State, Func, Async, Await, Return,
    If, Else, For, While, Break, Continue, Try, Catch, Throw,
    Import, Export, Unsafe, Platform,
    None
};

static const std::unordered_map<std::string, FlowKeyword> keywordTable = {
    {"var", FlowKeyword::Var},
    {"let", FlowKeyword::Let},
    {"state", FlowKeyword::State},
    {"func", FlowKeyword::Func},
    {"async", FlowKeyword::Async},
    {"await", FlowKeyword::Await},
    {"return", FlowKeyword::Return},
    {"if", FlowKeyword::If},
    {"else", FlowKeyword::Else},
    {"for", FlowKeyword::For},
    {"while", FlowKeyword::While},
    {"break", FlowKeyword::Break},
    {"continue", FlowKeyword::Continue},
    {"try", FlowKeyword::Try},
    {"catch", FlowKeyword::Catch},
    {"throw", FlowKeyword::Throw},
    {"import", FlowKeyword::Import},
    {"export", FlowKeyword::Export},
    {"unsafe", FlowKeyword::Unsafe},
    {"platform", FlowKeyword::Platform}
};