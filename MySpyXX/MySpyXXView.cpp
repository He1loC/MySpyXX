
// MySpyXXView.cpp : implementation of the CMySpyXXView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MySpyXX.h"
#endif

#include "MySpyXXDoc.h"
#include "MySpyXXView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMySpyXXView

IMPLEMENT_DYNCREATE(CMySpyXXView, CView)

BEGIN_MESSAGE_MAP(CMySpyXXView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMySpyXXView construction/destruction

CMySpyXXView::CMySpyXXView() noexcept
{
	// TODO: add construction code here

}

CMySpyXXView::~CMySpyXXView()
{
}

BOOL CMySpyXXView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMySpyXXView drawing

void CMySpyXXView::OnDraw(CDC* /*pDC*/)
{
	CMySpyXXDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMySpyXXView printing

BOOL CMySpyXXView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMySpyXXView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMySpyXXView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMySpyXXView diagnostics

#ifdef _DEBUG
void CMySpyXXView::AssertValid() const
{
	CView::AssertValid();
}

void CMySpyXXView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMySpyXXDoc* CMySpyXXView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMySpyXXDoc)));
	return (CMySpyXXDoc*)m_pDocument;
}
#endif //_DEBUG


// CMySpyXXView message handlers
