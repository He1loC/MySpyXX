
// MySpyXXView.h : interface of the CMySpyXXView class
//

#pragma once


class CMySpyXXView : public CView
{
protected: // create from serialization only
	CMySpyXXView() noexcept;
	DECLARE_DYNCREATE(CMySpyXXView)

// Attributes
public:
	CMySpyXXDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMySpyXXView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MySpyXXView.cpp
inline CMySpyXXDoc* CMySpyXXView::GetDocument() const
   { return reinterpret_cast<CMySpyXXDoc*>(m_pDocument); }
#endif

