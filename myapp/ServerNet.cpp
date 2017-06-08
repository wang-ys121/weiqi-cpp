/*
ServerNet.cpp
*/
#include "stdafx.h"
#include "ServerNet.h"

int CServerNet::Init(const char* address, int port)
{
	int rlt = 0;

	//���ڼ�¼������Ϣ�������
	int iErrorMsg;

	//��ʼ��WinSock
	WSAData wsaData;
	iErrorMsg = WSAStartup(MAKEWORD(1, 1), &wsaData);

	if (iErrorMsg != NO_ERROR)
	{
		//��ʼ��WinSockʧ��
		printf("wsastartup failed with error : %d\n", iErrorMsg);

		rlt = 1;
		return rlt;
	}

	//���������Socket
	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_sock == INVALID_SOCKET)

	{
		//����Socket�쳣
		printf("socket failed with error : %d\n", WSAGetLastError());

		rlt = 2;
		return rlt;
	}

	//������Ϣ
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = port;
	serverAddr.sin_addr.s_addr = inet_addr(address);

	//��
	iErrorMsg = bind(m_sock, (sockaddr*)&serverAddr, sizeof(serverAddr));
	if (iErrorMsg < 0)
	{
		//��ʧ��
		printf("bind failed with error : %d\n", iErrorMsg);
		rlt = 3;
		return rlt;
	}



	return rlt;
}

void CServerNet::Run(char* buf)
{
	//��������s
	listen(m_sock, 1);

	sockaddr_in tcpAddr;
	int len = sizeof(sockaddr);
	SOCKET newSocket;
	//char buf[3];
	int rval;

	//������Ϣ
	newSocket = accept(m_sock, (sockaddr*)&tcpAddr, &len);


	if (newSocket == INVALID_SOCKET)
	{
		//�ǿ���socket

	}
	else
	{
		//��socket����
		printf("new socket connect : %d\n", newSocket);


		//��Ϣ����
	//	do
		//{
			printf("process\n");
			//��������
			memset(buf, 0, sizeof(buf));
			rval = recv(newSocket, buf, 3, 0);

			//printf("222%c", buf[0]);
			//printf("222%c", buf[1]);
			//printf("222%c", buf[2]);
			/*
			//���Խ����Ƿ���ȷ��
			int i;
			for (i = 0; i < 2647; ++i)
			{
				if (buf[i] != '1') break;
			}
			printf("%d",i);
			*/

			/*
			if (rval == SOCKET_ERROR)
				//��Ӧ���Ǹ��쳣�����ͻ���û�е���closeSocket��ֱ���˳���Ϸ��ʱ�򣬽����������
				printf("recv socket error\n");



			if (rval == 0)
				//recv����0��ʾ�����˳�
				printf("ending connection");
			else
				//��ʾ���յ�������
				
				//printf("recv %s\n", buf);

			*/

		//} while (rval != 0);

		//�رն�ӦAccept��socket
		closesocket(newSocket);
		
	}




	//�ر������Socket
	closesocket(m_sock);
}