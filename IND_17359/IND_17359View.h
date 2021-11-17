
// IND_17359View.h : interface of the CIND17359View class
//

#pragma once


class CIND17359View : public CView
{
protected: // create from serialization only
	CIND17359View() noexcept;
	DECLARE_DYNCREATE(CIND17359View)

// Attributes
public:
	CIND17359Doc* GetDocument() const;

private:
	bool showGrid;
	CRect hostRectangle;
	int innerRectangleSize;
	int hostRectangleSize;

	int firstCactusPartDeg;
	int secondCactusPartDeg;
// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	void DrawBackground(CDC* pDC);
	void DrawGrid(CDC* pDC);
	void DrawStudentInfo(CDC* pDC);
	void DrawFlowerPot(CDC* pDC);
	void DrawStaticPartsOfCactus(CDC* pDC);
	void DrawFirstMovingPartOfCactus(CDC* pDC);
	void DrawSecondMovingCactusPart(CDC* pDC);
	void Scale(CDC* pDC, float sX, float sY, bool rightMultiply);
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void NoTranform(CDC* pDC);
	void SetWorldTransformTranslate(CDC* pDC, float eDx, float eDy);
	void ModifyWorldTransformRotate(CDC* pDC, double radians, DWORD modifyMode);
	void ModifyWorldTransformTranslate(CDC* pDC, float eDx, float eDy, DWORD modifyMode);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CIND17359View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg
		int mod(int k, int n);
	void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in IND_17359View.cpp
inline CIND17359Doc* CIND17359View::GetDocument() const
   { return reinterpret_cast<CIND17359Doc*>(m_pDocument); }
#endif

