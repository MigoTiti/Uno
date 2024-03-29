
// UnoClienteView.cpp : implementation of the CUnoClienteView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "UnoCliente.h"
#endif

#include "UnoClienteDoc.h"
#include "UnoClienteView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUnoClienteView

IMPLEMENT_DYNCREATE(CUnoClienteView, CView)

BEGIN_MESSAGE_MAP(CUnoClienteView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CUnoClienteView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CUnoClienteView construction/destruction

CUnoClienteView::CUnoClienteView()
{
	// TODO: add construction code here

}

CUnoClienteView::~CUnoClienteView()
{
}

BOOL CUnoClienteView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CUnoClienteView drawing

void CUnoClienteView::OnDraw(CDC* /*pDC*/)
{
	CUnoClienteDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CUnoClienteView printing


void CUnoClienteView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CUnoClienteView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CUnoClienteView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CUnoClienteView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CUnoClienteView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CUnoClienteView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CUnoClienteView diagnostics

#ifdef _DEBUG
void CUnoClienteView::AssertValid() const
{
	CView::AssertValid();
}

void CUnoClienteView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUnoClienteDoc* CUnoClienteView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUnoClienteDoc)));
	return (CUnoClienteDoc*)m_pDocument;
}
#endif //_DEBUG


// CUnoClienteView message handlers
