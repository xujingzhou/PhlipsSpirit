// SetRing.cpp : implementation file
//////////////////////////////////////////////////
//类名：CSetRing
//功能：闹铃设置功能
//作者：徐景周(Johnny Xu, xujingzhou2016@gmail.com)
//组织：未来工作室(Future Studio)
//日期：2001.12.1
//////////////////////////////////////////////////
#include "stdafx.h"
#include "helptip.h"
#include "SetRing.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
// Download by http://www.codefans.net
/////////////////////////////////////////////////////////////////////////////
// CSetRing dialog


CSetRing::CSetRing(CWnd* pParent /*=NULL*/)
	: CDialog(CSetRing::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetRing)
	m_Time = CTime(2002,4,24,12,00,00);
	m_sNowTime = _T("");
	//}}AFX_DATA_INIT
}


void CSetRing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetRing)
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_Time);
	DDX_Text(pDX, IDC_STATIC_NOW, m_sNowTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetRing, CDialog)
	//{{AFX_MSG_MAP(CSetRing)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, OnDatetimechangeDatetimepicker1)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetRing message handlers
//********************************************************************************
//* 名称：OnInitDialog()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：初始化闹铃设置对话框
//********************************************************************************
BOOL CSetRing::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//启动计时器，一秒钟更新一次
    SetTimer(0,1000,NULL);	

	m_bSetRing = FALSE;

	//初始更新闹钟显示
	CTime nowtime = CTime::GetCurrentTime();
	m_sNowTime = nowtime.Format(_T("%Y-%m-%d %H:%M:%S"));

	m_Time = CTime(nowtime.GetYear(),nowtime.GetMonth(),nowtime.GetDay(),nowtime.GetHour(),nowtime.GetMinute(),nowtime.GetSecond());

	//闹铃设置对话框中，初始化阴影位图按钮
    m_OK.SetTextColor(RGB(0,0,0));
	m_OK.SetToolTipText("确定");  
	m_OK.SetShade(SHS_NOISE,33);  //(SHS_HARDBUMP,10,20,5,RGB(55,55,255));

	m_Cancel.SetTextColor(RGB(0,0,0));
	m_Cancel.SetToolTipText("取消");  
	m_Cancel.SetShade(SHS_NOISE,33);  
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//********************************************************************************
//* 名称：OnDatetimechangeDatetimepicker1()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：更新时间控件显示
//********************************************************************************
void CSetRing::OnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(true);	//更新控件显示

	*pResult = 0;
}

//********************************************************************************
//* 名称：OnTimer()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：更新当前时间
//********************************************************************************
void CSetRing::OnTimer(UINT nIDEvent) 
{

    CTime nowtime = CTime::GetCurrentTime();
	m_sNowTime = nowtime.Format(_T("%Y-%m-%d %H:%M:%S"));

	UpdateData(FALSE);

	CDialog::OnTimer(nIDEvent);
}

//********************************************************************************
//* 名称：OnOK()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：选中定时闹铃
//********************************************************************************
void CSetRing::OnOK() 
{
	m_bSetRing = TRUE;

	CDialog::OnOK();
}

//********************************************************************************
//* 名称：GetCurRingTime()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：获取当前闹铃设置时间
//********************************************************************************
CTime CSetRing::GetCurRingTime()        
{
	if(m_bSetRing)
		return m_Time;
	else
		return NULL;
}