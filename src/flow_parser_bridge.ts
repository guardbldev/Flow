import { spawnSync } from 'child_process';

export function getFlowDiagnostics(code: string) {
    const result = spawnSync('./flow-parser', [], { input: code, encoding: 'utf8' });
    return result.stdout;
}