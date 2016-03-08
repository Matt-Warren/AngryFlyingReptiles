
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "Reptile.h"

// CChildView window
using namespace Gdiplus;
class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:
	void ResetGame();
// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();


	// Generated message map functions
protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	BOOL OnEraseBkgnd(CDC * pDC);
	DECLARE_MESSAGE_MAP()
public:
	int reptX;
	int reptY;
	bool status;

	ULONG_PTR gdiplusToken;

	Bitmap* backBmp;
	Bitmap* displayBackBmp;
	Bitmap* midBmp;
	Bitmap* displayMidBmp;
	Bitmap* foreBmp;
	Bitmap* displayForeBmp;

	Bitmap* sling1;
	Bitmap* displaySling1;
	Bitmap* sling2;
	Bitmap* displaySling2;
	Bitmap* rept;
	Bitmap* displayRept;
	
	

	Color chromaOut;
	RECT screenRect;
	
	bool yDirection;

};

