#pragma once
#ifndef WEBSOCKETMANAGER_H
#define WEBSOCKETMANAGER_H



#include <websocket-server/WebSocketServer.h>
//#include <WebSocketServer.h>
//#include <./examples/common/websocket-server/WebSocketServer.h>

//#include <app/tests/suites/credentials/TestHarnessDACProvider.h>

class WebsocketManager: public WebSocketServerDelegate
{
    WebsocketManager();
    bool OnWebSocketMessageReceived(char * msg) override;
};




#endif