// About.h : header file
//////////////////////////////////////////////////
//类名：CAbout
//功能：关于对话框实现
//作者：徐景周(Johnny Xu, xujingzhou2016@gmail.com)
//组织：未来工作室(Future Studio)
//日期：2001.12.1
//////////////////////////////////////////////////
#if !defined(AFX_ABOUT_H__5EB3DF73_66D5_47FE_951D_106E932070F4__INCLUDED_)
#define AFX_ABOUT_H__5EB3DF73_66D5_47FE_951D_106E932070F4__INCLUDED_
// Download by http://www.codefans.net
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAbout dialog

#include "CreditStatic.h"			//加入荣誉效果显示
#include "xShadeButton.h"			//加入自绘式阴影位图按钮类

class CAbout : public CDialog
{
// Construction
public:
	CAbout(CWnd* pParent = NULL);   // standard constructor

	//伸展或收缩对话框 
	void SizeWindow(int ReduceHeight, bool bExtend);      
	
	//"关于"对话框动态显示
	int dx,dy;						//偏移量
	int nWidth,nHeight;				//窗体宽、高

	//"关于"对话框中的荣誉显示
	int m_nReducedHeight;			//收缩状态下的窗口高度 
	
	bool m_bVertical;				//是否显示荣誉标志

// Dialog Data
	//{{AFX_DATA(CAbout)
	enum { IDD = IDD_ABOUT };
	CCreditStatic	m_DyCredits;	//荣誉显示效果
	CxShadeButton	m_OK;
	CxShadeButton	m_More;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAbout)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAbout)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMore();
	virtual BOOL OnInitDialog();
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABOUT_H__5EB3DF73_66D5_47FE_951D_106E932070F4__INCLUDED_)
