// HelpTip.cpp : Defines the class behaviors for the application.
//////////////////////////////////////////////////
//类名：CHelpTipApp
//功能：应用类
//作者：徐景周(Johnny Xu, xujingzhou2016@gmail.com)
//组织：未来工作室(Future Studio)
//日期：2001.12.1
//////////////////////////////////////////////////
#include "stdafx.h"
#include "HelpTip.h"
#include "HelpTipDlg.h"
#include "transparentWnd.h"
#include "Splash.h"
// Download by http://www.codefans.net
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHelpTipApp

BEGIN_MESSAGE_MAP(CHelpTipApp, CWinApp)
	//{{AFX_MSG_MAP(CHelpTipApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelpTipApp construction

CHelpTipApp::CHelpTipApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHelpTipApp object

CHelpTipApp theApp;

/////////////////////////////////////////////////////////////////////////////
//********************************************************************************
//* 名称：CHelpTipApp
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：程序初始化实例
//********************************************************************************
BOOL CHelpTipApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	srand(time(NULL));          //初始化随机涵数

	//限定此程序只能运行一次，用互斥量来判断程序是否已运行
    HANDLE m_hMutex=CreateMutex(NULL,TRUE, m_pszAppName); 
    if(GetLastError()==ERROR_ALREADY_EXISTS) { return FALSE; }

	//显示初始菲屏显示
	CSplashThread* pSplashThread = (CSplashThread*) AfxBeginThread(RUNTIME_CLASS(CSplashThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	if (pSplashThread == NULL)
	{
		AfxMessageBox(_T("显示扉屏创建失败!"), MB_OK | MB_ICONSTOP);
		return FALSE;
	}
	ASSERT(pSplashThread->IsKindOf(RUNTIME_CLASS(CSplashThread)));

	pSplashThread->SetBitmapID(IDB_SPLASH);  

	pSplashThread->ResumeThread();  //Resume the thread now that we have set it up 

	Sleep(2000);  

	//隐藏菲屏
	if (pSplashThread != NULL)
		pSplashThread->HideSplash();
	 
	//设置对话框背景和文本颜色
	SetDialogBkColor(RGB(160,180,220),RGB(0,0,0));

	//建立透明窗体
	CTransparentWnd* pFrame = new CTransparentWnd;
	m_pMainWnd = pFrame;

	CRect rect(0, 0, 80, 100);
	pFrame->CreateTransparent("精灵信使", rect);
	pFrame->CenterWindow();
	pFrame->ShowWindow(SW_SHOW);


	return TRUE;
}
