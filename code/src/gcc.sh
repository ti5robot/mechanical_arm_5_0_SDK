#!/bin/bash

g++ main.cpp  -L./include -lmylibti5 -L./include/can -I/usr/include/python3.10 -lpython3.10 -lmylibscan -lcontrolcan -lspdlog -lfmt -ludev -o move_sov
