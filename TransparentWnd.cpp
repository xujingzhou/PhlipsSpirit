//////////////////////////////////////////////////
//类名：CTransparentWnd
//功能：透明窗体实现
//作者：徐景周(Johnny Xu, xujingzhou2016@gmail.com)
//组织：未来工作室(Future Studio)
//日期：2001.12.1
//////////////////////////////////////////////////
#include "stdafx.h"
#include "TransparentWnd.h"
#include <assert.h>
#include "HelpTip.h"
#include "HelpTipDlg.h"
#include "DownloadAddress.h"
#include "About.h"
#include "SetRing.h"
#include "Advertise.h"
#include "Splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMER_SET			1
#define TIMER_WALK			2
#define TIMER_IDLE			3
#define TIMER_RUN			4
#define TIMER_PLAYSOUND		5
#define TIMER_DRAGDROP		6
#define TIMER_TRANSFORM     7
#define TIMER_SETRING       8
#define TIMER_FALL          9

#define WM_TRAYNOTIFY WM_USER + 100  //自定义系统托盘消息函数

CAdvertise *m_pADdlg ;				 //广告窗体
//设置开机程序自启动键值位置和其下新建子键值(可设为程序名)
const TCHAR gcszAutoRunKey[]= _T( "Software\\Microsoft\\windows\\CurrentVersion\\Run" );
const TCHAR	gcszWindowClass[] = _T("Man");
//********************************************************************************
//* 名称：CTransparentWnd()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：构造涵数，在此初始化变量
//********************************************************************************
CTransparentWnd::CTransparentWnd()
{
	m_iAniSeq=0;
	strPath="";	
	m_bSuccess=FALSE;
}

//********************************************************************************
//* 名称：~CTransparentWnd()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：析构涵数，可在此删除创建的变量
//********************************************************************************
CTransparentWnd::~CTransparentWnd()
{
	//消毁广告窗体
	if ( m_pADdlg != NULL )
	{
		delete m_pADdlg;
		m_pADdlg = NULL;
 	}
}

BEGIN_MESSAGE_MAP(CTransparentWnd, CWnd)
	//{{AFX_MSG_MAP(CTransparentWnd)
	ON_MESSAGE(WM_TRAYNOTIFY, OnTrayNotification)  //自定义系统托盘消息涵数 
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(IDR_EXIT, OnExit)
	ON_COMMAND(IDR_FULLSCREEN_WALK, OnFullscreenWalk)
	ON_UPDATE_COMMAND_UI(IDR_FULLSCREEN_WALK, OnUpdateFullscreenWalk)
	ON_COMMAND(IDR_SHOWHIDE, OnShowhide)
	ON_WM_INITMENUPOPUP()
	ON_COMMAND(IDR_DOWNLOAD, OnDownload)
	ON_COMMAND(IDR_ACTION_RUN, OnActionRun)
	ON_COMMAND(IDR_ACTION_WALK, OnActionWalk)
	ON_COMMAND(IDR_ACTION_IDLE, OnActionIdle)
	ON_WM_MEASUREITEM()
	ON_WM_MENUCHAR()
	ON_COMMAND(IDR_ABOUT, OnAbout)
	ON_WM_LBUTTONUP()
	ON_COMMAND(IDR_OPTION_MUTE, OnOptionMute)
	ON_COMMAND(IDR_OPTION_REST, OnOptionRest)
	ON_COMMAND(IDR_OPTION_TOPSHOW, OnOptionTopshow)
	ON_COMMAND(IDR_ACTION_SPECIAL, OnActionSpecial)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(IDR_AUTORUN, OnAutorun)
	ON_COMMAND(IDR_SHOWNEWS, OnShownews)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//********************************************************************************
