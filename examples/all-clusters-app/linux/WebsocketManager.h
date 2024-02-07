#pragma once
#ifndef WEBSOCKETMANAGER_H
#define WEBSOCKETMANAGER_H



#include <websocket-server/WebSocketServer.h>
#include <string>
#include <set>

class WebsocketManager: public WebSocketServerDelegate
{

    private:
        //char buf[1024];
    public:
    std::set<std::string> clusterInits;

    bool isWebsocketConnected;
    WebSocketServer mWebSocketServer;
    static WebsocketManager* instance;
    
    WebsocketManager();
    bool OnWebSocketMessageReceived(char * msg) override;
    void Start();
    void Send(const char * msg);
    void SendClusterInit(int clusterId, int endpointId);

};




#endif