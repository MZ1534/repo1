#pragma once
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <stdbool.h>
#define SPORT 8888  //�������˿ں�

//��ʼ��socket��
bool initSocket();
//�ر�socket��
bool closeSocket();
//�����ͻ�������
void listenToClient();
//������Ϣ
bool processMsg(SOCKET);