#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iomanip>
#include <arpa/inet.h>

#include "Ti5LOGIC.h"
#include "Ti5MOVE.h"

// 宏定义服务器IP地址
#define SERVER_IP "192.168.30.5"
#define SERVER_PORT 12345

void socket_data_analysis(uint8_t *input);

void socket_parse_data(uint8_t *values, uint16_t *reconstructedValues);

int socket_server();
