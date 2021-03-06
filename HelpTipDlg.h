/////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////
//类名：CHelpTipDlg
//功能：退出对话框类
//作者：徐景周(Johnny Xu, xujingzhou2016@gmail.com)
//组织：未来工作室(Future Studio)
//日期：2001.12.1
//////////////////////////////////////////////////
#if !defined(AFX_HELPTIPDLG_H__ED065C1B_6C7A_4B99_B975_6917B9EA3731__INCLUDED_)
#define AFX_HELPTIPDLG_H__ED065C1B_6C7A_4B99_B975_6917B9EA3731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "xShadeButton.h"			//加入自绘式阴影位图按钮类
#include "HyperLink.h"				//超链接类

class CHelpTipDlg : public CDialog
{
// Construction
public:
	CHelpTipDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHelpTipDlg)
	enum { IDD = IDD_HELPTIP_DIALOG };
	CxShadeButton	m_OK;
	CxShadeButton	m_Cancel;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHelpTipDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHelpTipDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELPTIPDLG_H__ED065C1B_6C7A_4B99_B975_6917B9EA3731__INCLUDED_)
