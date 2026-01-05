import * as path from 'path';
import * as vscode from 'vscode';
import { LanguageClient, LanguageClientOptions, ServerOptions, TransportKind } from 'vscode-languageclient/node';

export function activate(context: vscode.ExtensionContext) {
    let serverModule = context.asAbsolutePath(path.join('out', 'server.js'));
    let serverOptions: ServerOptions = {
        run:   { module: serverModule, transport: TransportKind.ipc },
        debug: { module: serverModule, transport: TransportKind.ipc, options: { execArgv: ['--nolazy', '--inspect=6009'] } }
    };
    let clientOptions: LanguageClientOptions = {
        documentSelector: [{ scheme: 'file', language: 'flow' }]
    };
    let client = new LanguageClient("flow-lsp", "Flow Language Server", serverOptions, clientOptions);
    context.subscriptions.push(client.start());
}
export function deactivate() {}