#pragma once
#include <string>
#include <unordered_map>

enum class FlowType {
    Int, Float, Bool, String, Char, Null, Any, Void, List, Map, Set, Tuple,
    Optional, Result, Range, Time, Date, URL, JSON, Regex, None
};

static const std::unordered_map<std::string, FlowType> typeTable = {
    {"Int", FlowType::Int},
    {"Float", FlowType::Float},
    {"Bool", FlowType::Bool},
    {"String", FlowType::String},
    {"Char", FlowType::Char},
    {"Null", FlowType::Null},
    {"Any", FlowType::Any},
    {"Void", FlowType::Void},
    {"List", FlowType::List},
    {"Map", FlowType::Map},
    {"Set", FlowType::Set},
    {"Tuple", FlowType::Tuple},
    {"Optional", FlowType::Optional},
    {"Result", FlowType::Result},
    {"Range", FlowType::Range},
    {"Time", FlowType::Time},
    {"Date", FlowType::Date},
    {"URL", FlowType::URL},
    {"JSON", FlowType::JSON},
    {"Regex", FlowType::Regex}
};