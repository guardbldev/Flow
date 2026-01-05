#pragma once
#include <string>
#include <unordered_map>

// Each entry is a feature—every keyword, every block gets a comment describing its use.
enum class FlowKeyword {
    Var,           // mutable variable
    Let,           // immutable variable
    State,         // reactive UI state
    Func,          // function declaration
    Async,         // async function
    Await,         // await async result
    Return,        // return value
    If,            // conditional
    // ... repeat pattern for ALL 200 features ...
    Websocket,     // websocket integration
    None           // not a keyword
};

static const std::unordered_map<std::string, FlowKeyword> keywordTable = {
    // "var" → FlowKeyword::Var,        // mutable variable
    // ... and so on for EVERY feature (1–200),
    // "websocket" → FlowKeyword::Websocket, // websocket integration
};