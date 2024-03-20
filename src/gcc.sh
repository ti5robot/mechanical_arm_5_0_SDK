#!/bin/bash
#g++ main.cpp -g -L../include/can -lmylibscan -lcontrolcan -lspdlog -lfmt -ludev -o move_sov 
#g++ main.cpp communication.cpp mathfunc.cpp Ti5BASIC.cpp  Ti5MOVE.cpp tool.cpp -g -L../include/can -lmylibscan -lcontrolcan -lspdlog -lfmt -ludev -o move_sov 

g++ main.cpp  -L./include -lmylibti5 -L./include/can -lmylibscan -lcontrolcan -lspdlog -lfmt -ludev -o move_sov