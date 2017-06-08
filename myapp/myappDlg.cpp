
// myappDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "myapp.h"
#include "myappDlg.h"
#include "afxdialogex.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CmyappDlg 对话框



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


// CmyappDlg 消息处理程序

BOOL CmyappDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmyappDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//InitConsole(); //在mfc中使用cout在控制台输出调试数据，先运行此函数即可。

		CRect   rect;
		CPaintDC   dc(this);
		GetClientRect(rect);
		dc.FillSolidRect(rect, RGB(212, 143, 28));   //设置为背景
		
		CDC *pDC;
		pDC = GetDC();
		theApp.chess.Paint_Qipan(pDC);  //调用画棋盘函数
	
		ReleaseDC(pDC); //及时释放pDC，防止内存泄漏

		

		CDialogEx::OnPaint();
	}
}





//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmyappDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmyappDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	//如果上次点击事件没有运行完，即没有接收到对方发来的数据，则点击鼠标无效
	if (kk == 0)
	{
		AfxMessageBox(_T("请等待对方下棋！")); 
		return;
	}
	

	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CDC *pDC;
	pDC = GetDC();
	
	
	if (theApp.chess.Paint_Cell(pDC, point) == 0) return; //下棋子,如果返回值为0，则下棋子失败，不做任何操作，返回

	

	//下棋成功,进行处理，检测是否销子
	if (theApp.chess.Chess_Suc_Deal(pDC) == 1) return;//出现禁着点或打劫，下棋失败

	
	
	//回传服务器数据	
	strcpy_s(theApp.m_socket.m_szBuffer, theApp.chess.buf);//拷贝数据到socket的数据缓存中
	theApp.m_socket.m_nLength = strlen(theApp.chess.buf);
	theApp.m_socket.AsyncSelect(FD_WRITE);//发送数据到服务器
		

	kk = 0;//将鼠标监听无效，在接收到数据之前

	ReleaseDC(pDC); //及时释放pDC，防止内存泄漏
	CDialogEx::OnLButtonDown(nFlags, point);
}

//悔棋
void CmyappDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码

	if (theApp.chess.getStep() == 0) return;
	if (theApp.chess.getRe() == 0) return;

	CDC *pDC;
	pDC = GetDC();

	theApp.chess.reChess(pDC);
	ReleaseDC(pDC); //及时释放pDC，防止内存泄漏

}

//取消
void CmyappDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}



//新游戏
void CmyappDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	CDC *pDC;
	pDC = GetDC();
	theApp.chess.newGame(pDC);
	ReleaseDC(pDC);
}
