/*
ServerNet.cpp
*/
#include "stdafx.h"
#include "ServerNet.h"

int CServerNet::Init(const char* address, int port)
{
	int rlt = 0;

	//用于记录错误信息，并输出
	int iErrorMsg;

	//初始化WinSock
	WSAData wsaData;
	iErrorMsg = WSAStartup(MAKEWORD(1, 1), &wsaData);

	if (iErrorMsg != NO_ERROR)
	{
		//初始化WinSock失败
		printf("wsastartup failed with error : %d\n", iErrorMsg);

		rlt = 1;
		return rlt;
	}

	//创建服务端Socket
	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_sock == INVALID_SOCKET)

	{
		//创建Socket异常
		printf("socket failed with error : %d\n", WSAGetLastError());

		rlt = 2;
		return rlt;
	}

	//声明信息
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = port;
	serverAddr.sin_addr.s_addr = inet_addr(address);

	//绑定
	iErrorMsg = bind(m_sock, (sockaddr*)&serverAddr, sizeof(serverAddr));
	if (iErrorMsg < 0)
	{
		//绑定失败
		printf("bind failed with error : %d\n", iErrorMsg);
		rlt = 3;
		return rlt;
	}



	return rlt;
}

void CServerNet::Run(char* buf)
{
	//公开连接s
	listen(m_sock, 1);

	sockaddr_in tcpAddr;
	int len = sizeof(sockaddr);
	SOCKET newSocket;
	//char buf[3];
	int rval;

	//接收信息
	newSocket = accept(m_sock, (sockaddr*)&tcpAddr, &len);


	if (newSocket == INVALID_SOCKET)
	{
		//非可用socket

	}
	else
	{
		//新socket连接
		printf("new socket connect : %d\n", newSocket);


		//消息处理
	//	do
		//{
			printf("process\n");
			//接收数据
			memset(buf, 0, sizeof(buf));
			rval = recv(newSocket, buf, 3, 0);

			//printf("222%c", buf[0]);
			//printf("222%c", buf[1]);
			//printf("222%c", buf[2]);
			/*
			//测试接收是否正确；
			int i;
			for (i = 0; i < 2647; ++i)
			{
				if (buf[i] != '1') break;
			}
			printf("%d",i);
			*/

			/*
			if (rval == SOCKET_ERROR)
				//这应该是个异常，当客户端没有调用closeSocket就直接退出游戏的时候，将会进入这里
				printf("recv socket error\n");



			if (rval == 0)
				//recv返回0表示正常退出
				printf("ending connection");
			else
				//显示接收到的数据
				
				//printf("recv %s\n", buf);

			*/

		//} while (rval != 0);

		//关闭对应Accept的socket
		closesocket(newSocket);
		
	}




	//关闭自身的Socket
	closesocket(m_sock);
}