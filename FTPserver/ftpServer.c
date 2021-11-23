#include <stdio.h>
#include "ftpServer.h"
int main() 
{
	initSocket();

	listenToClient();
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
void listenToClient()
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
	serAddr.sin_addr.S_un.S_addr = ADDR_ANY;  //监听本机所有网卡，IP地址
	if (0 != bind(serfd, (struct sockaddr *)&serAddr, sizeof(serAddr)))  // “函数”: 从“sockaddr_in *”到“const sockaddr *”的类型不兼容
	{
		printf("bind faild:%d\n", WSAGetLastError());
		return;
	}

	//监听客户端连接
	if (0 != listen(serfd, 10))
	{
		printf("listen faild:%d\n", WSAGetLastError());
		return;
	}

	//有客户端连接，那么就要接受连接
	struct sockaddr_in cliAddr; //是一个传出参数，来接收客户端的端口号IP地址等。
	int len = sizeof(cliAddr);
	SOCKET clifd = accept(serfd, (struct sockaddr_in *)&cliAddr, &len);  //返回值：是socket，用于和客户端进行通讯的socket
	if (INVALID_SOCKET == clifd)
	{
		printf("accept faild:%d\n", WSAGetLastError());
		return;
	}

	//开始处理消息
	while (processMsg(clifd))
	{
		Sleep(1000);
	}
}
//处理消息
bool processMsg(SOCKET clifd)
{
	
	char recvBuf[1024] = "{0}";
	recv(clifd, recvBuf, 1023, 0);
	printf("%s\n", recvBuf);
	return true;
}


