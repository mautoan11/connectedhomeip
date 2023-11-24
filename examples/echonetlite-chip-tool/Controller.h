#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "commands/common/Commands.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
using namespace std;

class Controller {
public:
    Commands* commands;
	Controller(Commands* commands_){commands = commands_;}
	virtual ~Controller(){}
    void TestPrint();//{printf("\n\nTest Controller OK\n\n");};
    void Start();
    void TestCommand();
};
#endif