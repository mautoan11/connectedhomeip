/*
 *
 *    Copyright (c) 2023 Project CHIP Authors
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
#include <operational-state-delegate-impl.h>

using namespace chip;
using namespace chip::app;
using namespace chip::app::Clusters;
using namespace chip::app::Clusters::OperationalState;
using namespace chip::app::Clusters::RvcOperationalState;

CHIP_ERROR GenericOperationalStateDelegateImpl::GetOperationalStateAtIndex(size_t index, GenericOperationalState & operationalState)
{
    if (index >= mOperationalStateList.size())
    {
        return CHIP_ERROR_NOT_FOUND;
    }
    operationalState = mOperationalStateList[index];
    return CHIP_NO_ERROR;
}

CHIP_ERROR GenericOperationalStateDelegateImpl::GetOperationalPhaseAtIndex(size_t index, MutableCharSpan & operationalPhase)
{
    if (index >= mOperationalPhaseList.size())
    {
        return CHIP_ERROR_NOT_FOUND;
    }
    return CopyCharSpanToMutableCharSpan(mOperationalPhaseList[index], operationalPhase);
}

void GenericOperationalStateDelegateImpl::HandlePauseStateCallback(GenericOperationalError & err)
{
    // placeholder implementation
    auto error = GetInstance()->SetOperationalState(to_underlying(OperationalState::OperationalStateEnum::kPaused));
    if (error == CHIP_NO_ERROR)
    {
        err.Set(to_underlying(ErrorStateEnum::kNoError));
    }
    else
    {
        err.Set(to_underlying(ErrorStateEnum::kUnableToCompleteOperation));
    }
}

void GenericOperationalStateDelegateImpl::HandleResumeStateCallback(GenericOperationalError & err)
{
    // placeholder implementation
    auto error = GetInstance()->SetOperationalState(to_underlying(OperationalStateEnum::kRunning));
    if (error == CHIP_NO_ERROR)
    {
        err.Set(to_underlying(ErrorStateEnum::kNoError));
    }
    else
    {
        err.Set(to_underlying(ErrorStateEnum::kUnableToCompleteOperation));
    }
}

void GenericOperationalStateDelegateImpl::HandleStartStateCallback(GenericOperationalError & err)
{
    // placeholder implementation
    auto error = GetInstance()->SetOperationalState(to_underlying(OperationalStateEnum::kRunning));
    if (error == CHIP_NO_ERROR)
    {
        err.Set(to_underlying(ErrorStateEnum::kNoError));
    }
    else
    {
        err.Set(to_underlying(ErrorStateEnum::kUnableToCompleteOperation));
    }
}

void GenericOperationalStateDelegateImpl::HandleStopStateCallback(GenericOperationalError & err)
{
    // placeholder implementation
    auto error = GetInstance()->SetOperationalState(to_underlying(OperationalStateEnum::kStopped));
    if (error == CHIP_NO_ERROR)
    {
        err.Set(to_underlying(ErrorStateEnum::kNoError));
    }
    else
    {
        err.Set(to_underlying(ErrorStateEnum::kUnableToCompleteOperation));
    }
}

// Init Operational State cluster

static OperationalState::Instance * gOperationalStateInstance = nullptr;
static OperationalStateDelegate * gOperationalStateDelegate   = nullptr;

void OperationalState::Shutdown()
{
    if (gOperationalStateInstance != nullptr)
    {
        delete gOperationalStateInstance;
        gOperationalStateInstance = nullptr;
    }
    if (gOperationalStateDelegate != nullptr)
    {
        delete gOperationalStateDelegate;
        gOperationalStateDelegate = nullptr;
    }
}

void emberAfOperationalStateClusterInitCallback(chip::EndpointId endpointId)
{
    
    if(gOperationalStateInstance == nullptr)
    {
    gOperationalStateDelegate           = new OperationalStateDelegate;
    EndpointId operationalStateEndpoint = endpointId;
    gOperationalStateInstance           = new OperationalState::Instance(gOperationalStateDelegate, operationalStateEndpoint);

    gOperationalStateInstance->SetOperationalState(to_underlying(OperationalState::OperationalStateEnum::kStopped));

    gOperationalStateInstance->Init();
    }
    else
    {
        OperationalStateDelegate* gOperationalStateDelegate2           = new OperationalStateDelegate;
        EndpointId operationalStateEndpoint2 = endpointId;
     OperationalState::Instance* gOperationalStateInstance2           = new OperationalState::Instance(gOperationalStateDelegate2, operationalStateEndpoint2);

     gOperationalStateInstance2->SetOperationalState(to_underlying(OperationalState::OperationalStateEnum::kStopped));

     gOperationalStateInstance2->Init();
    }
}

// Init RVC Operational State cluster

static OperationalState::Instance * gRvcOperationalStateInstance  = nullptr;
static RvcOperationalStateDelegate * gRvcOperationalStateDelegate = nullptr;

void RvcOperationalState::Shutdown()
{
    if (gRvcOperationalStateInstance != nullptr)
    {
        delete gRvcOperationalStateInstance;
        gRvcOperationalStateInstance = nullptr;
    }
    if (gRvcOperationalStateDelegate != nullptr)
    {
        delete gRvcOperationalStateDelegate;
        gRvcOperationalStateDelegate = nullptr;
    }
}

void emberAfRvcOperationalStateClusterInitCallback(chip::EndpointId endpointId)
{
    
    if(gRvcOperationalStateInstance == nullptr)
    {
        gRvcOperationalStateDelegate        = new RvcOperationalStateDelegate;
        EndpointId operationalStateEndpoint = endpointId;
        gRvcOperationalStateInstance        = new RvcOperationalState::Instance(gRvcOperationalStateDelegate, operationalStateEndpoint);
        gRvcOperationalStateInstance->SetOperationalState(to_underlying(OperationalState::OperationalStateEnum::kStopped));
        gRvcOperationalStateInstance->Init();
    }
    else
    {
        RvcOperationalStateDelegate* gRvcOperationalStateDelegate2        = new RvcOperationalStateDelegate;
        EndpointId operationalStateEndpoint2 = endpointId;
        RvcOperationalState::Instance* gRvcOperationalStateInstance2        = new RvcOperationalState::Instance(gRvcOperationalStateDelegate2, operationalStateEndpoint2);
        gRvcOperationalStateInstance2->SetOperationalState(to_underlying(OperationalState::OperationalStateEnum::kStopped));
        gRvcOperationalStateInstance2->Init();
    }
}