//* 名称：CreateTransparent()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：建立透明窗体
//********************************************************************************
void CTransparentWnd::CreateTransparent(LPCTSTR pTitle, RECT &rect)
{
	CreateEx(	0,
		AfxRegisterWndClass(0,AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
						pTitle,
						WS_POPUP ,
						rect,
						NULL,
						NULL,
						NULL );

}

//********************************************************************************
//* 名称：GetSourceHtml()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：下载网页涵数
//********************************************************************************
BOOL CTransparentWnd::GetSourceHtml(CString theUrl,CString Filename) 
{
 CInternetSession session;
 CInternetFile* file = NULL;
 try
 {
    // 试着连接到指定URL
    file = (CInternetFile*) session.OpenURL(theUrl); 
 }
 catch (CInternetException* m_pException)
 {
    // 如果有错误的话，置文件为空
    file = NULL; 
    m_pException->Delete();
    return FALSE;
 }

 // 用dataStore来保存读取的网页文件
 CStdioFile dataStore;

 if (file)
 {
    CString  somecode;							//也可采用LPTSTR类型，将不会删除文本中的\n回车符

	BOOL bIsOk = dataStore.Open(strPath+"\\"+Filename,
		CFile::modeCreate 
		| CFile::modeWrite 
		| CFile::shareDenyWrite 
		| CFile::typeText);
	
	if (!bIsOk)
		return FALSE;
	
	// 读写网页文件，直到为空
	while (file->ReadString(somecode) != NULL) //如果采用LPTSTR类型，读取最大个数nMax置0，使它遇空字符时结束
	{
		dataStore.WriteString(somecode);
		dataStore.WriteString("\n");		   //如果somecode采用LPTSTR类型,可不用此句
	}
	
	file->Close();
	delete file;
 }
 else
 {
    dataStore.WriteString(_T("到指定服务器的连接建立失败..."));	
    return FALSE;
 }

 return TRUE;
}

//********************************************************************************
//* 名称：SoundPlay()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：播放内镶WAV声音文件
//********************************************************************************
void CTransparentWnd::SoundPlay(void)
{
    //先关闭原声音播放
	PlaySound("IDR_WAVE",AfxGetResourceHandle(),SND_RESOURCE|SND_PURGE|SND_NODEFAULT  ); 
    //设置播放声音时间0.84秒
	SetTimer(TIMER_PLAYSOUND,840,NULL); 
	//资源WAV文件的ID须加双引号，用下API函数播放
    PlaySound("IDR_WAVE",AfxGetResourceHandle(),SND_RESOURCE|SND_ASYNC|SND_NODEFAULT  ); 
}

//********************************************************************************
//* 名称：SetupRegion()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：将窗体背景透明化(新的透明算法)
//********************************************************************************
void CTransparentWnd::SetupRegion(CDC *pDC)
{

	HRGN hRgn = NULL;

	CBitmap			&cBitmap=m_bmpDraw;
	CRect			cRect;

	GetWindowRect(&cRect);
	CPoint ptOrg=cRect.TopLeft();

	// 获取位图大小
	BITMAP bm;
	cBitmap.GetObject(sizeof(bm),&bm);
	CRect rcNewWnd=CRect(ptOrg,CSize(bm.bmWidth,bm.bmHeight));

		// 创建兼容DC，只便扫描它的元素
		HDC hMemDC = CreateCompatibleDC(NULL);
		if (hMemDC)
		{
			// 创建一32位位图，并放到兼容DC中 
			BITMAPINFOHEADER RGB32BITSBITMAPINFO = {	
					sizeof(BITMAPINFOHEADER),	// biSize 
					bm.bmWidth,					// biWidth; 
					bm.bmHeight,				// biHeight; 
					1,							// biPlanes; 
					32,							// biBitCount 
					BI_RGB,						// biCompression; 
					0,							// biSizeImage; 
					0,							// biXPelsPerMeter; 
					0,							// biYPelsPerMeter; 
					0,							// biClrUsed; 
					0							// biClrImportant; 
			};
			VOID * pbits32; 
			HBITMAP hbm32 = CreateDIBSection(hMemDC, (BITMAPINFO *)&RGB32BITSBITMAPINFO, DIB_RGB_COLORS, &pbits32, NULL, 0);
			if (hbm32)
			{
				HBITMAP holdBmp = (HBITMAP)SelectObject(hMemDC, hbm32);

				// 创建DC，放位图到它里面
				HDC hDC = CreateCompatibleDC(hMemDC);
				if (hDC)
				{
					// 获取每行多少位
					BITMAP bm32;
					GetObject(hbm32, sizeof(bm32), &bm32);
					while (bm32.bmWidthBytes % 4)
						bm32.bmWidthBytes++;

					// 复制位图到兼容DC中
					HBITMAP holdBmp = (HBITMAP)SelectObject(hDC, (HBITMAP)cBitmap );
					BitBlt(hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, hDC, 0, 0, SRCCOPY);

					COLORREF cTolerance = 0x101010;
					COLORREF cTransparentColor=::GetPixel(hDC,0,0);

					// 为了更好的实现，将使用 ExtCreateRegion() 涵数来创建一区域，这个涵数要用来
					// RGNDATA 结构. 我们将用ALLOC_UNI来添加矩形框。
					#define ALLOC_UNIT	100
					DWORD maxRects = ALLOC_UNIT;
					HANDLE hData = GlobalAlloc(GMEM_MOVEABLE, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects));
					RGNDATA *pData = (RGNDATA *)GlobalLock(hData);
					pData->rdh.dwSize = sizeof(RGNDATAHEADER);
					pData->rdh.iType = RDH_RECTANGLES;
					pData->rdh.nCount = pData->rdh.nRgnSize = 0;
					SetRect(&pData->rdh.rcBound, MAXLONG, MAXLONG, 0, 0);

					// 为了获得透明像素，要分别保留其要透明背景色的最高、最低值
					BYTE lr = GetRValue(cTransparentColor);
					BYTE lg = GetGValue(cTransparentColor);
					BYTE lb = GetBValue(cTransparentColor);
					BYTE hr = min(0xff, lr + GetRValue(cTolerance));
					BYTE hg = min(0xff, lg + GetGValue(cTolerance));
					BYTE hb = min(0xff, lb + GetBValue(cTolerance));

					// 从下往上扫描每一个位图(位图是竖直反方向的)
					BYTE *p32 = (BYTE *)bm32.bmBits + (bm32.bmHeight - 1) * bm32.bmWidthBytes;
					for (int y = 0; y < bm.bmHeight; y++)
					{
						// 从左往右扫描每一个像素
						for (int x = 0; x < bm.bmWidth; x++)
						{
							// 连续搜索非透明元素
							int x0 = x;
							LONG *p = (LONG *)p32 + x;
							while (x < bm.bmWidth)
							{
								BYTE b = GetRValue(*p);
								if (b >= lr && b <= hr)
								{
									b = GetGValue(*p);
									if (b >= lg && b <= hg)
									{
										b = GetBValue(*p);
										if (b >= lb && b <= hb)
											// 如果是透明元素的话
											break;
									}
								}
								p++;
								x++;
							}

							if (x > x0)
							{
								// 添加像素(x0, y) 到 (x, y+1) ，作为区域中的新矩形
								if (pData->rdh.nCount >= maxRects)
								{
									GlobalUnlock(hData);
									maxRects += ALLOC_UNIT;
									hData = GlobalReAlloc(hData, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects), GMEM_MOVEABLE);
									pData = (RGNDATA *)GlobalLock(hData);
								}
								RECT *pr = (RECT *)&pData->Buffer;
								SetRect(&pr[pData->rdh.nCount], x0, y, x, y+1);
								if (x0 < pData->rdh.rcBound.left)
									pData->rdh.rcBound.left = x0;
								if (y < pData->rdh.rcBound.top)
									pData->rdh.rcBound.top = y;
								if (x > pData->rdh.rcBound.right)
									pData->rdh.rcBound.right = x;
								if (y+1 > pData->rdh.rcBound.bottom)
									pData->rdh.rcBound.bottom = y+1;
								pData->rdh.nCount++;

								// 在Windows98中, 如果矩形数太多的话(ie: > 4000)，ExtCreateRegion()涵数可能失败. 
								//　因此，我们必须通过多步来创建矩形。
								if (pData->rdh.nCount == 2000)
								{
									HRGN h = ExtCreateRegion(NULL, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects), pData);
									if (hRgn)
									{
										CombineRgn(hRgn, hRgn, h, RGN_OR);
										DeleteObject(h);
									}
									else
										hRgn = h;
									pData->rdh.nCount = 0;
									SetRect(&pData->rdh.rcBound, MAXLONG, MAXLONG, 0, 0);
								}
							}
						}

						// 到下一行(注意： 位图是竖直反方向的)
						p32 -= bm32.bmWidthBytes;
					}

					// 根据保留的矩形来创建或廷伸区域
					HRGN h = ExtCreateRegion(NULL, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects), pData);
					if (hRgn)
					{
						CombineRgn(hRgn, hRgn, h, RGN_OR);
						DeleteObject(h);
					}
					else
						hRgn = h;

					// 释放
					GlobalFree(hData);
					SelectObject(hDC, holdBmp);
					DeleteDC(hDC);
				}

				DeleteObject(SelectObject(hMemDC, holdBmp));
			}

			DeleteDC(hMemDC);
		}	

	SetWindowRgn(hRgn, TRUE);
	MoveWindow(rcNewWnd);
}

