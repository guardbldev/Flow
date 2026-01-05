#pragma once
#include <string>
#include <vector>
#include "flow_keywords.h"

class FlowTypeSystem {
public:
    static bool ValidateType(const TypeInfo& lhs, const TypeInfo& rhs);
    static std::string TypeToString(const TypeInfo& info);
    // Advanced features: generics, optional, platform-specific
};