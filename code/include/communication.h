#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <arpa/inet.h>
#include <sys/socket.h>
#include<iostream>
using namespace std;
#define PORT 8087
extern struct sockaddr_in listenAddr;//服务端地址
extern struct sockaddr_in clientAddr;//客户端地址
void initsock();

#endif
