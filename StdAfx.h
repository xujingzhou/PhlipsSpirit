// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__89E7552B_714A_406B_A1D7_CE561729B811__INCLUDED_)
#define AFX_STDAFX_H__89E7552B_714A_406B_A1D7_CE561729B811__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <SDKDDKVer.h>

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxtempl.h>       //������ʾ����Ҫ�õ�ͷ�ļ�
#include "afxinet.h"        //����������ҳҪ�õ�ͷ�ļ�
#include <MMSystem.h>       //���벥�������ļ�֧�ֵ�ͷ�ļ�

// CG: The following line was added by the Windows Multimedia component.
#pragma comment(lib, "winmm.lib")

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__89E7552B_714A_406B_A1D7_CE561729B811__INCLUDED_)
