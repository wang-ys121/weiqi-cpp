
// myappDlg.h : ͷ�ļ�
//
#include "stdafx.h"
#pragma once


//����̨�����ͷ�ļ�
#include <io.h>
#include <fcntl.h>



// CmyappDlg �Ի���
class CmyappDlg : public CDialogEx
{
// ����
public:
	CmyappDlg(CWnd* pParent = NULL);	// ��׼���캯��


//public:
	//Chess chess;  //��Ķ����ܵ�

public:
	
	int kk = 1;//��kk��������ǰ�Ƿ��������壬�Ƿ�����������

public:
	void InitConsole() //��mfc��ʹ��cout�ڿ���̨����������ݣ������д˺������ɡ�
	{
		int nRet = 0;
		FILE* fp;
		AllocConsole();
		nRet = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
		fp = _fdopen(nRet, "w");
		*stdout = *fp;
		setvbuf(stdout, NULL, _IONBF, 0);
	}





// �Ի�������
	enum { IDD = IDD_MYAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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

