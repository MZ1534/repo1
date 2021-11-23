#include <stdio.h>
#include "ftpClient.h"
int main() 
{
	initSocket();

	connectToHost();
	closeSocket();
	return 0;
}


//初始化socket库
bool initSocket()
{
	WSADATA wsadata;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsadata))
	{ 
		printf("WSAStartup faild:%d\n",WSAGetLastError());
		return false;
	}
	return true;

}
//关闭socket库
bool closeSocket()
{
	if(0!=WSACleanup())
	{
		printf("WSACleanup faild:%d\n", WSAGetLastError());
		return false;
	}
	return true;
}
//监听客户端连接
void connectToHost()
{
	//创建server socket套接字 地址, 端口号
	//INVALID_SOCKET   SOCKET_ERROR

	SOCKET serfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == serfd)
	{
		printf("socket faild:%d\n", WSAGetLastError());
		return;
	}
	//给socket绑定IP和端口号
	struct sockaddr_in serAddr;
	serAddr.sin_family = AF_INET; //必须和创建socket指定的一样,AF_INET 代表的是ipv4的协议类型
	serAddr.sin_port = htons(SPORT); //把本地字节序转为网络字节序
	serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");  //服务器的IP地址
	//连接到服务器
	if (0 != connect(serfd, (struct sockaddr *)&serAddr, sizeof(serAddr)))
	{
		printf("connect faild:%d\n", WSAGetLastError());
		return;
	}

	//开始处理消息
	while (processMsg(serfd))
	{
		Sleep(1000);
	}
}
//处理消息
bool processMsg(SOCKET serfd)
{
	printf("hello ! \n");
	char sendBuffer[1024] = "msg:client send to server";
	send(serfd, sendBuffer, strlen(sendBuffer)+1, 0);
	return true;
}


