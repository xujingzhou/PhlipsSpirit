//////////////////////////////////////////////////
//类名：CTransparentWnd
//功能：透明窗体实现
//作者：徐景周(Johnny Xu, xujingzhou2016@gmail.com)
//组织：未来工作室(Future Studio)
//日期：2001.12.1
//////////////////////////////////////////////////
#if !defined(AFX_TRANSPARENTWND_H__INCLUDED_)
#define AFX_TRANSPARENTWND_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#include "XInfoTip.h"						//加入提示窗类
#include "NTray.h"							//加入系统托盘支持头文件
#include "BCMenu.h"							//添加位图菜单

class CTransparentWnd : public CWnd
{

public:
	CTransparentWnd();

    CXInfoTip	m_Tip;						//加入提示窗类变量
	BCMenu m_popmenu;						//定义位图菜单变量

	void CreateTransparent(LPCTSTR pTitle, RECT &rect);
	void SetupRegion(CDC *pDC);
	void DoSet(void);
	void DoWalk(void);
	void DoRun(void);
	void DoIdle(void);
	void DoDrag(void);                      //拖动
	void DoTransform(void);                 //变形
	void DoFall(void);						//拖动后的下落表现

	void WinAnimation(BOOL ShowFlag);		//窗体显示/隐藏的动画效果    
	CRect GetTopWndTitleRect();             //获取当前桌面最顶层窗口标题区大小
	int  GetCurAction();                    //获取当前行为表现方式
	BOOL GetFullScreenWalk();               //获取是否全屏运动标志位
	BOOL GetOptionMute();                   //获取静音标志位
	BOOL GetOptionTopShow();                //获取顶层显示标志位
	BOOL GetOptionRest();                   //获取静止标志位
	void SoundPlay(void);					//播放内镶WAV文件
	BOOL StartupAutorun(BOOL bIsAdd);       //开机自动运行

											//下载提示文件
	BOOL GetSourceHtml(CString theUrl,CString Filename);
	BOOL GetAutorunFlag();					//获取自动运行标志
	BOOL GetShowNewsFlag();                 //获取显示新闻标志

	BOOL m_bShowNews;                       //是否显示新闻
	BOOL m_bDownloadFailed;					//是否下载成功标志
	BOOL m_bSuccess;						//流文件打开是否成功
	CStdioFile m_sdFile;					//流文件

	CRect m_Rect;                           //最顶层窗口标题区大小
	int m_iAction;                          //当前行为表现方式
	CString strPath;						//主执行程序所在的路径
	CBitmap m_bmpDraw;						//位图
	int m_iAniSeq;							//位图变化量
	CPoint m_ptDest;						//运动点
	int m_iLastDirection;					//方向
	BOOL m_bFullScreenWalk;                 //全屏运动标志
	BOOL m_bDragDrop;						//拖动标志位
	CPoint m_ptCurPoint;					//记录当前鼠标位置
	BOOL m_bMute;                           //静音标志
	BOOL m_bTopShow;                        //最顶层显示标志
	BOOL m_bRest;                           //静止标志
	CTime m_Time;                           //闹铃设置时间
	BOOL m_bRing;                           //闹铃提示标志
	int m_iSecondNum;						//秒数
	BOOL m_bAutorun;                        //自动运行标志

public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransparentWnd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTransparentWnd();

protected:

	HICON			m_hIcon[1];				//系统托盘支持设置变量
	CTrayNotifyIcon m_TrayIcon;

	// Generated message map functions
protected:
	//{{AFX_MSG(CTransparentWnd)
	afx_msg LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnExit();
	afx_msg void OnFullscreenWalk();
	afx_msg void OnUpdateFullscreenWalk(CCmdUI* pCmdUI);
	afx_msg void OnShowhide();
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnDownload();
	afx_msg void OnActionRun();
	afx_msg void OnActionWalk();
	afx_msg void OnActionIdle();
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	afx_msg void OnAbout();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnOptionMute();
	afx_msg void OnOptionRest();
	afx_msg void OnOptionTopshow();
	afx_msg void OnActionSpecial();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnAutorun();
	afx_msg void OnShownews();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
