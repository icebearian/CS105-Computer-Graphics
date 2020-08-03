
// LineDemoView.h : interface of the CLineDemoView class
//

#pragma once


class CLineDemoView : public CView
{
protected: // create from serialization only
	CLineDemoView() noexcept;
	DECLARE_DYNCREATE(CLineDemoView)

// Attributes
public:
	CLineDemoDoc* GetDocument() const;
	CPoint startPoint;
	CPoint endPoint;
	int A;
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
	virtual ~CLineDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnThuatDda();
	afx_msg void OnThuatBressenham();
	afx_msg void OnThuatMidpoint32777();
	afx_msg void OnThuatMidpoint();
};

#ifndef _DEBUG  // debug version in LineDemoView.cpp
inline CLineDemoDoc* CLineDemoView::GetDocument() const
   { return reinterpret_cast<CLineDemoDoc*>(m_pDocument); }
#endif

