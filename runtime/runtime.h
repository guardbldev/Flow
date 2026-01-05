#pragma once
#include <string>
#include <unordered_map>
#include <functional>

class FlowState {
public:
    void set(const std::string& name, int value);
    int get(const std::string& name) const;
    // Reactive notification, etc.
private:
    std::unordered_map<std::string, int> states;
};

class FlowUI {
public:
    void showScreen(const std::string& name);
    void handleEvent(const std::string& widget, const std::string& event);
    // Rendering, layout
};