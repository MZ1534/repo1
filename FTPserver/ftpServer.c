#include <stdio.h>
#include "ftpServer.h"
int main() 
{
	initSocket();

	listenToClient();
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
void listenToClient()
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
	serAddr.sin_addr.S_un.S_addr = ADDR_ANY;  //������������������IP��ַ
	if (0 != bind(serfd, (struct sockaddr *)&serAddr, sizeof(serAddr)))  // ��������: �ӡ�sockaddr_in *������const sockaddr *�������Ͳ�����
	{
		printf("bind faild:%d\n", WSAGetLastError());
		return;
	}

	//�����ͻ�������
	if (0 != listen(serfd, 10))
	{
		printf("listen faild:%d\n", WSAGetLastError());
		return;
	}

	//�пͻ������ӣ���ô��Ҫ��������
	struct sockaddr_in cliAddr; //��һ�����������������տͻ��˵Ķ˿ں�IP��ַ�ȡ�
	int len = sizeof(cliAddr);
	SOCKET clifd = accept(serfd, (struct sockaddr_in *)&cliAddr, &len);  //����ֵ����socket�����ںͿͻ��˽���ͨѶ��socket
	if (INVALID_SOCKET == clifd)
	{
		printf("accept faild:%d\n", WSAGetLastError());
		return;
	}

	//��ʼ������Ϣ
	while (processMsg(clifd))
	{
		Sleep(1000);
	}
}
//������Ϣ
bool processMsg(SOCKET clifd)
{
	
	char recvBuf[1024] = "{0}";
	recv(clifd, recvBuf, 1023, 0);
	printf("%s\n", recvBuf);
	return true;
}


