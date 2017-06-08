
// myappDlg.h : 头文件
//
#include "stdafx.h"
#pragma once


//控制台输出的头文件
#include <io.h>
#include <fcntl.h>



// CmyappDlg 对话框
class CmyappDlg : public CDialogEx
{
// 构造
public:
	CmyappDlg(CWnd* pParent = NULL);	// 标准构造函数


//public:
	//Chess chess;  //棋的对象，总的

public:
	
	int kk = 1;//用kk来决定当前是否允许下棋，是否鼠标监听可用

public:
	void InitConsole() //在mfc中使用cout在控制台输出调试数据，先运行此函数即可。
	{
		int nRet = 0;
		FILE* fp;
		AllocConsole();
		nRet = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
		fp = _fdopen(nRet, "w");
		*stdout = *fp;
		setvbuf(stdout, NULL, _IONBF, 0);
	}





// 对话框数据
	enum { IDD = IDD_MYAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};

