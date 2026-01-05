#include "flow_tokenizer.h"
#include "flow_parser.h"
#include "flow_runtime.h"
#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
    if(argc < 2) { std::cerr << "Usage: flow <file.flow>\n"; return 1; }
    std::ifstream ifs(argv[1]);
    std::string src((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    Tokenizer lexer(src);
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    ASTNode* ast = parser.parse();
    parser.dumpAST(ast);

    FlowStateStore states;
    FlowEventSystem events;
    FlowAnimationSystem anim;
    FlowNetworkSystem net;
    FlowPlatformSystem platform;

    FlowRenderer renderer;
    renderer.renderAST(ast, states, events, anim, net, platform);

    delete ast;
    return 0;
}