//********************************************************************************
//* 名称：DoSet()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：判断该进行何种运行方式
//********************************************************************************
void CTransparentWnd::DoSet(void)
{
	int iSW=GetSystemMetrics(SM_CXFULLSCREEN);
	int	iSH=GetSystemMetrics(SM_CYFULLSCREEN);

	KillTimer(TIMER_SET);
	switch(rand()%5)
	{
		case(0):  //散步
		case(1):
		case(2):
		m_ptDest.x=rand()%(iSW - 10);
		m_ptDest.y=rand()%(iSH - 10);
		SetTimer(TIMER_WALK,150,NULL);
		break;
		  
		case(3):  //奔跑
		SetTimer(TIMER_TRANSFORM,300,NULL); //改原奔跑为变形状态 
//		m_ptDest.x=rand()%(iSW - 10);
//		m_ptDest.y=rand()%(iSH - 10);		
//		SetTimer(TIMER_RUN,500,NULL);
		break;

	    case(4):  //休息
		SetTimer(TIMER_IDLE,300,NULL);      
		break;
	}

}

//********************************************************************************
//* 名称：DoWalk()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：散步
//********************************************************************************
void CTransparentWnd::DoWalk(void)
{
	if(!m_bRest)							  //如果不是静止的话
	{
		char szBmp[20];
		CRect rcW;
		GetWindowRect(rcW);
		
		//决定全屏或局部运动的范围,暂只考虑任务条在下方时情况
		if(m_bFullScreenWalk)
		{
			if((m_ptDest.x> rcW.left && m_ptDest.x < rcW.right)||(m_ptDest.y> rcW.top && m_ptDest.y < rcW.bottom ))
			{
				KillTimer(TIMER_WALK);		
				SetTimer(TIMER_SET,10,NULL);
				return;
			}
			
			//设置精灵行走步长
			CPoint ptOffset((m_ptDest.x > rcW.left)?5:-5,(m_ptDest.y > rcW.top)?5:-5);
			
			rcW+=ptOffset;
			MoveWindow(rcW);
			
			if(m_ptDest.x<rcW.left)		//向左运动
			{
				sprintf(szBmp,"WALK%d",m_iAniSeq%12+1);
				m_iLastDirection=1;
			}
			else						//向右运动
			{
				sprintf(szBmp,"WALK%d",m_iAniSeq%12+13);
				m_iLastDirection=2;
			}
			
		}
		else
		{
			int xcounter=5,ycounter=5;	//设置精灵行走步长
			
			m_Rect=GetTopWndTitleRect();
			if(rcW.left < m_Rect.left +30 || m_iLastDirection==2) 
			{
				xcounter=5;
				m_iLastDirection=2;
			}
			if(rcW.left > m_Rect.right -30 || m_iLastDirection==1)
			{
				xcounter=-5;
				m_iLastDirection=1;
			}
			ycounter=0;                       //上、下位置不变
			
			rcW.top =m_Rect.top-rcW.Height();
			rcW.bottom =m_Rect.top;
			
			CPoint ptOffset(xcounter,ycounter);
			rcW+=ptOffset;
			
			MoveWindow(rcW);
			
			if((m_iAniSeq%80)==0)           //局部运动时，往右为奔跑
			{
				KillTimer(GetCurAction());
				SetTimer(TIMER_IDLE,300,NULL);	
			}
			else if((m_iAniSeq%30)==0)
			{
				KillTimer(GetCurAction());
				SetTimer(TIMER_TRANSFORM,300,NULL);	
			}
			
			if(m_iLastDirection==1)			  //向左运动
			{
				sprintf(szBmp,"WALK%d",m_iAniSeq%12+1);
			}
			else							  //向右运动
			{
				sprintf(szBmp,"WALK%d",m_iAniSeq%12+13);
			}
		}
		
		int CurAction;
		if((CurAction=GetCurAction())!=TIMER_WALK)
			KillTimer(CurAction);

		m_bmpDraw.DeleteObject();
		m_bmpDraw.LoadBitmap(szBmp);
		CWindowDC dc(this);
		SetupRegion(&dc);
		Invalidate();
	}
}

//********************************************************************************
//* 名称：DoRun()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：奔跑
//********************************************************************************
void CTransparentWnd::DoRun(void)
{
	if(!m_bRest)				//如果不是静止的话
	{
		char szBmp[20];
		CRect rcW;
		GetWindowRect(rcW);
		
		//决定全屏或局部运动的范围,暂只考虑任务条在下方时情况
		if(m_bFullScreenWalk)
		{
			if((m_ptDest.x> rcW.left && m_ptDest.x < rcW.right)||(m_ptDest.y> rcW.top && m_ptDest.y < rcW.bottom ))
			{
				KillTimer(TIMER_RUN);
				SetTimer(TIMER_SET,10,NULL);
				return;
			}
			CPoint ptOffset((m_ptDest.x > rcW.left)?10:-10,(m_ptDest.y > rcW.top)?5:-5);
			rcW+=ptOffset;
			MoveWindow(rcW);
			
			if(m_ptDest.x<rcW.left)  //向左运动
			{
				sprintf(szBmp,"RUN%d",m_iAniSeq%5+1);
				m_iLastDirection=1;
			}
			else                     //向右运动
			{
				sprintf(szBmp,"RUN%d",m_iAniSeq%5+6);
				m_iLastDirection=2;
			}
		}
		else
		{
			int xcounter=10,ycounter=10;
			
			m_Rect=GetTopWndTitleRect();
			if(rcW.left < m_Rect.left +30 || m_iLastDirection==2) 
			{
				xcounter=10;
				m_iLastDirection=2;
			}
			if(rcW.left > m_Rect.right -30 || m_iLastDirection==1)
			{
				xcounter=-10;
				m_iLastDirection=1;
			}
			ycounter=0;                        //上、下位置不变
			
			rcW.top =m_Rect.top-rcW.Height();
			rcW.bottom =m_Rect.top;
			
			CPoint ptOffset(xcounter,ycounter);
			rcW+=ptOffset;
			
			MoveWindow(rcW);
			
			if(m_iLastDirection==1)				//局部运动时，往左为散步
			{
				KillTimer(GetCurAction());
				SetTimer(TIMER_WALK,150,NULL);	
			}
			else if((m_iAniSeq%30)==0)
			{
				KillTimer(GetCurAction());
				SetTimer(TIMER_IDLE,300,NULL);
			}
			
			if(m_iLastDirection==1)				//向左运动
			{
				sprintf(szBmp,"RUN%d",m_iAniSeq%5+1);
			}
			else							    //向右运动
			{
				sprintf(szBmp,"RUN%d",m_iAniSeq%5+6);
			}
		}
		
		m_bmpDraw.DeleteObject();
		m_bmpDraw.LoadBitmap(szBmp);
		CWindowDC dc(this);
		SetupRegion(&dc);
		Invalidate();
	}
}

