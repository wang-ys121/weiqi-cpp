
// myapp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#include "ClientSocket.h"
#include "myappDlg.h"
#include "Chess.h"
#include "stdafx.h"
//����̨�����ͷ�ļ�
#include <io.h>
#include <fcntl.h>

// CmyApp: 
// �йش����ʵ�֣������ myapp.cpp
//






class CmyApp : public CWinApp
{
public:
	CmyApp();

public:
	Chess chess;  //��Ķ����ܵ�

//�����õ�socketClient
public:
	CmyappDlg *p_Dlg;

	//CClientNet client;
	ClientSocket m_socket;//�����������ݵ�socket
	void InitConsole() //��mfc��ʹ��cout�ڿ���̨����������ݣ������д˺������ɡ�
	{
		int nRet = 0;
		FILE* fp;
		AllocConsole();
		nRet = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
		fp = _fdopen(nRet, "w");
		*stdout = *fp;
		setvbuf(stdout, NULL, _IONBF, 0);
	};

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CmyApp theApp;
