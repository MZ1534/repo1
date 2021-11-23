#include <stdio.h>
#include "ftpClient.h"
int main() 
{
	initSocket();

	connectToHost();
	closeSocket();
	return 0;
}


//��ʼ��socket��
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
//�ر�socket��
bool closeSocket()
{
	if(0!=WSACleanup())
	{
		printf("WSACleanup faild:%d\n", WSAGetLastError());
		return false;
	}
	return true;
}
//�����ͻ�������
void connectToHost()
{
	//����server socket�׽��� ��ַ, �˿ں�
	//INVALID_SOCKET   SOCKET_ERROR

	SOCKET serfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == serfd)
	{
		printf("socket faild:%d\n", WSAGetLastError());
		return;
	}
	//��socket��IP�Ͷ˿ں�
	struct sockaddr_in serAddr;
	serAddr.sin_family = AF_INET; //����ʹ���socketָ����һ��,AF_INET �������ipv4��Э������
	serAddr.sin_port = htons(SPORT); //�ѱ����ֽ���תΪ�����ֽ���
	serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");  //��������IP��ַ
	//���ӵ�������
	if (0 != connect(serfd, (struct sockaddr *)&serAddr, sizeof(serAddr)))
	{
		printf("connect faild:%d\n", WSAGetLastError());
		return;
	}

	//��ʼ������Ϣ
	while (processMsg(serfd))
	{
		Sleep(1000);
	}
}
//������Ϣ
bool processMsg(SOCKET serfd)
{
	printf("hello ! \n");
	char sendBuffer[1024] = "msg:client send to server";
	send(serfd, sendBuffer, strlen(sendBuffer)+1, 0);
	return true;
}