//********************************************************************************
//* 名称：DoIdle()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：休息
//********************************************************************************
void CTransparentWnd::DoIdle(void)
{
	if(!m_bRest)						  //如果不是静止的话
	{
		CWnd * pFrame;					  //得到当前窗体指针
		
		//是否局部运动范围,暂只考虑任务条在下方时情况
		if(!m_bFullScreenWalk)
		{
			CRect rcW;
			GetWindowRect(rcW);
			m_Rect=GetTopWndTitleRect();
			
			rcW.top =m_Rect.top-rcW.Height();
			rcW.bottom =m_Rect.top;
			MoveWindow(rcW);
		}
		
		pFrame=AfxGetApp()->GetMainWnd();
		if(m_iAniSeq%12==0 && pFrame->IsWindowVisible())
		{
			
			//显示提示窗信息
			CRect rc;
			GetWindowRect(&rc);
			CPoint pt;
			pt.x=rc.left +rc.Width ()/2;
			pt.y=rc.top;
			if(m_bRing)						       //闹铃时提示窗
			{
				m_Tip.Show(_T("时间到了，该起床了!"),&pt);

				if(!m_bMute)
					SoundPlay();			        //播放声音    
			}
			else if(m_bDownloadFailed)		        //在线提示窗
			{
				if(m_bShowNews)                     //显示新闻标志为真
				{
					CString str;

					if(m_sdFile.ReadString(str) == NULL)
					{
						m_sdFile.SeekToBegin();
						m_sdFile.ReadString(str);
					}
					str.Replace("&&",_T("\n"));     //处理字符串换行标志"&&"，多行显示
					m_Tip.SetHideDelay(10000);      //显示10秒
					m_Tip.Show(str,&pt);		    //作者注：同一行中显示的字数不能过大
					
					if(!m_bMute)
						SoundPlay();			    //播放声音   
				}
				else
				{
					m_Tip.SetHideDelay(100);
					m_Tip.Hide();
				}   
			}
//			else									//断线时提示窗
//				m_Tip.Show(_T("欢迎您，来到未来工作室！"),&pt);
			
			m_Tip.Hide();

			m_iSecondNum++;
		}

		if( m_bDownloadFailed && m_bShowNews)        //在线时
		{
			if(m_iSecondNum >= 10 )					 //(>=10)秒时关闭它，不再显示提示窗
			{
				m_Tip.SetHideDelay(100); 
				m_Tip.Hide();
				KillTimer(TIMER_IDLE);
				SetTimer(TIMER_SET,100,NULL);
				m_iSecondNum = 0;
				
				return;
			}
		}
		else
		{
			if(m_iSecondNum >= 1 )					//(>=1)秒时关闭它，不再显示提示窗
			{
				m_Tip.SetHideDelay(100); 
				m_Tip.Hide();
				KillTimer(TIMER_IDLE);
				SetTimer(TIMER_SET,100,NULL);
				m_iSecondNum = 0;
				
				return;
			}
		}
		
		int CurAction;
		if((CurAction=GetCurAction())!=TIMER_IDLE)
			KillTimer(CurAction);

		char szBmp[20];	
		sprintf(szBmp,"IDLE%d",m_iAniSeq%4+1);
		
		m_bmpDraw.DeleteObject();
		m_bmpDraw.LoadBitmap(szBmp);
		CWindowDC dc(this);
		SetupRegion(&dc);
		Invalidate();
	}
}

//********************************************************************************
//* 名称：DoTransform()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：变形行为表现
//********************************************************************************
void CTransparentWnd::DoTransform(void)                
{
	if(!m_bRest)          //如果不是静止的话
	{
		char szBmp[20];	
		sprintf(szBmp,"TRANSFORM%d",m_iAniSeq%13+1);
		
		if(strcmp(szBmp,"TRANSFORM13")==0)
		{
			KillTimer(TIMER_TRANSFORM);
			SetTimer(TIMER_SET,10,NULL);
			return;
		}
		
		//是否局部运动的范围,暂只考虑任务条在下方时情况
		if(!m_bFullScreenWalk)
		{
			CRect rcW;
			GetWindowRect(rcW);
			m_Rect=GetTopWndTitleRect();
			
			rcW.top =m_Rect.top-rcW.Height();
			rcW.bottom =m_Rect.top;
			MoveWindow(rcW);
		}
		
		int CurAction;
		if((CurAction=GetCurAction())!=TIMER_TRANSFORM)
			KillTimer(CurAction);

		m_bmpDraw.DeleteObject();
		m_bmpDraw.LoadBitmap(szBmp);
		CWindowDC dc(this);
		SetupRegion(&dc);
		Invalidate();
	}
}

//********************************************************************************
//* 名称：DoDrag()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：拖动窗体时行为表现
//********************************************************************************
void CTransparentWnd::DoDrag(void)
{

	CRect rcW;
	POINT point;
	GetWindowRect(rcW);

	//实现拖动时窗体跟着移动
    ::GetCursorPos(&point);			
	MoveWindow(point.x-m_ptCurPoint.x ,point.y-m_ptCurPoint.y ,rcW.Width(),rcW.Height() ,true); 

	char szBmp[20];

	sprintf(szBmp,"SLING%d",m_iAniSeq%8+1);

	m_bmpDraw.DeleteObject();
	m_bmpDraw.LoadBitmap(szBmp);
	CWindowDC dc(this);
	SetupRegion(&dc);
	Invalidate();

}

//********************************************************************************
//* 名称：DoFall()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：拖动后的下落表现
//********************************************************************************
void CTransparentWnd::DoFall(void)
{
	CRect rcW,m_Rect;
	GetWindowRect(&rcW);
	
	m_Rect=GetTopWndTitleRect();
	if( rcW.bottom >= m_Rect.top )
	{
		KillTimer(TIMER_FALL);
		SetTimer(TIMER_SET,10,NULL);
		return;
	}

	MoveWindow(rcW.left,rcW.top+10,rcW.Width(),rcW.Height(),true); 
}

