
// myapp.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

#include "ClientSocket.h"
#include "myappDlg.h"
#include "Chess.h"
#include "stdafx.h"
//控制台输出的头文件
#include <io.h>
#include <fcntl.h>

// CmyApp: 
// 有关此类的实现，请参阅 myapp.cpp
//






class CmyApp : public CWinApp
{
public:
	CmyApp();

public:
	Chess chess;  //棋的对象，总的

//连接用的socketClient
public:
	CmyappDlg *p_Dlg;

	//CClientNet client;
	ClientSocket m_socket;//创建传输数据的socket
	void InitConsole() //在mfc中使用cout在控制台输出调试数据，先运行此函数即可。
	{
		int nRet = 0;
		FILE* fp;
		AllocConsole();
		nRet = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
		fp = _fdopen(nRet, "w");
		*stdout = *fp;
		setvbuf(stdout, NULL, _IONBF, 0);
	};

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CmyApp theApp;
