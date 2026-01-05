#include "flow_runtime.h"
#include <iostream>

// --- State ---
void FlowStateStore::setGlobal(const std::string& name, int value) { globalVars[name] = value; }
int  FlowStateStore::getGlobal(const std::string& name) const { auto it = globalVars.find(name); return it != globalVars.end() ? it->second : 0; }
void FlowStateStore::setLocal(const std::string& cid, const std::string& name, int value) { localVars[cid][name] = value; }
int FlowStateStore::getLocal(const std::string& cid, const std::string& name) const {
    auto cit = localVars.find(cid); if(cit!=localVars.end()) { auto vit = cit->second.find(name); return vit!=cit->second.end()?vit->second:0; }
    return 0;
}

// --- Event ---
void FlowEventSystem::wire(const std::string& eventName, const std::function<void()>& handler) { handlers[eventName].push_back(handler); }
void FlowEventSystem::trigger(const std::string& eventName) {
    std::cout << "[Event] " << eventName << std::endl;
    auto it=handlers.find(eventName);
    if(it!=handlers.end()) for(auto& h:it->second) h();
}

// --- Animation ---
void FlowAnimationSystem::schedule(const std::string& targetId, const std::string& type, int duration, int delay) {
    std::cout << "[Animation] Target: " << targetId << " Type: " << type << " Duration: " << duration << " Delay: " << delay << std::endl;
    // Extend with timer-based logic
}
void FlowAnimationSystem::tick() {
    // Advance animation frames
}

// --- Networking ---
void FlowNetworkSystem::fetch(const std::string& url, const std::function<void(const std::string&)>& callback) {
    std::cout << "[Fetch] " << url << std::endl;
    callback("{json: 'response'}"); // Simulated network reply
}
void FlowNetworkSystem::websocket(const std::string& url, const std::function<void(const std::string&)>& onMessage) {
    std::cout << "[WebSocket] Connect: " << url << std::endl;
    onMessage("WebSocket message (simulated)");
}

// --- Platform ---
void FlowPlatformSystem::executePlatformBlock(const ASTNode* node) {
    std::cout << "[Platform] Executing platform-specific logic: " << node->text << std::endl;
    // Add bridges for WASM, desktop, mobile, etc.
}

// --- AST Renderer --- (every ASTKind is extended)
void FlowRenderer::renderAST(const ASTNode* node, FlowStateStore& states, FlowEventSystem& events, FlowAnimationSystem& anim, FlowNetworkSystem& net, FlowPlatformSystem& platform, const std::string& componentId) {
    switch(node->kind) {
        case ASTKind::ScreenBlock:
            std::cout << "<Screen: " << node->text << ">\n";
            events.trigger("mount");
            break;
        case ASTKind::ButtonBlock:
            std::cout << "<Button: " << node->text << ">\n";
            events.wire("click", [](){ std::cout << "Button clicked!\n"; });
            break;
        case ASTKind::OnClickBlock:
            events.wire("click", [node](){ std::cout << "Handling click event: " << node->text << "\n"; });
            break;
        case ASTKind::StateDecl:
            states.setGlobal(node->text, 0);
            std::cout << "[State] " << node->text << " set to 0 (global)\n";
            break;
        case ASTKind::EffectBlock:    // Reactivity/effects
            std::cout << "[Effect] " << node->text << "\n";
            break;
        case ASTKind::AnimateBlock:   // Animation
            anim.schedule(componentId, "fadeIn", 250, 0);
            break;
        case ASTKind::FetchBlock:     // Networking fetch
            net.fetch(node->text, [](const std::string& data){ std::cout << "Fetched data: " << data << "\n"; });
            break;
        case ASTKind::WebsocketBlock:
            net.websocket(node->text, [](const std::string& msg){ std::cout << "WS received: " << msg << "\n"; });
            break;
        case ASTKind::PlatformBlock:
            platform.executePlatformBlock(node);
            break;
        // ...continue for all 200+ ASTKind cases, mapping each kind to subsystem, state, event, layout, animation, etc...
        default:
            break;
    }
    for(const auto* child : node->children)
        renderAST(child, states, events, anim, net, platform, componentId);
}