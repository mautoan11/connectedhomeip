#pragma once
#ifndef WEBSOCKETMANAGER_H
#define WEBSOCKETMANAGER_H

#include <websocket-server/WebSocketServer.h>

class WebsocketManager: public WebSocketServerDelegate
{
    //chip::Optional<uint16_t> mPort;
    WebSocketServer mWebSocketServer;
    public:
    WebsocketManager();
    bool OnWebSocketMessageReceived(char * msg) override;
};




#endif