#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include "flow_ast.h"

// Global & Local State
class FlowStateStore {
public:
    void setGlobal(const std::string& name, int value);
    int getGlobal(const std::string& name) const;

    void setLocal(const std::string& componentId, const std::string& name, int value);
    int getLocal(const std::string& componentId, const std::string& name) const;
private:
    std::unordered_map<std::string, int> globalVars;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> localVars;
};

// Event System
class FlowEventSystem {
public:
    void wire(const std::string& eventName, const std::function<void()>& handler);
    void trigger(const std::string& eventName);
private:
    std::unordered_map<std::string, std::vector<std::function<void()>>> handlers;
};

// Animation System (per node/component)
class FlowAnimationSystem {
public:
    void schedule(const std::string& targetId, const std::string& type, int duration, int delay = 0);
    void tick(); // Advances animation frame/time
private:
    // Data: struct for active animations
};

// Network System
class FlowNetworkSystem {
public:
    void fetch(const std::string& url, const std::function<void(const std::string&)>& callback);
    void websocket(const std::string& url, const std::function<void(const std::string&)>& onMessage);
private:
    // Data: active requests/connections
};

// Platform code hooks (WASM/desktop/mobile)
class FlowPlatformSystem {
public:
    void executePlatformBlock(const ASTNode* node);
    // Extend: per-platform implementations
};

// The main renderer: walks the AST, wiring up everything
class FlowRenderer {
public:
    void renderAST(const ASTNode* root, 
                   FlowStateStore& states,
                   FlowEventSystem& events,
                   FlowAnimationSystem& anim,
                   FlowNetworkSystem& net,
                   FlowPlatformSystem& platform,
                   const std::string& componentId = "");
};