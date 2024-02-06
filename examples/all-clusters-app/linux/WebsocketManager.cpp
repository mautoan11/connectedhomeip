#ifndef WEBSOCKETMANAGER_CPP
#define WEBSOCKETMANAGER_CPP
#include "WebsocketManager.h"
#include <app/clusters/switch-server/switch-server.h>
#include <app/clusters/on-off-server/on-off-server.h>
#include <websocket-server/WebSocketServer.h>

WebsocketManager::WebsocketManager()
{
    WebsocketManager::instance = this;
    
    
    
}
void * MySocketThread(void * context)
{
    WebsocketManager *manager = (WebsocketManager *)context;
    chip::Optional<uint16_t> mPort(9005);
    manager->mWebSocketServer.Run(mPort, manager);

     return NULL;
}
void WebsocketManager::Start()
{
    pthread_t poll_thread2; 
    int res = pthread_create(&poll_thread2, nullptr, MySocketThread, this);
    if (res)
    {
        printf("Error creating polling thread: %d\n", res);
    }
}
bool WebsocketManager::OnWebSocketMessageReceived(char * msg)
{
    printf("\n\nCCCCCCCCCCCCCCC \n OnWebSocketMessageReceived \n\n");
    return true;
}

WebsocketManager* WebsocketManager::instance = nullptr;
#endif