//********************************************************************************
//* 名称：OnLButtonDown()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：实现窗体无标题拖动
//********************************************************************************
void CTransparentWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonDown(nFlags, point);

	KillTimer(GetCurAction());		   //关闭当前行为表现

	SetTimer(TIMER_DRAGDROP,60,NULL);  //打开拖动时计数器

	//鼠标移动到窗体时改变鼠标指针
	::SetCursor(AfxGetApp()->LoadCursor(IDC_DROP));

	m_bDragDrop=true;					//精灵助手拖动标志为真
	SetCapture();						//设置鼠标全屏捕捉
    m_ptCurPoint=point;					//记下按下时的鼠标坐标

//	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x,point.y));

}

//********************************************************************************
//* 名称：OnLButtonUp()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：实现窗体实时拖动效果
//********************************************************************************
void CTransparentWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	
	m_bDragDrop=false;				//精灵助手拖动标志为假
	ReleaseCapture();
	KillTimer(TIMER_DRAGDROP);		//关闭拖动时记数器 

	SetTimer(TIMER_FALL,100,NULL);  //启动下落表现
	
	CWnd::OnLButtonUp(nFlags, point);
}

//********************************************************************************
//* 名称：OnCreate()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：创建窗体
//********************************************************************************
int CTransparentWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//系统区显示的图标文件
	m_hIcon[0]=AfxGetApp()->LoadIcon(IDI_TRAYICON);
    
	//创建系统区图标
	if (!m_TrayIcon.Create(this, 
				IDR_POPUP, 
				_T("精灵信使 V1.0"), 
				m_hIcon, 
				1,							//一幅图像
				1000,						//延时1秒变化
				WM_TRAYNOTIFY))
	{
		AfxMessageBox(_T("错误：创建系统图标失败！"), MB_OK | MB_ICONSTOP);
		return -1;
	}

	// 建立信息提示窗
	m_Tip.Create(GetDesktopWindow());

	m_bShowNews = TRUE;                        //新闻显示初始为真
	m_bFullScreenWalk = TRUE;				   //全屏运动标志初始置真
	m_bMute = FALSE;                           //静音标志
	m_bTopShow = TRUE;                         //最顶层显示标志
	m_bRest = FALSE;                           //静止标志

	m_bRing = FALSE;                           //闹铃提示标志
	m_Time = NULL;                             //闹铃时间为空
	m_iAction = 1;							   //初始行为表现
	m_iSecondNum = 0;                          //初始秒数为0
	SetTimer(TIMER_SET,300,NULL);

	//窗体拖运时变量初始化
	m_bDragDrop=FALSE;  
	m_ptCurPoint=CPoint(0,0);

	//判断程序是否已设置了开机自启动选项
	HKEY hKey;
	LONG lRet;
	DWORD dwLength, dwDataType;
	TCHAR szBuffer[MAX_PATH];

	// 打开注册表键
	lRet = RegOpenKeyEx( HKEY_LOCAL_MACHINE, gcszAutoRunKey,
			0, KEY_READ | KEY_WRITE, &hKey );
	if( lRet != ERROR_SUCCESS )
		return FALSE;

	// 查询自动运行项目是否存在
	dwLength = sizeof( szBuffer );
	lRet = RegQueryValueEx( hKey, gcszWindowClass, 
			NULL, &dwDataType, (LPBYTE)szBuffer, &dwLength );
		
	if( lRet == ERROR_SUCCESS )
		m_bAutorun = TRUE;                     //已设置自动运行标志
	else
		m_bAutorun = FALSE;					   //没有设置自动运行标志


	//置窗体初始显示位置
	CRect rcW;
	GetWindowRect(&rcW);
	m_Rect=GetTopWndTitleRect();	
	rcW.top =m_Rect.top-rcW.Height();
	rcW.bottom =m_Rect.top;
	rcW.left =10;
	//置窗体为最顶层显示及其位置
	SetWindowPos(&wndTopMost,rcW.left,rcW.top,rcW.Width(),rcW.Height(),SWP_NOSIZE|SWP_NOMOVE);


	//获取主程序所在路径,存在全局变量strPath中
	GetModuleFileName(NULL,strPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);
	strPath.ReleaseBuffer ();
    int nPos;
	nPos=strPath.ReverseFind ('\\');
	strPath=strPath.Left (nPos);

	CFileFind  fFind;
	BOOL bFailed;
	bFailed=fFind.FindFile(strPath+"\\News.txt",0);
    //是否已下载提示文件，否则下载它并打开文件
	if(!bFailed)
		m_bDownloadFailed=GetSourceHtml("http://www.philips120dreams.com/member/pet_news/news.txt","News.txt");	//下载提示文件的默认网址
	else
		m_bDownloadFailed=TRUE;
    fFind.Close ();
	if(m_bDownloadFailed)
		m_bSuccess=m_bDownloadFailed=m_sdFile.Open(strPath+"\\News.txt",
		CFile::modeRead | CFile::typeText);


	//同时在系统区上面显示广告窗体，只能是无模式对话框
    m_pADdlg = new CAdvertise(this);
    m_pADdlg->Create(IDD_DIALOG_ADVERTISE,this);
	m_pADdlg->ShowWindow(SW_SHOW);


	return 0;
}

//********************************************************************************
//* 名称：OnTrayNotification()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：系统区创建的图标映射涵数
//********************************************************************************
LRESULT CTransparentWnd::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
  
  return m_TrayIcon.OnTrayNotification(wParam, lParam);
}

//********************************************************************************
//* 名称：OnEraseBkgnd()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：擦除背景
//********************************************************************************
BOOL CTransparentWnd::OnEraseBkgnd(CDC* pDC) 
{

	CRect	rect;
	GetWindowRect(&rect);

	CDC memDC;
	CBitmap			&cBitmap=m_bmpDraw;;
	CBitmap*		pOldMemBmp = NULL;
	CFont* pOldMemFont=NULL;

	memDC.CreateCompatibleDC(pDC);
	pOldMemBmp = memDC.SelectObject(&cBitmap);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	if (pOldMemBmp) memDC.SelectObject( pOldMemBmp );

	return TRUE;
}

//********************************************************************************
//* 名称：OnPaint()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：刷新背景
//********************************************************************************
void CTransparentWnd::OnPaint()
{
	CPaintDC dc(this);
	
}

