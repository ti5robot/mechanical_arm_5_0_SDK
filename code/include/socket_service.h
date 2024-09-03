#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iomanip>
#include <arpa/inet.h>

#include "Ti5LOGIC.h"
#include "Ti5MOVE.h"
#include "Ti5BASIC.h"

// 宏定义服务器IP地址
// #define SERVER_IP "192.168.30.5"
// #define SERVER_PORT 12345

void socket_data_analysis(uint8_t *input);

void socket_parse_data(uint8_t *values, uint16_t *reconstructedValues);

/*
 socket连接函数
 参数：
    serverIP:服务器IP地址
    port:服务器端口号
 返回值：
    成功返回0，失败返回1
*/
int socket_server(std::string& serverIP,int port);
