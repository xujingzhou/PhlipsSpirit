// Splash.h : header file
//////////////////////////////////////////////////
//类名：CSplashWnd
//功能：菲屏显示
//作者：徐景周(Johnny Xu, xujingzhou2016@gmail.com)
//组织：未来工作室(Future Studio)
//日期：2001.12.1
//////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
#ifndef _SPLASH_SCRN_
#define _SPLASH_SCRN_

//   Splash Screen class

class CSplashWnd : public CWnd
{
// Construction
public:
	CSplashWnd();

// Attributes:
public:
	CBitmap m_bitmap;

// Operations
public:
	void EnableSplashScreen(	UINT nResourceID, BOOL bEnable = TRUE);
	void ShowSplashScreen(CWnd* pParentWnd = NULL);
	BOOL PreTranslateAppMessage(MSG* pMsg);

	BOOL Create(CWnd* pParentWnd = NULL);
	void HideSplashScreen();
	BOOL c_bShowSplashWnd;
	CSplashWnd* c_pSplashWnd;
	UINT m_nResourceID;                 //打开位图资源名称,jingzhou xu
	CWnd      m_wndOwner;     

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplashWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	~CSplashWnd();
	virtual void PostNcDestroy();

protected:
	
// Generated message map functions
protected:
	//{{AFX_MSG(CSplashWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif


/////////////////////////////////////////////////////////////////////////////
// CSplashThread thread

class CSplashThread : public CWinThread
{
	DECLARE_DYNCREATE(CSplashThread)
protected:
	CSplashThread();           // protected constructor used by dynamic creation

// Attributes
public:

	void SetBitmapID(UINT nResourceID);          //设置位图资源ID
	void HideSplash();							 //隐藏位图

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplashThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSplashThread();

	 CSplashWnd m_SplashScreen;
	// Generated message map functions
	//{{AFX_MSG(CSplashThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
