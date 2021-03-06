/////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////
//类名：CHelpTipDlg
//功能：退出对话框类
//作者：徐景周(Johnny Xu, xujingzhou2016@gmail.com)
//组织：未来工作室(Future Studio)
//日期：2001.12.1
//////////////////////////////////////////////////
#include "stdafx.h"
#include "HelpTip.h"
#include "HelpTipDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define BACKWIDTH 320   // 窗体高度(既背景位图高度)
#define BACKHEIGHT 240  // 窗体宽度(既背景位图宽度)

CHelpTipDlg::CHelpTipDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHelpTipDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHelpTipDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHelpTipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHelpTipDlg)
//	DDX_Control(pDX, IDOK, m_OK);
//	DDX_Control(pDX, IDCANCEL, m_Cancel);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHelpTipDlg, CDialog)
	//{{AFX_MSG_MAP(CHelpTipDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelpTipDlg message handlers
//********************************************************************************
//* 名称：OnInitDialog()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：初始化关闭对话框
//********************************************************************************
BOOL CHelpTipDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

/*
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
    //退出对话框中，初始化阴影位图按钮
    m_OK.SetTextColor(RGB(0,0,0));
	m_OK.SetToolTipText("继续");  
	m_OK.SetShade(SHS_NOISE,33);  //(SHS_HARDBUMP,10,20,5,RGB(55,55,255));

	m_Cancel.SetTextColor(RGB(0,0,0));
	m_Cancel.SetToolTipText("退出");  
	m_Cancel.SetShade(SHS_NOISE,33);  

	//加入标签的超连
//    m_Mail.SetURL(_T("mailto:jingzhou_xu@163.net"));
//	m_Mail.SetUnderline(FALSE);	

*/
	//初始置窗体大小为背景位图大小
	CRect	windowRect,m_Rect,DeskTopWnd;
	windowRect.SetRect(0,
		0,
		BACKWIDTH ,
		BACKHEIGHT );

	//置窗体为显示及其位置
	MoveWindow(windowRect,FALSE);
	CenterWindow();

	SetTimer(1,2000,NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHelpTipDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHelpTipDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// ---------------------------------------------------------
//	名称: OnEraseBkgnd
//	功能: 刷新窗体背景位图
//	变量: 无
//	返回: TRUE --成功，FALSE -- 失败
//	编写: 徐景周，2002.4.8
// ---------------------------------------------------------
BOOL CHelpTipDlg::OnEraseBkgnd(CDC* pDC) 
{
	CDC     memDC;
	CBitmap cBitmap;
	cBitmap.LoadBitmap(IDB_SPLASH_CLOSE);
	memDC.CreateCompatibleDC (pDC);
	CBitmap *oldBitmap=memDC.SelectObject(&cBitmap);
	pDC->BitBlt (0,0,BACKWIDTH,BACKHEIGHT,&memDC,0,0,SRCCOPY);
	memDC.SelectObject(oldBitmap);

	return TRUE;
}

// ---------------------------------------------------------
//	名称: OnLButtonDown
//	功能: 左键按下时，关闭对话框　
//	变量: 无
//	返回: 无
//	编写: 徐景周，2002.4.8
// ---------------------------------------------------------
void CHelpTipDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect rcWnd;
	GetWindowRect(&rcWnd);
	CPoint pt;
	GetCursorPos(&pt);

	if(rcWnd.PtInRect(pt))
	{
		SendMessage(WM_CLOSE);
	}
}

// ---------------------------------------------------------
//	名称: OnTimer
//	功能: 定时时间到，关闭对话框
//	变量: 无
//	返回: 无
//	编写: 徐景周，2002.4.8
// ---------------------------------------------------------
void CHelpTipDlg::OnTimer(UINT nIDEvent) 
{
	SendMessage(WM_CLOSE);

	CDialog::OnTimer(nIDEvent);
}
