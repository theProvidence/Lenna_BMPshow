
// Lenna_BMPshowView.h : interface of the CLennaBMPshowView class
//

#pragma once


class CLennaBMPshowView : public CView
{
protected: // create from serialization only
	CLennaBMPshowView() noexcept;
	DECLARE_DYNCREATE(CLennaBMPshowView)

// Attributes
public:
	CLennaBMPshowDoc* GetDocument() const;

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
	virtual ~CLennaBMPshowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in Lenna_BMPshowView.cpp
inline CLennaBMPshowDoc* CLennaBMPshowView::GetDocument() const
   { return reinterpret_cast<CLennaBMPshowDoc*>(m_pDocument); }
#endif

