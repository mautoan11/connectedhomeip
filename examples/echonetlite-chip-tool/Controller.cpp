#ifndef CONTROLLER_CPP
#define CONTROLLER_CPP
#include "Controller.h"

//#include "commands/common/Commands.h"
// #include "commands/example/ExampleCredentialIssuerCommands.h"

// #include "commands/clusters/SubscriptionsCommands.h"
// #include "commands/delay/Commands.h"
// #include "commands/discover/Commands.h"
// #include "commands/group/Commands.h"
// #include "commands/interactive/Commands.h"
// #include "commands/pairing/Commands.h"
// #include "commands/payload/Commands.h"
// #include "commands/session-management/Commands.h"
// #include "commands/storage/Commands.h"

// #include <zap-generated/cluster/Commands.h>

#include <string>
#include <vector>
#include <json/value.h>
#include <fstream>
#include <json/writer.h>
#include <string>
using namespace std;

void Controller::TestPrint()
{
    printf("\n\nTest Controller OK\n\n");
    //int argc = 5;
    //char* argv[] = { (char*)"./chip-tool", (char*)"onoff", (char*)"toggle",(char*)"1111",(char*)"3" };
    //commands->RunCommand(argc,argv);
    //commands->RunInteractive("this is the world",nullptr, false);
};
void Controller::TestCommand()
{
    int argc = 5;
    char* argv[] = { (char*)"./chip-tool", (char*)"onoff", (char*)"toggle",(char*)"1111",(char*)"3" };
    commands->Run(argc,argv);
    //commands->RunInteractive("this is the world",nullptr, false);
}

void * MyControllingThread(void * context)
{
    Controller *manager = (Controller *)context;

    sleep(2);
    //manager->TestCommand();
    manager->TestPrint();
	while(true) {
		sleep(1);
        
	}
    
    
    return NULL;
}
void Controller::Start()
{
    pthread_t poll_thread2; 
    int res = pthread_create(&poll_thread2, nullptr, MyControllingThread, this);
    if (res)
    {
        printf("Error creating polling thread: %d\n", res);
    }
}

#endif