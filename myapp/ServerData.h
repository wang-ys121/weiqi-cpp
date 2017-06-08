#pragma once
#include "ClientNet.h"
#include "ServerNet.h"
class ServerData
{
public:
	ServerData();
	~ServerData();


public:
	void send(char* msg)
	{
		CClientNet client;

		//���ӵ�127.0.0.1�������أ�,�˿ں�Ϊ8888�ķ����
		printf("Connect\n");
		client.Connect(9999, "127.0.0.1");

		//������Ϣ
		printf("send msg\n");
		client.SendMsg(msg, sizeof(msg));

		//�ر�socket
		printf("close\n");
		client.Close();

	};
	void receive(char* buf)
	{

		CServerNet serverNet;
		int iRlt = serverNet.Init("127.0.0.1", 8888);
		if (iRlt == 0)
		{
			printf("init ok...\n");
			serverNet.Run(buf);
			
		}
		else
			printf("serverNet init failed with error : %d\n", iRlt);
	}

};

