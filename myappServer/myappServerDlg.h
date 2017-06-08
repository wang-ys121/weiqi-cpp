
// myappServerDlg.h : 头文件
//

#pragma once
#include "ListenSocket.h"


//控制台输出的头文件
#include <io.h>
#include <fcntl.h>


// CmyappServerDlg 对话框
class CmyappServerDlg : public CDialogEx
{
// 构造
public:
	CmyappServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MYAPPSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	CListenSocket m_srvrSocket; //监听套接字 

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
	afx_msg void OnBnClickedOk();
};
