/**
 *
 *    Copyright (c) 2022 Project CHIP Authors
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

#include "FanControlManager.h"
#include <app-common/zap-generated/attributes/Accessors.h>
#include <platform/internal/CHIPDeviceLayerInternal.h>
#include <system/SystemClock.h>

using namespace chip;
using namespace chip::app;
using namespace chip::app::Clusters::FanControl;
using namespace chip::System::Clock::Literals;

// FanControlManager::FanControlManager()
// {

// }
FanControlManager::FanControlManager(chip::EndpointId endpoint) : Delegate(endpoint)
{

//     //mState = OperationalState::Stall;
//     //SetEndpoint(endpoint);
}
void FanControlManager::Init(EndpointId endpoint)
{

}
// void FanControlManager::HandleLiftMovementTimer(System::Layer * layer, void * aAppState)
// {
    
// }

// void FanControlManager::HandleTiltMovementTimer(System::Layer * layer, void * aAppState)
// {
    
// }

// CHIP_ERROR FanControlManager::HandleMovement(WindowCoveringType type)
// {
//      return CHIP_NO_ERROR;
// }

// CHIP_ERROR FanControlManager::HandleStopMotion()
// {
//     return CHIP_NO_ERROR;
// }


Protocols::InteractionModel::Status FanControlManager::HandleStep(StepDirectionEnum aDirection, bool aWrap, bool aLowestOff)
{
    return (Protocols::InteractionModel::Status)0;
}