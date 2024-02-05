/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include "AppMain.h"
#include "AppOptions.h"
#include "binding-handler.h"
//#include "WebsocketManager.h"
using namespace chip;
using namespace chip::app::Clusters;
// Network commissioning
namespace {
constexpr chip::EndpointId kNetworkCommissioningEndpointSecondary = 0xFFFE;
} // anonymous namespace


// void MatterPostAttributeChangeCallback(const chip::app::ConcreteAttributePath & path, uint8_t type, uint16_t size, uint8_t * value)
// {
//     printf("\n\n\n\n\n ====> MatterPostAttributeChangeCallback endpoint=%d clusterId=%d attribute=%d data=%d\r\n\n\n",path.mEndpointId ,path.mClusterId,path.mAttributeId, (int)value[0]);
    
//     //OnOff::Attributes::OnOff::
//     //OnOffServer::Instance().setOnOffValue(0,chip::app::Clusters::OnOff::Commands::On::Id,false);
//     return;
// }



EmberAfStatus emberAfExternalAttributeReadCallback(EndpointId endpoint, ClusterId clusterId,
                                                   EmberAfAttributeMetadata * attributeMetadata, uint16_t manufacturerCode,
                                                   uint8_t * buffer, uint16_t maxReadLength, int32_t index)
{
    printf("\n\n\n\n\n &&&&&&&> emberAfExternalAttributeReadCallback endpoint=%d clusterId=%d data=%d\r\n\n\n",endpoint,clusterId,(int)buffer[0]);
    return EMBER_ZCL_STATUS_SUCCESS;
}
EmberAfStatus emberAfExternalAttributeReadCallback(EndpointId endpoint, ClusterId clusterId,
                                                   const EmberAfAttributeMetadata * attributeMetadata, uint8_t * buffer,
                                                   uint16_t maxReadLength)
{
    printf("\n\n\n\n\n &&&&&&&2> emberAfExternalAttributeReadCallback endpoint=%d clusterId=%d data=%d\r\n\n\n",endpoint,clusterId,(int)buffer[0]);
    return EMBER_ZCL_STATUS_SUCCESS;
}

EmberAfStatus emberAfExternalAttributeWriteCallback(EndpointId endpoint, ClusterId clusterId,
                                                    const EmberAfAttributeMetadata * attributeMetadata, uint8_t * buffer)
{
   printf("\n\n\n\n\n 8888888> emberAfExternalAttributeWriteCallback endpoint=%d clusterId=%d data=%d\r\n\n\n",endpoint,clusterId,(int)buffer[0]);
    return EMBER_ZCL_STATUS_SUCCESS;
}



int main(int argc, char * argv[])
{
    VerifyOrDie(
        ChipLinuxAppInit(argc, argv, AppOptions::GetOptions(), chip::MakeOptional(kNetworkCommissioningEndpointSecondary)) == 0);
    VerifyOrDie(InitBindingHandlers() == CHIP_NO_ERROR);

    LinuxDeviceOptions::GetInstance().dacProvider = AppOptions::GetDACProvider();



    ChipLinuxAppMainLoop();

    return 0;
}
