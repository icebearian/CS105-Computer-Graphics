
// LineDemoView.cpp : implementation of the CLineDemoView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "LineDemo.h"
#endif

#include "LineDemoDoc.h"
#include "LineDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CLine.h"

// CLineDemoView

IMPLEMENT_DYNCREATE(CLineDemoView, CView)

BEGIN_MESSAGE_MAP(CLineDemoView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CLineDemoView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_THUAT_DDA, &CLineDemoView::OnThuatDda)
	ON_COMMAND(ID_THUAT_BRESSENHAM, &CLineDemoView::OnThuatBressenham)
	ON_COMMAND(ID_THUAT_MIDPOINT32777, &CLineDemoView::OnThuatMidpoint)
END_MESSAGE_MAP()

// CLineDemoView construction/destruction

CLineDemoView::CLineDemoView() noexcept
{
	// TODO: add construction code here

}

CLineDemoView::~CLineDemoView()
{
}

BOOL CLineDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLineDemoView drawing

void CLineDemoView::OnDraw(CDC* pDC)
{
	CLineDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	int R = sqrt((endPoint.x - startPoint.x) * (endPoint.x - startPoint.x) + (endPoint.y - startPoint.y) * (endPoint.y - startPoint.y));
	switch (A)
	{
	case 1: 
		CLine::LineDDA(pDC, startPoint, endPoint, RGB(255, 0, 0));
		break;
	case 2: 
		CLine::LineBressenham(pDC, startPoint, endPoint, RGB(0, 0, 255));
		break;
	case 3:
		CLine::Midpoint(pDC, startPoint.x, startPoint.y, R, RGB(0, 255, 0));
		break;
	default:
		CLine::LineDDA(pDC, startPoint, endPoint, RGB(255, 0, 0));
		break;
	}
	

}


// CLineDemoView printing


void CLineDemoView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CLineDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLineDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLineDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CLineDemoView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLineDemoView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CLineDemoView diagnostics

#ifdef _DEBUG
void CLineDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CLineDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLineDemoDoc* CLineDemoView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLineDemoDoc)));
	return (CLineDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CLineDemoView message handlers



void CLineDemoView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	startPoint = point;
	endPoint = point;
	CView::OnLButtonDown(nFlags, point);
}


void CLineDemoView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	endPoint = point;
	CView::OnLButtonUp(nFlags, point);
}


void CLineDemoView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (nFlags && MK_LBUTTON)
	{
		endPoint = point;
		Invalidate();
	}
	CView::OnMouseMove(nFlags, point);
}


void CLineDemoView::OnThuatDda()
{
	// TODO: Add your command handler code here
	A = 1;
}


void CLineDemoView::OnThuatBressenham()
{
	// TODO: Add your command handler code here
	A = 2;
}



void CLineDemoView::OnThuatMidpoint()
{
	// TODO: Add your command handler code here
	A = 3;
}
