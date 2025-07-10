
import {
    DebugSession,
    InitializedEvent, TerminatedEvent
} from 'vscode-debugadapter';
import { DebugProtocol } from 'vscode-debugprotocol';

export class SnaskDebugSession extends DebugSession {
    public constructor() {
        super();
    }

    protected initializeRequest(
        response: DebugProtocol.InitializeResponse,
        args: DebugProtocol.InitializeRequestArguments
    ): void {
        console.log('Snask Debugger Initialized');

        response.body = response.body || {};
        response.body.supportsConfigurationDoneRequest = true;

        this.sendResponse(response);
        this.sendEvent(new InitializedEvent());
    }

    protected configurationDoneRequest(
        response: DebugProtocol.ConfigurationDoneResponse,
        args: DebugProtocol.ConfigurationDoneArguments
    ): void {
        super.configurationDoneRequest(response, args);
    }

    protected launchRequest(response: DebugProtocol.LaunchResponse, args: DebugProtocol.LaunchRequestArguments): void {
        console.log('Launch request');
        this.sendEvent(new TerminatedEvent());
    }
}

SnaskDebugSession.run(SnaskDebugSession);
