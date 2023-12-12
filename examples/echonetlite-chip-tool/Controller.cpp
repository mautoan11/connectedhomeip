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

#include <stdio.h>
#include <string>
#include <vector>
#include <json/value.h>
#include <fstream>
#include <json/writer.h>
#include <string>
#include <iostream>
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
    //char buf[256];
    // char* arg0 = (char*)"./chip-tool";
    // char* arg1 = (char*)"onoff";
    // char* arg2 = (char*)"toggle";
    // char* arg3 = (char*)"1111";
    // char* arg4 = (char*)"3";
    // char* argv[] = {arg0, arg1, arg2, arg3, arg4};
    // char* argv2[] = {arg1, arg2, arg3, arg4};
    

    sleep(1);
    //manager->TestCommand();
    // manager->TestPrint();
	// while(true) {
	// 	sleep(1);
    //     //printf("testing thread\n");
	// }
    //bool isStorageInited = false;
    //std::string line;
    int status;
    while (true) {
        //getline(std::cin, line);

        sleep(5);
        
        char *command = (char*)(malloc(sizeof(char) * 128));
        sprintf(command,"%s","onoff toggle 1111 3");
        //manager->commands->RunInteractive(command, GetStorageDirectory(), NeedsOperationalAdvertising());
        status = manager->RunCommand(command);//manager->commands->RunInteractive(command, chip::NullOptional, false);


        //sprinf(buf,"./chip-tool onoff toggle 1111 3");
        cout << "status:" << status << endl;
        // if (!isStorageInited)
        // {
        //     isStorageInited = true;
        //     if(line.size()<=1)
        //         manager->commands->Run(5,argv);
        //     else
        //         manager->commands->Run(4,argv2);
        // }
        // else
        // {
        //     if(line.size()<=1)
        //         manager->commands->RunCommand(5,argv);
        //     else
        //         manager->commands->RunCommand(4,argv2);
        // }
        printf("My Controller processing \n");
    }
    
    
    return NULL;
}

int Controller::RunCommand(char* command)
{
    return commands->RunInteractive(command, chip::NullOptional, false);
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