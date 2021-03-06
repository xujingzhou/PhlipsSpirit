// SetRing.h : header file
//////////////////////////////////////////////////
//类名：CSetRing
//功能：闹铃设置功能
//作者：徐景周(Johnny Xu, xujingzhou2016@gmail.com)
//组织：未来工作室(Future Studio)
//日期：2001.12.1
//////////////////////////////////////////////////
#if !defined(AFX_SETRING_H__14F520C7_12F7_4950_806C_FB3791EC4F11__INCLUDED_)
#define AFX_SETRING_H__14F520C7_12F7_4950_806C_FB3791EC4F11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "xShadeButton.h"			//加入自绘式阴影位图按钮类

/////////////////////////////////////////////////////////////////////////////
// CSetRing dialog

class CSetRing : public CDialog
{
// Construction
public:
	CSetRing(CWnd* pParent = NULL);   // standard constructor

	BOOL m_bSetRing;                  //闹铃设置标志位

	CTime GetCurRingTime();           //获取当前闹铃设置时间

// Dialog Data
	//{{AFX_DATA(CSetRing)
	enum { IDD = IDD_SETRING };
	CxShadeButton	m_OK;
	CxShadeButton	m_Cancel;
	CTime	m_Time;
	CString	m_sNowTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetRing)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetRing)
	virtual BOOL OnInitDialog();
	afx_msg void OnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETRING_H__14F520C7_12F7_4950_806C_FB3791EC4F11__INCLUDED_)
