
// myappServerDlg.h : ͷ�ļ�
//

#pragma once
#include "ListenSocket.h"


//����̨�����ͷ�ļ�
#include <io.h>
#include <fcntl.h>


// CmyappServerDlg �Ի���
class CmyappServerDlg : public CDialogEx
{
// ����
public:
	CmyappServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MYAPPSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	CListenSocket m_srvrSocket; //�����׽��� 

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
	afx_msg void OnBnClickedOk();
};
