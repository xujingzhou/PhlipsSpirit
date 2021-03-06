/////////////////////////////////////////////////////////////////////////////
// Advertise dialog
//////////////////////////////////////////////////
//类名：CAdvertise
//功能：广告对话框实现
//作者：徐景周(Johnny Xu, xujingzhou2016@gmail.com)
//组织：未来工作室(Future Studio)
//日期：2001.12.1
//////////////////////////////////////////////////
#if !defined(AFX_ADVERTISE_H__6E5E575F_52F9_48A5_A9BB_626351F98435__INCLUDED_)
#define AFX_ADVERTISE_H__6E5E575F_52F9_48A5_A9BB_626351F98435__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define BACKWIDTH 148  // 窗体高度(既背景位图高度)
#define BACKHEIGHT 40  // 窗体宽度(既背景位图宽度)

class CAdvertise : public CDialog
{
// Construction
public:
	CAdvertise(CWnd* pParent = NULL);   // standard constructor

	void  TransparentRegion(CDC *pDC); //透明窗体区域
	CRect GetTrayWndRect();			   //获取系统区范围大小

	CBitmap	m_bmpDraw;
	HCURSOR m_Cursor;                  //鼠标经过窗体时的手形光标
// Dialog Data
	//{{AFX_DATA(Advertise)
	enum { IDD = IDD_DIALOG_ADVERTISE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Advertise)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Advertise)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADVERTISE_H__6E5E575F_52F9_48A5_A9BB_626351F98435__INCLUDED_)
