#!/bin/bash
g++ main.cpp  -L./include -lmylibti5 -L./include/can -lmylibscan -lcontrolcan -lspdlog -lfmt -ludev -o move_sov
