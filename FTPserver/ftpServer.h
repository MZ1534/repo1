#pragma once
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <stdbool.h>
#define SPORT 8888  //服务器端口号

//初始化socket库
bool initSocket();
//关闭socket库
bool closeSocket();
//监听客户端连接
void listenToClient();
//处理消息
bool processMsg(SOCKET);