#ifndef WEBSOCKETMANAGER_CPP
#define WEBSOCKETMANAGER_CPP
#include "WebsocketManager.h"
#include <app/clusters/switch-server/switch-server.h>
#include <app/clusters/on-off-server/on-off-server.h>
#include <app/clusters/level-control/level-control.h>
#include <websocket-server/WebSocketServer.h>
#include <string>
#include <sstream>
#include <json/value.h>
#include <json/reader.h>
#include <platform/CHIPDeviceLayer.h>
#include <app-common/zap-generated/attributes/Accessors.h>
#include <app-common/zap-generated/ids/Clusters.h>

using namespace std;
using namespace chip;
using namespace chip::app::Clusters;
char buf[1024];
//char buf_dataraw[128];
WebsocketManager* WebsocketManager::instance = nullptr;
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
void WebsocketManager::SendClusterInit(int clusterId, int endpointId)
{
    
    sprintf(buf,"{\"clusterId\":%d,\"endpointId\": %d}", clusterId, endpointId);
    this->clusterInits.insert(string(buf));
    if(this->isWebsocketConnected)
    {
        Send(buf);
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
    printf("OnWebSocketMessageReceived: %s \n\n",msg);

    if(strcmp(msg,"new") == 0)
    {
        set<string>::reverse_iterator itr;
        for (itr = clusterInits.rbegin(); itr != clusterInits.rend(); itr++) 
        {
            //printf("aa= %s\n",(*itr).c_str());
            Send((*itr).c_str());
        }
    }
    else
    {
        Json::Value root;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse( msg, root );
        if ( !parsingSuccessful )printf("Error parsing the string");
        else
        {
            if(strcmp(root["action"].asString().c_str(),"get")==0)
            {
                //printf("\nget\n");
                int endpointId = root["endpointId"].asInt();
                int clusterId = root["clusterId"].asInt();
                this->GetClusterValue(endpointId,clusterId);
            } else if(strcmp(root["action"].asString().c_str(),"set")==0)
            {
                int endpointId = root["endpointId"].asInt();
                int clusterId = root["clusterId"].asInt();
                int attributeId = root["attributeId"].asInt();
                this->SetClusterValue(endpointId,clusterId,attributeId,root["value"] );

            }
            else printf("\nERROR\n");

        }
    }

    return true;
}
void WebsocketManager::SetClusterValue(int endpointId,int clusterId, int attributeId,Json::Value value )
{
    bool valueBool;
    uint valueInt;
    LevelControl::Commands::MoveToLevel::DecodableType data;
    switch(clusterId)
    {
        case 6:
            switch (attributeId)
            {
                case 0:
                    printf("aa\n");
                    valueBool = value.asBool();
                    printf("bb\n");
                    chip::DeviceLayer::PlatformMgr().LockChipStack();
                    OnOffServer::Instance().setOnOffValue((EndpointId)endpointId,valueBool==true?chip::app::Clusters::OnOff::Commands::On::Id:chip::app::Clusters::OnOff::Commands::Off::Id,false);
                    chip::DeviceLayer::PlatformMgr().UnlockChipStack();
                break;
                default: printf("\n[NOT IMPLEMENTED ERROR 2] NOT SUPPORT clusterId=%d attributeId=%d\n\n", clusterId,attributeId);break;
            }
            
        break;
        case 8:
            
            switch (attributeId)
            {
            case 0:
                    valueInt = value.asUInt();
                    chip::DeviceLayer::PlatformMgr().LockChipStack();
                    data.level = (unsigned char)valueInt;
                    data.optionsMask.Set(LevelControl::OptionsBitmap::kExecuteIfOff);
                    data.optionsOverride.Set(LevelControl::OptionsBitmap::kExecuteIfOff);
                    LevelControlServer::MoveToLevel((EndpointId)endpointId, data);
                    chip::DeviceLayer::PlatformMgr().UnlockChipStack();
            break;
            default: printf("\n[NOT IMPLEMENTED ERROR 2] NOT SUPPORT clusterId=%d attributeId=%d\n\n", clusterId,attributeId);break;
            }
        break;
        case 1026:
            switch (attributeId)
                {
                case 0:
                    valueInt = value.asUInt();
                    chip::DeviceLayer::PlatformMgr().LockChipStack();
                    chip::app::Clusters::TemperatureMeasurement::Attributes::MeasuredValue::Set((EndpointId)endpointId,  int16_t(valueInt));
                    chip::DeviceLayer::PlatformMgr().UnlockChipStack();
                break;
                case 1:
                    valueInt = value.asUInt();
                    chip::DeviceLayer::PlatformMgr().LockChipStack();
                    chip::app::Clusters::TemperatureMeasurement::Attributes::MinMeasuredValue::Set((EndpointId)endpointId,  int16_t(valueInt));
                    chip::DeviceLayer::PlatformMgr().UnlockChipStack();
                break;
                case 2:
                    valueInt = value.asUInt();
                    chip::DeviceLayer::PlatformMgr().LockChipStack();
                    chip::app::Clusters::TemperatureMeasurement::Attributes::MaxMeasuredValue::Set((EndpointId)endpointId,  int16_t(valueInt));
                    chip::DeviceLayer::PlatformMgr().UnlockChipStack();
                break;
                default: printf("\n[NOT IMPLEMENTED ERROR 2] NOT SUPPORT clusterId=%d attributeId=%d\n\n", clusterId,attributeId);break;
                }

           
        break;
        default:
            printf("\n[NOT IMPLEMENTED ERROR] NOT SUPPORT clusterId=%d attributeId=%d\n\n", clusterId,attributeId);
        break;
    }
}
void WebsocketManager::GetClusterValue(int endpointId,int clusterId)
{
    chip::EndpointId endpointid = (chip::EndpointId)endpointId;
    int attributeId =0;
    int size=1;
    string raw ="";
    string data_int_str = "0";
    chip::app::DataModel::Nullable<int16_t> measuredValue;
    ///printf("ZZZZZZZZZZZZZZ %d %d\n",endpointId,clusterId);
    switch(clusterId)
    {
        case 6:
            bool currentLedState;
            chip::DeviceLayer::PlatformMgr().LockChipStack();
            OnOffServer::Instance().getOnOffValue(endpointid, &currentLedState);
            chip::DeviceLayer::PlatformMgr().UnlockChipStack();
            attributeId =0;
            data_int_str = currentLedState?"1":"0";
            this->SendAttributeValue(endpointId,clusterId,attributeId, data_int_str,size, raw );
        break;
        //case 8:
            // chip::DeviceLayer::PlatformMgr().LockChipStack();
            // LevelControlServer::Instance().getl getOnOffValue(endpointid, &currentLedState);
            // chip::DeviceLayer::PlatformMgr().UnlockChipStack();
        //break;
        //case 1026: //temperator
            //chip::app::Clusters::TemperatureMeasurement::Attributes::MeasuredValue::Set((EndpointId)endpointId,  int16_t(valueInt));
            // chip::DeviceLayer::PlatformMgr().LockChipStack();
            // chip::app::Clusters::TemperatureMeasurement::Attributes::MeasuredValue::Get((EndpointId)endpointId,measuredValue);
            // chip::DeviceLayer::PlatformMgr().UnlockChipStack();
            // this->SendAttributeValue(endpointId,clusterId,0, measuredValue.Value(),0, 0 );

            // chip::DeviceLayer::PlatformMgr().LockChipStack();
            // chip::app::Clusters::TemperatureMeasurement::Attributes::MinMeasuredValue::Get((EndpointId)endpointId,measuredValue);
            // chip::DeviceLayer::PlatformMgr().UnlockChipStack();
            // this->SendAttributeValue(endpointId,clusterId,1, measuredValue.Value(),0, 0 );

            // chip::DeviceLayer::PlatformMgr().LockChipStack();
            // chip::app::Clusters::TemperatureMeasurement::Attributes::MaxMeasuredValue::Get((EndpointId)endpointId,measuredValue);
            // chip::DeviceLayer::PlatformMgr().UnlockChipStack();
            // this->SendAttributeValue(endpointId,clusterId,2, measuredValue.Value(),0, 0 );


        //break;
        default:
            printf("\n[NOT IMPLEMENTED ERROR (GET)] NOT SUPPORT clusterId=%d endpointId=%d\n\n", clusterId,endpointId);
            return;
        break;


    }
}

void WebsocketManager::SendAttributeValue(int endpointId,int clusterId,int attributeId, int data_int, int size, std::string data_raw)
{
    sprintf(buf,"{\"endpointId\":%d,\"clusterId\":%d,\"attributeId\":%d,\"data_int\":%d,\"size\":%d,\"data_raw\":\"%s\" }",
    endpointId,
    clusterId,
    attributeId,
    data_int,
    size,
    data_raw.c_str() );
    WebsocketManager::instance->Send(buf);
}
void WebsocketManager::SendAttributeValue(int endpointId,int clusterId,int attributeId, std::string data_int, int size, std::string data_raw)
{
sprintf(buf,"{\"endpointId\":%d,\"clusterId\":%d,\"attributeId\":%d,\"data_int\":%s,\"size\":%d,\"data_raw\":\"%s\" }",
    endpointId,
    clusterId,
    attributeId,
    data_int.c_str(),
    size,
    data_raw.c_str() );
    WebsocketManager::instance->Send(buf);
}

void MatterPostAttributeChangeCallback(const chip::app::ConcreteAttributePath & path, uint8_t type, uint16_t size, uint8_t * value)
{
    printf("\n\n\n\n\n ====> MatterPostAttributeChangeCallback endpoint=%d clusterId=%d attribute=%d data=%d \n",path.mEndpointId ,path.mClusterId,path.mAttributeId, (int)value[0]);
    std::ostringstream sstream;
    for(int i=0; i < size; i++)
    {
        sstream << (int)value[i];
        if (i < size -1)
            sstream << " ";
    }
    sprintf(buf,"{\"endpointId\":%d,\"clusterId\":%d,\"attributeId\":%d,\"data_int\":%d,\"size\":%d,\"data_raw\":\"%s\" }",path.mEndpointId,path.mClusterId,path.mAttributeId,(int)value[0],size,sstream.str().c_str() );
    printf("Sending: %s \n",buf);
    WebsocketManager::instance->Send(buf);

}







void emberAfAirQualityClusterInitCallback(chip::EndpointId endpointId)
{
    printf("\n\n\n\n\n\n CCCCCCCCCCCCCCCCCCCCCCCCCC CCCCCCCCCCCCCCCCCCCC \n\n\n");
}
void emberAfOnOffClusterInitCallback(chip::EndpointId endpointId)
{
    printf("\n\n\n\n\n\n DDDDDDDDDDDDDD WWWWWWWWWWWWWW \n\n\n");
    WebsocketManager::instance->SendClusterInit(6,endpointId );
}
void emberAfLevelControlClusterInitCallback(chip::EndpointId endpointId)
{
    printf("\n\n\n\n\n\n DDDDDDDDDDDDDD emberAfLevelControlClusterInitCallback WWWWWWWWWWWWWW \n\n\n");
    WebsocketManager::instance->SendClusterInit(8,endpointId );
}
void emberAfTemperatureMeasurementClusterInitCallback(chip::EndpointId endpointId)
{
    printf("\n\n\n\n\n\n DDDDDDDDDDDDDD emberAfLevelControlClusterInitCallback WWWWWWWWWWWWWW \n\n\n");
    WebsocketManager::instance->SendClusterInit(0x0402,endpointId );
}


#endif