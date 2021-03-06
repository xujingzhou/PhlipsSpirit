// CG: This file was added by the Splash Screen component.
// Splash.cpp : implementation file
//////////////////////////////////////////////////
//类名：CSplashWnd
//功能：菲屏显示
//作者：徐景周(Johnny Xu, xujingzhou2016@gmail.com)
//组织：未来工作室(Future Studio)
//日期：2001.12.1
//////////////////////////////////////////////////
#include "stdafx.h"  // e. g. stdafx.h
#include "resource.h"  // e.g. resource.h

#include "Splash.h"  // e.g. splash.h

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define MOUSE_MOVE 0xF012
/////////////////////////////////////////////////////////////////////////////
//   Splash Screen class
//UINT CSplashWnd::m_nResourceID;
//BOOL CSplashWnd::c_bShowSplashWnd;
//CSplashWnd* CSplashWnd::c_pSplashWnd;
CSplashWnd::CSplashWnd()
{
}

CSplashWnd::~CSplashWnd()
{
	// Clear the static window pointer.
//	ASSERT(c_pSplashWnd == this);
//	c_pSplashWnd = NULL;
	if (m_wndOwner.m_hWnd != NULL)
		m_wndOwner.DestroyWindow();
}

BEGIN_MESSAGE_MAP(CSplashWnd, CWnd)
	//{{AFX_MSG_MAP(CSplashWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSplashWnd::EnableSplashScreen(UINT nResourceID,BOOL bEnable /*= TRUE*/)
{
	m_nResourceID = nResourceID;
	c_bShowSplashWnd = bEnable;
}

void CSplashWnd::ShowSplashScreen(CWnd* pParentWnd /*= NULL*/)
{
	if (!c_bShowSplashWnd || c_pSplashWnd != NULL)
		return;

	// Allocate a new splash screen, and create the window.
	c_pSplashWnd = new CSplashWnd;
	if (!c_pSplashWnd->Create(pParentWnd))
		delete c_pSplashWnd;
	else
		c_pSplashWnd->UpdateWindow();
}

BOOL CSplashWnd::PreTranslateAppMessage(MSG* pMsg)
{
	if (c_pSplashWnd == NULL)
		return FALSE;

	// If we get a keyboard or mouse message, hide the splash screen.
	if (pMsg->message == WM_KEYDOWN ||
	    pMsg->message == WM_SYSKEYDOWN ||
	    pMsg->message == WM_LBUTTONDOWN ||
	    pMsg->message == WM_RBUTTONDOWN ||
	    pMsg->message == WM_MBUTTONDOWN ||
	    pMsg->message == WM_NCLBUTTONDOWN ||
	    pMsg->message == WM_NCRBUTTONDOWN ||
	    pMsg->message == WM_NCMBUTTONDOWN)
	{
		SendMessage(WM_CLOSE);
//		c_pSplashWnd->HideSplashScreen();
//		SendMessage(WM_LBUTTONUP);
//		SendMessage(WM_SYSCOMMAND, MOUSE_MOVE);
		return TRUE;	// message handled here
	}

	return FALSE;	// message not handled
}

BOOL CSplashWnd::Create(CWnd* pParentWnd /*= NULL*/)
{
	if (!m_bitmap.LoadBitmap(m_nResourceID))
		return FALSE;

	BITMAP bm;
	m_bitmap.GetBitmap(&bm);

	LPCTSTR pszWndClass = AfxRegisterWndClass(0);
	VERIFY(m_wndOwner.CreateEx(0, pszWndClass, _T(""), WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, 0));
	
	//Create this window
	pszWndClass = AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	VERIFY(CreateEx(0, pszWndClass, _T(""), WS_POPUP | WS_VISIBLE, 0, 0, bm.bmWidth, bm.bmHeight, m_wndOwner.GetSafeHwnd(), NULL));

	return TRUE;
}

void CSplashWnd::HideSplashScreen()
{
	// Destroy the window, and update the mainframe.
//	DestroyWindow();
//	AfxGetMainWnd()->UpdateWindow();
}

void CSplashWnd::PostNcDestroy()
{
	// Free the C++ class.
//	delete this;
}

int CSplashWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Center the window.
	CenterWindow();

	return 0;
}

void CSplashWnd::OnPaint()
{
	CPaintDC dc(this);

	CDC dcImage;
	if (!dcImage.CreateCompatibleDC(&dc))
		return;

	BITMAP bm;
	m_bitmap.GetBitmap(&bm);

	// Paint the image.
	CBitmap* pOldBitmap = dcImage.SelectObject(&m_bitmap);
	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCCOPY);
	dcImage.SelectObject(pOldBitmap);
}

void CSplashWnd::OnTimer(UINT nIDEvent)
{
	// Destroy the splash screen window.
}

void CSplashWnd::OnClose() 
{	
	CWnd::OnClose();
}

/////////////////////////////////////////////////////////////////////////////
// CSplashThread

IMPLEMENT_DYNCREATE(CSplashThread, CWinThread)

CSplashThread::CSplashThread()
{
}

CSplashThread::~CSplashThread()
{
}

BOOL CSplashThread::InitInstance()
{
  //Attach this threads UI state to the main one, This will ensure that 
  //the activation state is managed consistenly across the two threads
  ASSERT(AfxGetApp());
  BOOL bSuccess = AttachThreadInput(m_nThreadID, AfxGetApp()->m_nThreadID, TRUE);
  if (!bSuccess)
    TRACE(_T("Failed in call to AttachThredInput, GetLastError:%d\n"), ::GetLastError());

  //Create the Splash Screen UI
  BOOL bCreated = m_SplashScreen.Create();
	VERIFY(bCreated);
  m_pMainWnd = &m_SplashScreen;

	return bCreated;
}

//设置显示位图资源ID
void CSplashThread::SetBitmapID(UINT nResourceID)
{
	m_SplashScreen.EnableSplashScreen(nResourceID,true);
}

//隐藏窗体
void CSplashThread::HideSplash()
{
  //Wait until the splash screen has been created
  //before trying to close it
  while (!m_SplashScreen.GetSafeHwnd());

  m_SplashScreen.SendMessage(WM_CLOSE);
}

int CSplashThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CSplashThread, CWinThread)
	//{{AFX_MSG_MAP(CSplashThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplashThread message handlers
