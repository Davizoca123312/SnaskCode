"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.SnaskDebugSession = void 0;
const vscode_debugadapter_1 = require("vscode-debugadapter");
class SnaskDebugSession extends vscode_debugadapter_1.DebugSession {
    constructor() {
        super();
    }
    initializeRequest(response, args) {
        console.log('Snask Debugger Initialized');
        response.body = response.body || {};
        response.body.supportsConfigurationDoneRequest = true;
        this.sendResponse(response);
        this.sendEvent(new vscode_debugadapter_1.InitializedEvent());
    }
    configurationDoneRequest(response, args) {
        super.configurationDoneRequest(response, args);
    }
    launchRequest(response, args) {
        console.log('Launch request');
        this.sendEvent(new vscode_debugadapter_1.TerminatedEvent());
    }
}
exports.SnaskDebugSession = SnaskDebugSession;
SnaskDebugSession.run(SnaskDebugSession);
//# sourceMappingURL=snaskDebug.js.map