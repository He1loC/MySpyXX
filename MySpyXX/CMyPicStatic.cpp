// CMyPicStatic.cpp : implementation file
//

#include "pch.h"
#include "MySpyXX.h"
#include "CMyPicStatic.h"
#include "CFindWindowDlg.h"


// CMyPicStatic

IMPLEMENT_DYNAMIC(CMyPicStatic, CStatic)

CMyPicStatic::CMyPicStatic()
{

}

CMyPicStatic::~CMyPicStatic()
{
    DrawWndSPy(m_pWndLast->GetSafeHwnd());  //关闭时还原
}


BEGIN_MESSAGE_MAP(CMyPicStatic, CStatic)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CMyPicStatic message handlers




void CMyPicStatic::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_NOCROSS));
	::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR_MYCROSS));
	SetCapture();
	m_bIsDetecting = true;

	CStatic::OnLButtonDown(nFlags, point);
}

//绘制窗口
HDC CMyPicStatic::DrawWndSPy(HWND hWnd)
{
    HWND v1; // ebx
    HDC result; // eax
    HDC v3; // edi
    HGDIOBJ v4; // eax
    int v5; // esi
    COLORREF v6; // eax
    HBRUSH v7; // esi
    HPEN ho; // [esp+Ch] [ebp-30h]
    HGDIOBJ v9; // [esp+10h] [ebp-2Ch]
    HGDIOBJ h; // [esp+14h] [ebp-28h]
    int v11; // [esp+18h] [ebp-24h]
    int v12; // [esp+18h] [ebp-24h]
    int w; // [esp+1Ch] [ebp-20h]
    int v14; // [esp+20h] [ebp-1Ch]
    int v15; // [esp+20h] [ebp-1Ch]
    HRGN hRgn; // [esp+24h] [ebp-18h]
    struct tagRECT Rect; // [esp+28h] [ebp-14h]

    v1 = hWnd;
    v14 = ::GetSystemMetrics(5);
    v11 = ::GetSystemMetrics(6);
    result = ::GetWindowDC(v1);
    v3 = result;
    if (result)
    {
        hRgn = ::CreateRectRgn(0, 0, 0, 0);
        ho = ::CreatePen(6, 3 * v14, 0);
        v9 = ::SelectObject(v3, ho);
        v4 = ::GetStockObject(5);
        h = ::SelectObject(v3, v4);
        ::SetROP2(v3, 6);
        if (::GetWindowRgn(v1, hRgn))
        {
            v6 = ::GetSysColor(6);
            v7 = ::CreateHatchBrush(5, v6);
            ::FrameRgn(v3, hRgn, v7, 3 * v14, 3 * v11);
            ::DeleteObject(v7);
        }
        else
        {
            w = ::GetSystemMetrics(32);
            v15 = ::GetSystemMetrics(33);
            v12 = ::GetSystemMetrics(0);
            v5 = ::GetSystemMetrics(1);
            ::GetWindowRect(v1, &Rect);
            if (::IsZoomed(v1))
                ::Rectangle(v3, w, v15, w + v12, v5 + v15);
            else
                ::Rectangle(v3, 0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top);
        }
        ::SelectObject(v3, h);
        ::SelectObject(v3, v9);
        ::DeleteObject(ho);
        ::DeleteObject(hRgn);
        result = (HDC)::ReleaseDC(v1, v3);
    }
    return result;
}



void CMyPicStatic::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	// 当前是否在探测窗口
	if (!m_bIsDetecting)
	{
		CStatic::OnMouseMove(nFlags, point);
		return;
	}
	// 绘制矩形
	// 获取当前窗口
	ClientToScreen(&point);
	CWnd* pWndCur = WindowFromPoint(point);

	if (pWndCur!=m_pWndLast)
	{
        // 第一次画
        if (m_pWndLast == nullptr)
        {
            DrawWndSPy(pWndCur->GetSafeHwnd());
        }
        else
        {
            DrawWndSPy(m_pWndLast->GetSafeHwnd());
            DrawWndSPy(pWndCur->GetSafeHwnd());
        }
        m_pWndLast = pWndCur;
        SetFindWindowInfo(pWndCur);
	}



	CStatic::OnMouseMove(nFlags, point);
}


void CMyPicStatic::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bIsDetecting = false;
	SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_CROSSED));
	ReleaseCapture();

	CStatic::OnLButtonUp(nFlags, point);
}


void CMyPicStatic::SetFindWindowInfo(CWnd* pWnd)
{
    auto pParentWnd = (CFindWindowDlg *)GetParent();

    pParentWnd->m_strHandle.Format(_T("%p"),(unsigned int) pWnd->GetSafeHwnd());


    pParentWnd->UpdateData(FALSE);
    pParentWnd->OnEnChangeEditFindwndHandle();
}
