安装spdlog库
sudo apt install libspdlog-dev
编译的时候需要加：-lspdlog -lfmt

安装opcv库
sudo apt install libopencv-dev

安装libudev库libudev-dev
编译的时候需要加：
-ludev 则指示链接器链接 libudev 库

编译：
g++ main.cpp communication.cpp mathfunc.cpp Ti5BASIC.cpp  Ti5MOVE.cpp tool.cpp Ti5LOGIC.cpp  -L../include/can -lmylibscan -lcontrolcan -lspdlog -lfmt -ludev -o move_sov 

生成.o文件：
g++ -c -fpic Ti5BASIC.cpp Ti5LOGIC.cpp Ti5MOVE.cpp  communication.cpp mathfunc.cpp tool.cpp

生成.so文件：
g++ -shared mathfunc.o   -o lib_mathfunc.so
g++ -shared Ti5BASIC.o   -o lib_ti5basic.so
g++ -shared Ti5LOGIC.o   -o lib_ti5logic.so
g++ -shared Ti5MOVE.o   -o lib_ti5move.so
g++ -shared tool.o   -o lib_tool.so
g++ -shared communication.o   -o lib_communication.so