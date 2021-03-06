// DownloadAddress.cpp : implementation file
//////////////////////////////////////////////////
//类名：CDownloadAddress
//功能：下载网页设置
//作者：徐景周(Johnny Xu, xujingzhou2016@gmail.com)
//组织：未来工作室(Future Studio)
//日期：2001.12.1
//////////////////////////////////////////////////
#include "stdafx.h"
#include "helptip.h"
#include "DownloadAddress.h"
// Download by http://www.codefans.net
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDownloadAddress dialog


CDownloadAddress::CDownloadAddress(CWnd* pParent /*=NULL*/)
	: CDialog(CDownloadAddress::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDownloadAddress)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDownloadAddress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDownloadAddress)
	DDX_Control(pDX, IDC_DOWNLOAD, m_Address);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Control(pDX, IDOK, m_Download);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDownloadAddress, CDialog)
	//{{AFX_MSG_MAP(CDownloadAddress)
	ON_BN_CLICKED(IDOK, OnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDownloadAddress message handlers
//********************************************************************************
//* 名称：OnInitDialog()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：初始化下载网页对话框
//********************************************************************************
BOOL CDownloadAddress::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//网页下载设置对话框中，初始化阴影位图按钮
    m_Download.SetTextColor(RGB(0,0,0));
	m_Download.SetToolTipText("下载");  
	m_Download.SetShade(SHS_NOISE,33);  //(SHS_HARDBUMP,10,20,5,RGB(55,55,255));

	m_Cancel.SetTextColor(RGB(0,0,0));
	m_Cancel.SetToolTipText("取消");  
	m_Cancel.SetShade(SHS_NOISE,33);  	

	m_strAddress="";

	m_Address.SetWindowText("http://");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//********************************************************************************
//* 名称：OnOk()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：下载网页
//********************************************************************************
void CDownloadAddress::OnOk() 
{
	m_Address.GetWindowText(m_strAddress);

	if (m_strAddress =="")
	{
		AfxMessageBox("\n 抱歉,下载网址不能为空! ");
		return ;
	}

	CString szHTTP	= m_strAddress;
	szHTTP	= szHTTP.Left(5);
	szHTTP.MakeUpper();

	//增加一个合法的网址头
	if(szHTTP	!=	_T("HTTP:")) 
		m_strAddress	=	_T("HTTP://") + m_strAddress;

	CDialog::OnOK();	//关闭此对话框，必须加入，否则不能返回IDOK

}

//********************************************************************************
//* 名称：GetDownloadAddress()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：获取当前网页下载地址
//********************************************************************************
CString CDownloadAddress::GetDownloadAddress()  
{
	
	return m_strAddress;
}
