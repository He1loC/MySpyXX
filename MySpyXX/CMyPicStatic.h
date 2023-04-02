#pragma once


// CMyPicStatic

class CMyPicStatic : public CStatic
{
	DECLARE_DYNAMIC(CMyPicStatic)

public:
	CMyPicStatic();
	virtual ~CMyPicStatic();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	HDC DrawWndSPy(HWND hWnd);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void SetFindWindowInfo(CWnd* pWnd);
protected:
	bool m_bIsDetecting=false;
	CWnd* m_pWndLast=nullptr;
};