//********************************************************************************
//* 名称：OnTimer()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：触发定时器
//********************************************************************************
void CTransparentWnd::OnTimer(UINT nIDEvent) 
{
	
	switch(nIDEvent)
	{
	case(1):				//判定何种运行方式
		DoSet();
		break;

	case(2):				//散步
		DoWalk();
		break;

	case(3):				//休息
		DoIdle();
		break;

	case(4):				//奔跑
		DoRun();
		break;

	case(5):				//播放声音
		KillTimer(TIMER_PLAYSOUND);
		break;

	case(6):
		DoDrag();			//实时拖动
		break;

	case(7):
		DoTransform();      //变形
		break;

	case(8):                //闹铃设置
		{
			int hour,min,sec;
			int yhour,ymin,ysec;
			
			CTime nowtime = CTime::GetCurrentTime();

			hour = nowtime.GetHour();
			min	 = nowtime.GetMinute();
			sec  = nowtime.GetSecond();
			
			yhour = m_Time.GetHour();
			ymin  = m_Time.GetMinute();
			ysec  = m_Time.GetSecond();
			
			//如果时间到，则进行闹铃
			if(hour == yhour && min == ymin && sec==ysec)
			{
				m_bRing = TRUE;
				OnActionIdle();            //用Idle行为来闹铃提示
			}
			else if(m_bRing==TRUE)         //关闭闹铃  	
			{		
				OnActionIdle();            //用Idle行为来闹铃提示
				
				if( m_iAniSeq%80 == 0)
				{
					KillTimer(TIMER_SETRING);
					m_bRing = FALSE;
				}
			}
		}
		break;

	case(9):
		DoFall();             //鼠标拖动释放后的下落表现
		break;

	default:
		break;
	}
	
	if(nIDEvent!=5 && nIDEvent!=6 && nIDEvent!=8)
		m_iAction= nIDEvent;    //当前行为表现方式标志

	m_iAniSeq++;				//下一幅图像       
	if(m_iAniSeq>156)           //13X12
		m_iAniSeq=0;    

	CWnd::OnTimer(nIDEvent);
}

//********************************************************************************
//* 名称：OnDestroy()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：销毁窗体
//********************************************************************************
void CTransparentWnd::OnDestroy() 
{
	CWnd::OnDestroy();
}

//********************************************************************************
//* 名称：OnRButtonDown()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：弹出相关菜单
//********************************************************************************
void CTransparentWnd::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CWnd::OnRButtonDown(nFlags, point);

	m_popmenu.LoadMenu(IDR_POPUP);
	BCMenu::SetMenuDrawMode(BCMENU_DRAWMODE_XP);

	//设置选中时的复选框效果
	if(m_bFullScreenWalk) 
		m_popmenu.ModifyODMenu(NULL, IDR_FULLSCREEN_WALK,IDB_CHECK);
	if(m_bMute)
		m_popmenu.ModifyODMenu(NULL, IDR_OPTION_MUTE,IDB_CHECK);
	if(m_bTopShow)
		m_popmenu.ModifyODMenu(NULL, IDR_OPTION_TOPSHOW,IDB_CHECK);
	if(m_bRest)
		m_popmenu.ModifyODMenu(NULL, IDR_OPTION_REST,IDB_CHECK);
	if(m_bAutorun)
		m_popmenu.ModifyODMenu(NULL, IDR_AUTORUN,IDB_CHECK);
	if(m_bShowNews)
		m_popmenu.ModifyODMenu(NULL, IDR_SHOWNEWS,IDB_CHECK);

	ClientToScreen(&point);
	BCMenu *psub = (BCMenu *)m_popmenu.GetSubMenu(0); 
	psub->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
	m_popmenu.DestroyMenu();
}

//********************************************************************************
//* 名称：PreTranslateMessage()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：传递提示窗消息
//********************************************************************************
BOOL CTransparentWnd::PreTranslateMessage(MSG* pMsg) 
{
	m_Tip.RelayEvent(pMsg);
	
	return CWnd::PreTranslateMessage(pMsg);
}

//********************************************************************************
//* 名称：PreTranslateMessage()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：在显示窗体动画效果前，先寻找系统区位置
//********************************************************************************
BOOL CALLBACK FindTrayWnd(HWND hwnd, LPARAM lParam)
{
    TCHAR szClassName[256];
    GetClassName(hwnd, szClassName, 255);

    // 比较窗口类名
    if (_tcscmp(szClassName, _T("TrayNotifyWnd")) == 0)
    {
        CRect *pRect = (CRect*) lParam;
        ::GetWindowRect(hwnd, pRect);
        return TRUE;
    }

    // 当找到时钟窗口时表示可以结束了
    if (_tcscmp(szClassName, _T("TrayClockWClass")) == 0)
    {
        CRect *pRect = (CRect*) lParam;
        CRect rectClock;
        ::GetWindowRect(hwnd, rectClock);
        pRect->right = rectClock.left;
        return FALSE;
    }
 
    return TRUE;
}

//********************************************************************************
//* 名称：PreTranslateMessage()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：显示窗口动画效果的涵数
//********************************************************************************
void CTransparentWnd::WinAnimation(BOOL ShowFlag) 
{
    CRect rect(0,0,0,0);

    // 查找托盘窗口 
    CWnd* pWnd = FindWindow("Shell_TrayWnd", NULL);
    if (pWnd)
    {
        pWnd->GetWindowRect(rect);
		EnumChildWindows(pWnd->m_hWnd, FindTrayWnd, (LPARAM)&rect);
		//rect 为托盘区矩形
		CRect rcWnd;
		GetWindowRect(rcWnd);
		if(ShowFlag)					//窗体滑向系统区
		  DrawAnimatedRects(IDANI_CAPTION,rcWnd,rect);
		else							//窗体从系统区滑出
		  DrawAnimatedRects(IDANI_CAPTION,rect,rcWnd);
    }
}

//********************************************************************************
//* 名称：OnExit()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：退出程序
//********************************************************************************
void CTransparentWnd::OnExit()  
{
/*
	CHelpTipDlg dlg;

	//保证此对话框一次只弹出一个
	if( !FindWindow(NULL,"退出"))
	{
		if(IDCANCEL==dlg.DoModal())
		{
			m_TrayIcon.RemoveIcon();          //删除系统区图标
			
			DestroyWindow();
		}
	}
*/
	CHelpTipDlg dlg;

	m_Tip.SetHideDelay(100);     //隐藏提示窗
	m_Tip.Hide();

	dlg.DoModal();
	m_TrayIcon.RemoveIcon();     //删除系统区图标

	if(m_bAutorun)
	{
		//设置为开机自动运行　
		StartupAutorun(TRUE);
	}
	else
	{
		//取消开机自动运行　
		StartupAutorun(FALSE);
	}

	DestroyWindow();
}

