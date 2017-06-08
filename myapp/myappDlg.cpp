
// myappDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "myapp.h"
#include "myappDlg.h"
#include "afxdialogex.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmyappDlg �Ի���



CmyappDlg::CmyappDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmyappDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmyappDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmyappDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDOK, &CmyappDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CmyappDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &CmyappDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CmyappDlg ��Ϣ�������

BOOL CmyappDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CmyappDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmyappDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//InitConsole(); //��mfc��ʹ��cout�ڿ���̨����������ݣ������д˺������ɡ�

		CRect   rect;
		CPaintDC   dc(this);
		GetClientRect(rect);
		dc.FillSolidRect(rect, RGB(212, 143, 28));   //����Ϊ����
		
		CDC *pDC;
		pDC = GetDC();
		theApp.chess.Paint_Qipan(pDC);  //���û����̺���
	
		ReleaseDC(pDC); //��ʱ�ͷ�pDC����ֹ�ڴ�й©

		

		CDialogEx::OnPaint();
	}
}





//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CmyappDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmyappDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	//����ϴε���¼�û�������꣬��û�н��յ��Է����������ݣ����������Ч
	if (kk == 0)
	{
		AfxMessageBox(_T("��ȴ��Է����壡")); 
		return;
	}
	

	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDC *pDC;
	pDC = GetDC();
	
	
	if (theApp.chess.Paint_Cell(pDC, point) == 0) return; //������,�������ֵΪ0����������ʧ�ܣ������κβ���������

	

	//����ɹ�,���д�������Ƿ�����
	if (theApp.chess.Chess_Suc_Deal(pDC) == 1) return;//���ֽ��ŵ���٣�����ʧ��

	
	
	//�ش�����������	
	strcpy_s(theApp.m_socket.m_szBuffer, theApp.chess.buf);//�������ݵ�socket�����ݻ�����
	theApp.m_socket.m_nLength = strlen(theApp.chess.buf);
	theApp.m_socket.AsyncSelect(FD_WRITE);//�������ݵ�������
		

	kk = 0;//����������Ч���ڽ��յ�����֮ǰ

	ReleaseDC(pDC); //��ʱ�ͷ�pDC����ֹ�ڴ�й©
	CDialogEx::OnLButtonDown(nFlags, point);
}

//����
void CmyappDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	if (theApp.chess.getStep() == 0) return;
	if (theApp.chess.getRe() == 0) return;

	CDC *pDC;
	pDC = GetDC();

	theApp.chess.reChess(pDC);
	ReleaseDC(pDC); //��ʱ�ͷ�pDC����ֹ�ڴ�й©

}

//ȡ��
void CmyappDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}



//����Ϸ
void CmyappDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDC *pDC;
	pDC = GetDC();
	theApp.chess.newGame(pDC);
	ReleaseDC(pDC);
}
