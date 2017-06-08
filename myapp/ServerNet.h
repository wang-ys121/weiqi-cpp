#pragma once

/*
ServerNet.h
用于表示服务端的网络操作

*/

#include <stdio.h>
#include <winsock.h>

#pragma comment (lib,"ws2_32.lib")

class CServerNet
{
public:

	//初始化服务器,返回0表示成功
	int Init(const char* address, int port);

	//更新数据
	void Run(char * buf);


private:
	SOCKET m_sock;
};