#ifndef WEBSOCKETMANAGER_CPP
#define WEBSOCKETMANAGER_CPP
#include "WebsocketManager.h"
#include <app/clusters/switch-server/switch-server.h>
#include <app/clusters/on-off-server/on-off-server.h>
#include <websocket-server/WebSocketServer.h>
#include <string>
#include <sstream>
using namespace std;
char buf[1024];
WebsocketManager::WebsocketManager()
{
    WebsocketManager::instance = this;
    isWebsocketConnected = false;
    
    
}
void WebsocketManager::Send(const char * msg)
{
    if(this->isWebsocketConnected)
        this->mWebSocketServer.Send(msg);
    
}
void WebsocketManager::SendClusterInit(string clusterId, int endpointId)
{
    
    sprintf(buf,"{\"clusterName\":\"%s\",\"endpointId\": %d}", clusterId.c_str(), endpointId);
    if(this->isWebsocketConnected)
    {
        Send(buf);
    }
    else
    {
        this->clusterInits.insert(string(buf));
    }
    
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
    isWebsocketConnected= true;
    printf("\n\nCCCCCCCCCCCCCCC \n OnWebSocketMessageReceived \n\n");

    if(strcmp(msg,"new") == 0)
    {
        set<string>::reverse_iterator itr;
        for (itr = clusterInits.rbegin(); itr != clusterInits.rend(); itr++) 
        {
            //printf("aa= %s\n",(*itr).c_str());
            Send((*itr).c_str());
        }
    }

    return true;
}


void MatterPostAttributeChangeCallback(const chip::app::ConcreteAttributePath & path, uint8_t type, uint16_t size, uint8_t * value)
{
    //bool currentLedState;
    //OnOffServer::Instance().getOnOffValue(1, &currentLedState);
    printf("\n\n\n\n\n ====> MatterPostAttributeChangeCallback endpoint=%d clusterId=%d attribute=%d data=%d \r\n\n\n",path.mEndpointId ,path.mClusterId,path.mAttributeId, (int)value[0]);
    
    //OnOff::Attributes::OnOff::
    //OnOffServer::Instance().setOnOffValue(1,chip::app::Clusters::OnOff::Commands::On::Id,false);

    std::ostringstream sstream;
    
    
    for(int i=0; i < size; i++)
    {
        sstream << (int)value[i];
        if (i < size -1)
            sstream << " ";
    }
    sprintf(buf,"{\"endpointId\":%d,\"clusterId\":%d,\"attributeId\":%d,\"data_int\":%d,\"size\":%d,\"data_raw\":\"%s\" }",path.mEndpointId,path.mClusterId,path.mAttributeId,(int)value[0],size,sstream.str().c_str() );
    WebsocketManager::instance->Send(buf);

}




WebsocketManager* WebsocketManager::instance = nullptr;


void emberAfAirQualityClusterInitCallback(chip::EndpointId endpointId)
{
    printf("\n\n\n\n\n\n CCCCCCCCCCCCCCCCCCCCCCCCCC CCCCCCCCCCCCCCCCCCCC \n\n\n");
    // //VerifyOrDie(endpointId == 1); // this cluster is only enabled for endpoint 1.
    // if(gAirQualityCluster == nullptr)
    // {
    //     chip::BitMask<Feature, uint32_t> airQualityFeatures(Feature::kModerate, Feature::kFair, Feature::kVeryPoor,
    //                                                     Feature::kExtremelyPoor);
    //     gAirQualityCluster = new Instance(endpointId, airQualityFeatures);
    //     gAirQualityCluster->Init();
    // }
    // else
    // {
    //     chip::BitMask<Feature, uint32_t> airQualityFeatures2(Feature::kModerate, Feature::kFair, Feature::kVeryPoor,
    //                                                     Feature::kExtremelyPoor);
    //     Instance* gAirQualityCluster2 = new Instance(endpointId, airQualityFeatures2);
    //     gAirQualityCluster2->Init();
    // }
}
void emberAfOnOffClusterInitCallback(chip::EndpointId endpointId)
{
    printf("\n\n\n\n\n\n DDDDDDDDDDDDDD WWWWWWWWWWWWWW \n\n\n");
    WebsocketManager::instance->SendClusterInit("OnOff",endpointId );
    
}
#endif