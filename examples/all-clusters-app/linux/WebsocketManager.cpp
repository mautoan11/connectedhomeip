#ifndef WEBSOCKETMANAGER_CPP
#define WEBSOCKETMANAGER_CPP
#include "WebsocketManager.h"
#include <app/clusters/switch-server/switch-server.h>
#include <app/clusters/on-off-server/on-off-server.h>
#include <websocket-server/WebSocketServer.h>

WebsocketManager::WebsocketManager()
{
    // chip::Optional<uint16_t> mPort(9005);
    
    // mWebSocketServer.Run(mPort, this);
}

bool WebsocketManager::OnWebSocketMessageReceived(char * msg)
{
    return true;
}

#endif