// Advertise.cpp : implementation file
//////////////////////////////////////////////////
//类名：CAdvertise
//功能：广告对话框实现
//作者：徐景周(Johnny Xu, xujingzhou2016@gmail.com)
//组织：未来工作室(Future Studio)
//日期：2001.12.1
//////////////////////////////////////////////////
#include "stdafx.h"
#include "helptip.h"
#include "Advertise.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Advertise dialog


CAdvertise::CAdvertise(CWnd* pParent /*=NULL*/)
	: CDialog(CAdvertise::IDD, pParent)
{
	//{{AFX_DATA_INIT(Advertise)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAdvertise::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Advertise)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdvertise, CDialog)
	//{{AFX_MSG_MAP(Advertise)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Advertise message handlers
// ---------------------------------------------------------
//	名称: OnInitDialog
//	功能: 初始化广告对话框
//	变量: 无
//	返回: TRUE --成功，FALSE -- 失败
//	编写: 徐景周，2002.4.8
// ---------------------------------------------------------
BOOL CAdvertise::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//初始置窗体大小为背景位图大小
	CRect	windowRect,m_Rect,DeskTopWnd;
	windowRect.SetRect(0,
		0,
		BACKWIDTH ,
		BACKHEIGHT );

	//计算广告窗体到系统区位置
	m_Rect=GetTrayWndRect();						//注：暂只限任务条在屏幕下方时
	::GetWindowRect(::GetDesktopWindow(),&DeskTopWnd);
	windowRect.top =DeskTopWnd.bottom -m_Rect.Height()-windowRect.Height();
	windowRect.bottom =DeskTopWnd.bottom-m_Rect.Height();

	windowRect.right =m_Rect.right;
	windowRect.left = windowRect.right - BACKWIDTH;

	//置窗体为显示及其位置
	MoveWindow(windowRect,FALSE);

	//装入手形光标
	m_Cursor = ::LoadCursor(AfxGetResourceHandle(),MAKEINTRESOURCE(IDC_HAND));

	//将广告位图透明化
	m_bmpDraw.LoadBitmap(IDB_ADVERTISE);
	CWindowDC dc(this);
	TransparentRegion(&dc);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//********************************************************************************
//* 名称：TransparentRegion()
//* 作者：徐景周(jingzhou_xu@163.net)
//* 功能：将窗体背景透明化(新的透明算法)
//********************************************************************************
void CAdvertise::TransparentRegion(CDC *pDC)
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

// ---------------------------------------------------------
//	名称: GetTrayWndRect
//	功能: 获取系统区范围大小
//	变量: 无
//	返回: CRect -- 系统区大小
//	编写: 徐景周，2002.4.8
// ---------------------------------------------------------
CRect CAdvertise::GetTrayWndRect()             
{
	// 查找并返回任务栏窗口大小 
	CRect rect(0,0,0,0);
    CWnd* pWnd = FindWindow("Shell_TrayWnd", NULL);
    if (pWnd)
    {
        pWnd->GetWindowRect(&rect);
	}
	return rect;
}

// ---------------------------------------------------------
//	名称: OnEraseBkgnd
//	功能: 刷新窗体背景位图
//	变量: 无
//	返回: TRUE --成功，FALSE -- 失败
//	编写: 徐景周，2002.4.8
// ---------------------------------------------------------
BOOL CAdvertise::OnEraseBkgnd(CDC* pDC) 
{
	CDC     memDC;
	CBitmap cBitmap;
	cBitmap.LoadBitmap(IDB_ADVERTISE);
	memDC.CreateCompatibleDC (pDC);
	CBitmap *oldBitmap=memDC.SelectObject(&cBitmap);
	pDC->BitBlt (0,0,BACKWIDTH,BACKHEIGHT,&memDC,0,0,SRCCOPY);
	memDC.SelectObject(oldBitmap);

	return TRUE;
}

// ---------------------------------------------------------
//	名称: OnLButtonDown
//	功能: 左键按下时，打开相应网页
//	变量: 无
//	返回: 无
//	编写: 徐景周，2002.4.8
// ---------------------------------------------------------
void CAdvertise::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect rcWnd;
	GetWindowRect(&rcWnd);
	CPoint pt;
	GetCursorPos(&pt);

	CString url = _T("http://www.philips120dreams.com");
	if(rcWnd.PtInRect(pt))
	{
		HINSTANCE result=ShellExecute(NULL, _T("open"), url, NULL,NULL, SW_SHOW);
	}
}

// ---------------------------------------------------------
//	名称: OnMouseMove
//	功能: 鼠标在窗体上移动时，显示手形光标
//	变量: 无
//	返回: 无
//	编写: 徐景周，2002.4.8
// ---------------------------------------------------------
void CAdvertise::OnMouseMove(UINT nFlags, CPoint point) 
{
	CRect rcWnd;
	GetWindowRect(&rcWnd);
	CPoint pt;
	GetCursorPos(&pt);
	
	if(rcWnd.PtInRect(pt))
	{
		if(m_Cursor)
			SetCursor(m_Cursor);
	}

}