//********************************************************************************
//* 名称：OnOptionMute()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：静音
//********************************************************************************
void CTransparentWnd::OnOptionMute() 
{
	m_bMute = !m_bMute;;   

}   

//********************************************************************************
//* 名称：OnOptionRest()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：静止
//********************************************************************************
void CTransparentWnd::OnOptionRest() 
{
	m_bRest = !m_bRest;
	
}

//********************************************************************************
//* 名称：OnOptionTopshow()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：顶层显示
//********************************************************************************
void CTransparentWnd::OnOptionTopshow() 
{
	m_bTopShow = !m_bTopShow;
	
}

//********************************************************************************
//* 名称：OnFullscreenWalk()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：全屏运动还是局部运动
//********************************************************************************
void CTransparentWnd::OnFullscreenWalk() 
{
	m_bFullScreenWalk = !m_bFullScreenWalk;	

}

//********************************************************************************
//* 名称：OnUpdateFullscreenWalk()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：更新全屏运动还是局部运动
//********************************************************************************
void CTransparentWnd::OnUpdateFullscreenWalk(CCmdUI* pCmdUI) 
{
	if(m_bFullScreenWalk) 
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);	
}

//********************************************************************************
//* 名称：OnShowhide()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：显示或隐藏精灵助手
//********************************************************************************
void CTransparentWnd::OnShowhide() 
{
	CWnd * pFrame;					 //得到当前窗体指针

	pFrame=AfxGetApp()->GetMainWnd();
	if(!pFrame->IsWindowVisible())	 //是否进行窗体动画,窗体已显示则不进行
	{
		WinAnimation(false);		 //窗体动画从系统区滑出 
		pFrame->ShowWindow(SW_SHOW);
	}
    else							 //是否进行窗体动画,窗体已隐藏则不进行
	{
		m_Tip.SetHideDelay(100);     //隐藏提示窗
		m_Tip.Hide();
        pFrame->ShowWindow(SW_HIDE);
	    WinAnimation(true);			 //窗体动画滑入到系统区中 
	}	
}

//********************************************************************************
//* 名称：OnInitMenuPopup()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：加此涵数，使动态新增菜单条同步以XP风格显示
//********************************************************************************
void CTransparentWnd::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	CWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	
	if(!bSysMenu){
		if(BCMenu::IsMenu(pPopupMenu)) BCMenu::UpdateMenu(pPopupMenu);
	}
}

//********************************************************************************
//* 名称：OnMeasureItem()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：重新测量菜单条
//********************************************************************************
void CTransparentWnd::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	BOOL setflag=FALSE;
	if(lpMeasureItemStruct->CtlType==ODT_MENU){
		if(IsMenu((HMENU)lpMeasureItemStruct->itemID)&&BCMenu::IsMenu((HMENU)lpMeasureItemStruct->itemID)){
			m_popmenu.MeasureItem(lpMeasureItemStruct);
			setflag=TRUE;
		}
	}
	if(!setflag)CWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);	
}

//********************************************************************************
//* 名称：OnMenuChar()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：重新绘制菜单条
//********************************************************************************
LRESULT CTransparentWnd::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
	LRESULT lresult;
	if(BCMenu::IsMenu(pMenu))
		lresult=BCMenu::FindKeyboardShortcut(nChar, nFlags, pMenu);
	else
		lresult=CWnd::OnMenuChar(nChar, nFlags, pMenu);

	return(lresult);
	
}

//********************************************************************************
//* 名称：GetFullScreenWalk()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：获取是否全屏运动的标志位
//********************************************************************************
BOOL CTransparentWnd::GetFullScreenWalk()                
{
	return m_bFullScreenWalk;
}  

//********************************************************************************
//* 名称：GetOptionMute()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：获取静音标志位
//********************************************************************************
BOOL CTransparentWnd::GetOptionMute()                  
{
	return m_bMute;   
}
  
//********************************************************************************
//* 名称：GetOptionTopShow()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：获取顶层显示标志位
//********************************************************************************
BOOL CTransparentWnd::GetOptionTopShow()               
{
	return m_bTopShow;
}

//********************************************************************************
//* 名称：GetOptionRest()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：获取静止标志位
//********************************************************************************
BOOL CTransparentWnd::GetOptionRest()                 
{
	return m_bRest; 
}

//********************************************************************************
//* 名称：OnDownload()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：设置下载网页地址
//********************************************************************************
void CTransparentWnd::OnDownload() 
{
	CDownloadAddress dlg;  
	CString str;

	//保证此对话框一次只弹出一个
	if(!FindWindow(NULL,"设置下载网址"))
	{
		if(dlg.DoModal()==IDOK)
		{
			if((str=dlg.GetDownloadAddress())!="")
			{
				CWnd * pFrame;					        

				pFrame=AfxGetApp()->GetMainWnd();
				pFrame->ShowWindow(SW_HIDE);            //下载前先隐藏精灵助手
				if(m_bSuccess)
				{
					m_sdFile.Close();                   //先关闭原打开文件，以便新建文件
					m_bSuccess=FALSE;
				}
				m_bDownloadFailed= FALSE;               //选置假，避免显示提示窗信息
														
				//下载新设置的网页
				m_bDownloadFailed=GetSourceHtml(str,"News.txt");	

				if(m_bDownloadFailed)
					m_bSuccess=m_bDownloadFailed=m_sdFile.Open(strPath+"\\Nesw.txt",
					CFile::modeRead | CFile::typeText);
			}
		}
	}
}

//********************************************************************************
//* 名称：OnActionRun()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：奔跑方式
//********************************************************************************
void CTransparentWnd::OnActionRun() 
{
	int CurAction;
	if((CurAction=GetCurAction())!=TIMER_TRANSFORM)
		KillTimer(CurAction);

	m_Tip.SetHideDelay(100);     //隐藏提示窗
	m_Tip.Hide();

	SetTimer(TIMER_TRANSFORM,500,NULL);  //改奔跑为变形方式
//	SetTimer(TIMER_RUN,500,NULL);	
}

