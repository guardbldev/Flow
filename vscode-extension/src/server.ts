import {
    createConnection,
    TextDocuments,
    ProposedFeatures,
    CompletionItem, CompletionItemKind,
    Diagnostic, DiagnosticSeverity, InitializeParams, Position, Location, Hover
} from 'vscode-languageserver/node';
import { KEYWORDS, TYPES, UI_ELEMENTS } from './flow_builtins';
import { spawnSync } from 'child_process'; // For bridging to C++ parser

const connection = createConnection(ProposedFeatures.all);
const documents = new TextDocuments();

connection.onInitialize((_params: InitializeParams) => ({
    capabilities: {
        textDocumentSync: documents.syncType,
        completionProvider: { resolveProvider: false },
        hoverProvider: true,
        definitionProvider: true
    }
}));

// === Diagnostics: Leverage C++ parser ===
documents.onDidChangeContent(change => {
    const text = change.document.getText();
    const diagnostics: Diagnostic[] = [];

    // [Option 1] Inline JS: Example parse for 'func' keyword not closed
    if (text.includes("func") && !text.includes("{") && !text.includes(":")) {
        diagnostics.push({
            severity: DiagnosticSeverity.Error,
            range: {
                start: {line: 0, character: 0}, end: {line: 0, character: 4}
            },
            message: "Function declaration missing block",
            source: "flow-lsp"
        });
    }

    // [Option 2] C++ Bridge: Call your flow-parser binary, parse output
    /*
    const parseResult = spawnSync('./flow-parser', [], { input: text, encoding: 'utf8' });
    if (parseResult.stdout) {
        // Example expected: "ERROR: line,col: message"
        parseResult.stdout.split("\n").forEach(line => {
            if (line.startsWith("ERROR:")) {
                const parts = line.split(":");
                diagnostics.push({
                    severity: DiagnosticSeverity.Error,
                    range: {
                        start: {line: parseInt(parts[1]), character: parseInt(parts[2])},
                        end: {line: parseInt(parts[1]), character: parseInt(parts[2]) + 1}
                    },
                    message: parts.slice(3).join(":").trim(),
                    source: "FlowParser"
                });
            }
        });
    }
    */

    connection.sendDiagnostics({ uri: change.document.uri, diagnostics });
});

// === Completion Items ===
connection.onCompletion((params) => {
    // Aggregate completions based on builtins, add context-awareness as needed
    let completions: CompletionItem[] = [];
    KEYWORDS.forEach(kw =>
        completions.push({
            label: kw,
            kind: CompletionItemKind.Keyword,
            detail: "Flow core keyword"
        }));
    TYPES.forEach(tp =>
        completions.push({
            label: tp,
            kind: CompletionItemKind.Class,
            detail: "Flow type"
        }));
    UI_ELEMENTS.forEach(e =>
        completions.push({
            label: e,
            kind: CompletionItemKind.Field,
            detail: "Flow UI element"
        }));
    return completions;
});

// === Jump to definition (stub) ===
connection.onDefinition((params) => {
    // Optionally, hook into your AST or symbol table for navigation:
    // return Location for symbol under cursor
    return null;
});

// === Hover Information (stub) ===
connection.onHover((params) => {
    // Optionally, lookup docs for symbol under cursor
    return { contents: "Flow Language Symbol" };
});

// === Connection to VS Code ===
documents.listen(connection);
connection.listen();