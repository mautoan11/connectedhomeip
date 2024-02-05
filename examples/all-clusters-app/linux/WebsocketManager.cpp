#ifndef WEBSOCKETMANAGER_CPP
#define WEBSOCKETMANAGER_CPP
#include "WebsocketManager.h"

WebsocketManager::WebsocketManager()
{
    chip::Optional<uint16_t> mPort;
    mWebSocketServer.Run(mPort, this);
}

bool WebsocketManager::OnWebSocketMessageReceived(char * msg)
{
    return true;
}

#endif