//********************************************************************************
//* 名称：OnActionWalk()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：散步方式
//********************************************************************************
void CTransparentWnd::OnActionWalk() 
{
	int CurAction;
	if((CurAction=GetCurAction())!=TIMER_WALK)
		KillTimer(CurAction);

	m_Tip.SetHideDelay(100); 
	m_Tip.Hide();

	SetTimer(TIMER_WALK,150,NULL);
}

//********************************************************************************
//* 名称：OnActionIdle()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：休息方式
//********************************************************************************
void CTransparentWnd::OnActionIdle() 
{		
	int CurAction;
	if((CurAction=GetCurAction())!=TIMER_IDLE)
		KillTimer(CurAction);

	SetTimer(TIMER_IDLE,300,NULL);
}

//********************************************************************************
//* 名称：GetCurAction()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：获取当前行为表现方式
//********************************************************************************
int  CTransparentWnd::GetCurAction()
{
	return m_iAction;
}

//********************************************************************************
//* 名称：GetTopWndTitleRect()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：获取当前桌面最顶层窗口标题区大小
//********************************************************************************
CRect CTransparentWnd::GetTopWndTitleRect()             
{
/*
	HWND TopHwnd;
	CHelpTipDlg ExitDlg;
	CDownloadAddress AddressDlg; 
	CAbout aboutDlg;
	CSetRing RingDlg;

	TopHwnd=::GetForegroundWindow();

	//不能是本程序所具有的窗体，否则返回初窗口标题区大小
	if(TopHwnd==this->m_hWnd||TopHwnd==ExitDlg.m_hWnd||TopHwnd==AddressDlg.m_hWnd||TopHwnd==aboutDlg.m_hWnd||TopHwnd==RingDlg)
		return m_Rect;

	CRect rtWnd;
	::GetWindowRect(TopHwnd,&rtWnd);

	return rtWnd;
*/

	// 查找并返回任务栏窗口大小 
	CRect rect(0,0,0,0);
    CWnd* pWnd = FindWindow("Shell_TrayWnd", NULL);
    if (pWnd)
    {
        pWnd->GetWindowRect(&rect);
	}
	return rect;
}

//********************************************************************************
//* 名称：OnAbout()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：关于对话框
//********************************************************************************
void CTransparentWnd::OnAbout() 
{
	CAbout aboutDlg;

	//保证此对话框一次只弹出一个
	if(!FindWindow(NULL,"关于"))
		aboutDlg.DoModal(); 
}

//********************************************************************************
//* 名称：OnActionSpecial()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：闹铃设置对话框
//********************************************************************************
void CTransparentWnd::OnActionSpecial() 
{
	CSetRing RingDlg;

	//保证此对话框一次只弹出一个
	HWND hWnd = ::FindWindow(NULL,"设置闹钟功能");
	if(!hWnd)
	{
		if(RingDlg.DoModal()==IDOK)
		{
			m_Time=RingDlg.GetCurRingTime();
			if(m_Time!=NULL)
				SetTimer(TIMER_SETRING,1000,NULL);	 //一秒钟更新一次
		}
	}
}

//********************************************************************************
//* 名称：OnActionSpecial()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：闹铃设置对话框
//********************************************************************************
void CTransparentWnd::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CRect rcWnd;
	GetWindowRect(&rcWnd);
	CPoint pt;
	GetCursorPos(&pt);

	if(rcWnd.PtInRect(pt))
		OnActionSpecial();	

	CWnd::OnLButtonDblClk(nFlags, point);
}

//********************************************************************************
//* 名称：StartupAutorun()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：开机时程序自动运行
//********************************************************************************
BOOL CTransparentWnd::StartupAutorun(BOOL bIsAdd)
{
	HKEY hKey;
	LONG lRet, lRet2;
	DWORD dwLength, dwDataType;
	TCHAR szItemValue[MAX_PATH], szPrevValue[MAX_PATH];
	TCHAR szBuffer[MAX_PATH];

	// 得到程序全路径名
	GetModuleFileName( NULL, szItemValue, MAX_PATH );


	// 打开注册表键
		lRet = RegOpenKeyEx( HKEY_LOCAL_MACHINE, gcszAutoRunKey,
			0, KEY_READ | KEY_WRITE, &hKey );
		if( lRet != ERROR_SUCCESS )
			return FALSE;

	// 查询自动运行项目是否存在
		dwLength = sizeof( szBuffer );
		lRet = RegQueryValueEx( hKey, gcszWindowClass, 
			NULL, &dwDataType, (LPBYTE)szBuffer, &dwLength );

	// 添加
		if( bIsAdd == TRUE ) 
		{
	// 自动运行项目不存在
			if( lRet != ERROR_SUCCESS )
				lRet2 = RegSetValueEx( hKey, gcszWindowClass,
				0, REG_SZ, (LPBYTE)szItemValue, strlen( szItemValue ) );
			else 
			{
	// 存在, 比较二者是否相同
				dwLength = sizeof( szPrevValue );
				lRet2 = RegQueryValueEx( hKey, gcszWindowClass, 
					0, &dwDataType,(LPBYTE)szPrevValue, &dwLength );
	// 不相同则替换
				if( lstrcmp( szItemValue, szPrevValue ) ) 
				{
					lRet2 = RegDeleteValue( hKey, gcszWindowClass );
					lRet2 = RegSetValueEx( hKey, gcszWindowClass, 
						0, REG_SZ,(LPBYTE)szItemValue, strlen( szItemValue ) );
				}
			}
		}
	// 删除
		else 
	// 自动运行项目已存在则删除
			if( lRet == ERROR_SUCCESS )
				lRet2 = RegDeleteValue( hKey, gcszWindowClass );

	// 关闭注册表键
		RegCloseKey( hKey );

		if( lRet2 != ERROR_SUCCESS )
			return FALSE;


	return TRUE;
}

//********************************************************************************
//* 名称：OnAutorun()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：开机时程序自动运行
//********************************************************************************
void CTransparentWnd::OnAutorun() 
{
	m_bAutorun = !m_bAutorun;
	
}

//********************************************************************************
//* 名称：GetAutorunFlag()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：获取自动运行标志
//********************************************************************************
BOOL CTransparentWnd::GetAutorunFlag()		
{
	return m_bAutorun;
}

//********************************************************************************
//* 名称：GetShowNews()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：获取显示新闻标志
//********************************************************************************
BOOL CTransparentWnd::GetShowNewsFlag()   
{
	return m_bShowNews;
}

//********************************************************************************
//* 名称：OnShownews()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：是否显示新闻
//********************************************************************************
void CTransparentWnd::OnShownews() 
{
	m_bShowNews = !m_bShowNews;
	
}

