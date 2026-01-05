# 🌊 Flow Language Support for VS Code

**Advanced syntax highlighting, run tasks, and roadmap for full LSP, error squiggles, and autocompletion.**

## Features

- Syntax highlighting for ALL Flow language features (`.fl` files)
- Run Flow file from VS Code command palette
- Bracket, string, and comment support
- Foundation for LSP: completions, error diagnostics, jump-to-definition
- Modern extension structure: TypeScript + JSON grammars

## Getting Started

1. Clone this repo:
    ```sh
    git clone https://github.com/example/flow-vscode.git
    cd flow-vscode
    npm install
    ```

2. Build/Run the extension:
    ```sh
    npm run compile
    code .
    F5 # to launch into your VS Code test window
    ```

## Running Flow Files

Open a `.fl` file and run:
- `Ctrl+Shift+P > Run Flow File`
- See syntax highlighting and language config

## Roadmap

- [x] Syntax Highlighting
- [x] Bracket, comment, string rules
- [x] "Run File" Command
- [ ] Autocomplete & Snippets
- [ ] Error squiggles (LSP integration)
- [ ] Docs hover and jump to symbol
- [ ] Debugger integration

## Contributing

- PRs and issues welcome!
- See [src/extension.ts](src/extension.ts) for the extension entrypoint.

## License

MIT (see LICENSE)