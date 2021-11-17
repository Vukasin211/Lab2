
// IND_17359View.cpp : implementation of the CIND17359View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "IND_17359.h"
#endif

#include "IND_17359Doc.h"
#include "IND_17359View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif // !_USE_MATH_DEFINES
#include <math.h>

// CIND17359View

IMPLEMENT_DYNCREATE(CIND17359View, CView)

BEGIN_MESSAGE_MAP(CIND17359View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// CIND17359View construction/destruction

CIND17359View::CIND17359View() noexcept
{
	// TODO: add construction code here
	hostRectangleSize = 500;
	innerRectangleSize = 500 / 20;

	showGrid = false;
	hostRectangle = CRect(0, 0, hostRectangleSize, hostRectangleSize);

	firstCactusPartDeg = 45;
	secondCactusPartDeg = 45;
}

CIND17359View::~CIND17359View()
{
}

BOOL CIND17359View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CIND17359View drawing

void CIND17359View::OnDraw(CDC* pDC)
{
	CIND17359Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	this->DrawBackground(pDC);

	
	this->DrawStaticPartsOfCactus(pDC);
	this->DrawFlowerPot(pDC);
	this->DrawFirstMovingPartOfCactus(pDC);
	this->DrawStudentInfo(pDC);
	if(showGrid)
	this->DrawGrid(pDC);
}

void CIND17359View::DrawBackground(CDC* pDC)
{
	CBrush blueBrush(RGB(135, 206, 235));
	CBrush* oldBrush = pDC->SelectObject(&blueBrush);
	CGdiObject* oldPen = pDC->SelectStockObject(NULL_PEN);

	pDC->Rectangle(hostRectangle);

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	blueBrush.DeleteObject();
}

void CIND17359View::DrawGrid(CDC* pDC)
{
		CPen whitePen(PS_SOLID, 2, RGB(255, 255, 255));
		POINT verticalGridLinePoints[40];
		POINT horizontalGridLinePoints[40];
		DWORD pointCount[40];

		for (int i = 0; i < 40; i++)
		{
			pointCount[i] = 2;
		}

		for (int i = 0; i < 40 - 1; i += 2)
		{
			verticalGridLinePoints[i] = { hostRectangle.left + i / 2 * innerRectangleSize, hostRectangle.top };
			verticalGridLinePoints[i + 1] = { hostRectangle.left + i / 2 * innerRectangleSize, hostRectangle.bottom };
			horizontalGridLinePoints[i] = { hostRectangle.left, hostRectangle.top + i / 2 * innerRectangleSize };
			horizontalGridLinePoints[i + 1] = { hostRectangle.right ,hostRectangle.top + i / 2 * innerRectangleSize };
		}

		POINT allPoints[80];
		for (int i = 0; i < 40; i++)
		{
			allPoints[i] = verticalGridLinePoints[i];
			allPoints[40 + i] = horizontalGridLinePoints[i];
		}

		CPen* oldPen = pDC->SelectObject(&whitePen);
		pDC->PolyPolyline(allPoints, pointCount, 40);

		pDC->SelectObject(oldPen);
		whitePen.DeleteObject();
}

void CIND17359View::DrawStudentInfo(CDC* pDC)
{
	//COLORREF clrOld = pDC->SetTextColor(RGB(255, 255, 0));
	int nOldMode = pDC->SetBkMode(TRANSPARENT);
	char* signature = "17359 Vukasin Popovic";
	CString str(signature);
	CFont font;;
	font.CreateFont(innerRectangleSize, 13, -900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (CString)"Times New Roman");
	CFont* oldFont = pDC->SelectObject(&font);
	pDC->SetTextAlign(TA_TOP);
	pDC->TextOut(hostRectangle.right - innerRectangleSize, innerRectangleSize, str);
	COLORREF clrOld = pDC->SetTextColor(RGB(255, 255, 0));
	pDC->TextOut(hostRectangle.right - innerRectangleSize - 2, innerRectangleSize + 2, str);
	pDC->SetBkMode(nOldMode);
	pDC->SetTextColor(clrOld);
}

void CIND17359View::DrawFlowerPot(CDC* pDC)
{
	POINT A = { hostRectangle.left + innerRectangleSize * 8, hostRectangle.bottom - innerRectangleSize * 2.5 };
	POINT B = { hostRectangle.left + innerRectangleSize * 12, hostRectangle.bottom - innerRectangleSize * 2.5 };
	POINT C = { hostRectangle.left + innerRectangleSize * 11 + innerRectangleSize / 2, hostRectangle.bottom };
	POINT D = { hostRectangle.left + innerRectangleSize * 8 + innerRectangleSize / 2, hostRectangle.bottom };

	CPoint trapezPartOfThePot[4] = { A, B, C, D };

	CRect rectanglePartOfPot(hostRectangle.left + 7.6 * innerRectangleSize,
		hostRectangle.bottom - 2.8 * innerRectangleSize,
		hostRectangle.right - 7.6 * innerRectangleSize,
		hostRectangle.bottom - 2 * innerRectangleSize);

	CPen blackPen(PS_SOLID, 1, RGB(0, 0, 0));
	CBrush orangeBrush(RGB(222, 148, 0));
	CBrush* oldBrush = pDC->SelectObject(&orangeBrush);
	CPen* oldPen = pDC->SelectObject(&blackPen);

	pDC->Polygon(trapezPartOfThePot, 4);
	pDC->Rectangle(rectanglePartOfPot);

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);

	blackPen.DeleteObject();
	orangeBrush.DeleteObject();
}

void CIND17359View::DrawStaticPartsOfCactus(CDC* pDC)
{
	int prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	XFORM xformOld;
	GetWorldTransform(pDC->m_hDC, &xformOld);

	CRect bottomCircle(int(hostRectangle.left + 9.6 * innerRectangleSize),
		int(hostRectangle.bottom - 3.4 * innerRectangleSize),
		int(hostRectangle.left + 10.4 * innerRectangleSize),
		int(hostRectangle.bottom - 2.6 * innerRectangleSize));

	HENHMETAFILE cactusStandardPart = GetEnhMetaFile(CString("res/cactus_part.emf"));

	CRect middleCactusPart(hostRectangle.left + 8.8 * innerRectangleSize,
		hostRectangle.bottom - 6 * innerRectangleSize,
		hostRectangle.right - 8.8 * innerRectangleSize,
		hostRectangle.bottom - 3 * innerRectangleSize);

	PlayEnhMetaFile(pDC->m_hDC, cactusStandardPart, middleCactusPart); //crtanje dela koji je vezan za source.emf

	CRect middleCircle(bottomCircle.left,
		int(hostRectangle.bottom - 6.4 * innerRectangleSize),
		bottomCircle.right,
		int(hostRectangle.bottom - 5.6 * innerRectangleSize));

	CRect middleThinCactusPart(
		hostRectangle.left + 9.5 * innerRectangleSize,
		hostRectangle.bottom - 9 * innerRectangleSize,
		hostRectangle.right - 9.5 * innerRectangleSize,
		hostRectangle.bottom - 6 * innerRectangleSize
	);

	CRect leftThinCactusPart(
		hostRectangle.left + 9.5 * innerRectangleSize,
		hostRectangle.bottom - 9 * innerRectangleSize,
		hostRectangle.right - 9.5 * innerRectangleSize,
		hostRectangle.bottom - 6 * innerRectangleSize
	);

	CBrush darkGreenBrush(RGB(0, 204, 0));
	CBrush* oldBrush = pDC->SelectObject(&darkGreenBrush);

	this->Translate(pDC, leftThinCactusPart.CenterPoint().x, leftThinCactusPart.bottom, false);
	this->Rotate(pDC, - (M_PI / 4), false);
	this->Translate(pDC, -leftThinCactusPart.CenterPoint().x, -leftThinCactusPart.bottom, false);
	
	PlayEnhMetaFile(pDC->m_hDC, cactusStandardPart, middleThinCactusPart);

	this->NoTranform(pDC);

	PlayEnhMetaFile(pDC->m_hDC, cactusStandardPart, middleThinCactusPart);
	pDC->Ellipse(bottomCircle);
	pDC->Ellipse(middleCircle);

	pDC->SelectObject(oldBrush);
	darkGreenBrush.DeleteObject();
	SetGraphicsMode(pDC->m_hDC, prevMode);
	DeleteEnhMetaFile(cactusStandardPart);
}

void CIND17359View::DrawFirstMovingPartOfCactus(CDC* pDC){

	CBrush darkGreenBrush(RGB(0, 204, 0));
	CBrush* oldBrush = pDC->SelectObject(&darkGreenBrush);

	HENHMETAFILE cactusStandardPart = GetEnhMetaFile(CString("res/cactus_part.emf"));
	HENHMETAFILE rotatingCactusPart = GetEnhMetaFile(CString("res/cactus_part_light.emf"));
	int prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	XFORM xformOld;
	GetWorldTransform(pDC->m_hDC, &xformOld);

	CRect rightThinCactusPart(
		hostRectangle.left + 9.5 * innerRectangleSize,
		hostRectangle.bottom - 9 * innerRectangleSize,
		hostRectangle.right - 9.5 * innerRectangleSize,
		hostRectangle.bottom - 6 * innerRectangleSize
	);
	
	this->Translate(pDC, rightThinCactusPart.CenterPoint().x, rightThinCactusPart.bottom, false);
	this->Rotate(pDC, (firstCactusPartDeg * M_PI / 180), false);
	this->Translate(pDC, -rightThinCactusPart.CenterPoint().x, -rightThinCactusPart.bottom, false);

	PlayEnhMetaFile(pDC->m_hDC, rotatingCactusPart, rightThinCactusPart);

	CRect firstCircle(int(hostRectangle.left + 9.6 * innerRectangleSize),
		int(hostRectangle.bottom - 9.4 * innerRectangleSize),
		int(hostRectangle.left + 10.4 * innerRectangleSize),
		int(hostRectangle.bottom - 8.6 * innerRectangleSize));

	CRect secondCircle(int(hostRectangle.left + 9.6 * innerRectangleSize),
		int(hostRectangle.bottom - 12.4 * innerRectangleSize),
		int(hostRectangle.left + 10.4 * innerRectangleSize),
		int(hostRectangle.bottom - 11.6 * innerRectangleSize));
	

	CRect ThinCactusPart(
		hostRectangle.left + 9.5 * innerRectangleSize,
		hostRectangle.bottom - 11.9 * innerRectangleSize,
		hostRectangle.right - 9.5 * innerRectangleSize,
		hostRectangle.bottom - 8.9 * innerRectangleSize
	);

	CRect middleCactusPart(hostRectangle.left + 9.1 * innerRectangleSize, //deo srednje debljine a ne lokacije
		hostRectangle.bottom - 15 * innerRectangleSize,
		hostRectangle.right - 9.1 * innerRectangleSize,
		hostRectangle.bottom - 12 * innerRectangleSize);

	CRect fatCactusPart(hostRectangle.left + 8.8 * innerRectangleSize,
		hostRectangle.bottom - 15 * innerRectangleSize,
		hostRectangle.right - 8.8 * innerRectangleSize,
		hostRectangle.bottom - 12 * innerRectangleSize);

	
	PlayEnhMetaFile(pDC->m_hDC, cactusStandardPart, ThinCactusPart);
	PlayEnhMetaFile(pDC->m_hDC, cactusStandardPart, fatCactusPart);
	pDC->Ellipse(secondCircle);

	this->Translate(pDC, ThinCactusPart.CenterPoint().x, ThinCactusPart.bottom, false);
	this->Rotate(pDC,  -(M_PI / 4), false);
	this->Translate(pDC, -ThinCactusPart.CenterPoint().x, -ThinCactusPart.bottom, false);
	
	PlayEnhMetaFile(pDC->m_hDC, cactusStandardPart, ThinCactusPart);
	PlayEnhMetaFile(pDC->m_hDC, cactusStandardPart, fatCactusPart);
	pDC->Ellipse(secondCircle);

	this->Translate(pDC, ThinCactusPart.CenterPoint().x, ThinCactusPart.bottom, false);
	this->Rotate(pDC, 2 * M_PI / 4, false);
	this->Translate(pDC, -ThinCactusPart.CenterPoint().x, -ThinCactusPart.bottom, false);

	PlayEnhMetaFile(pDC->m_hDC, cactusStandardPart, ThinCactusPart);

	this->Translate(pDC, middleCactusPart.CenterPoint().x, middleCactusPart.bottom, false);
	this->Rotate(pDC, -(M_PI / 4), false);
	this->Translate(pDC, -middleCactusPart.CenterPoint().x, -middleCactusPart.bottom, false);
	
	PlayEnhMetaFile(pDC->m_hDC, cactusStandardPart, middleCactusPart);

	this->Translate(pDC, middleCactusPart.CenterPoint().x, middleCactusPart.bottom, false);
	this->Rotate(pDC, M_PI / 4, false);
	this->Translate(pDC, -middleCactusPart.CenterPoint().x, -middleCactusPart.bottom, false);


	pDC->Ellipse(secondCircle);

	pDC->Ellipse(firstCircle);

	this->DrawSecondMovingCactusPart(pDC);

	this->NoTranform(pDC);

	pDC->SelectObject(oldBrush);
	darkGreenBrush.DeleteObject();
	SetGraphicsMode(pDC->m_hDC, prevMode);
	DeleteEnhMetaFile(cactusStandardPart);
	DeleteEnhMetaFile(rotatingCactusPart);
}

void CIND17359View::DrawSecondMovingCactusPart(CDC* pDC){


	HENHMETAFILE rotatingCactusPart = GetEnhMetaFile(CString("res/cactus_part_light.emf"));

	CRect middleCactusPart(hostRectangle.left + 9.1 * innerRectangleSize, 
		hostRectangle.bottom - 15 * innerRectangleSize,
		hostRectangle.right - 9.1 * innerRectangleSize,
		hostRectangle.bottom - 12 * innerRectangleSize);

	this->Translate(pDC, middleCactusPart.CenterPoint().x, middleCactusPart.bottom, false);
	this->Rotate(pDC, (secondCactusPartDeg * M_PI / 180), false);
	this->Translate(pDC, -middleCactusPart.CenterPoint().x, -middleCactusPart.bottom, false);

	PlayEnhMetaFile(pDC->m_hDC, rotatingCactusPart, middleCactusPart);

	DeleteEnhMetaFile(rotatingCactusPart);

}

void CIND17359View::Scale(CDC* pDC, float sX, float sY, bool rightMultiply) {
	
	XFORM xform;
	xform.eM11 = sX;
	xform.eM12 = 0.0;
	xform.eM21 = 0.0;
	xform.eM22 = sY;
	xform.eDx = 0.0;
	xform.eDy = 0.0;

	if (rightMultiply)
		ModifyWorldTransform(pDC->m_hDC, &xform, MWT_RIGHTMULTIPLY);
	else
		ModifyWorldTransform(pDC->m_hDC, &xform, MWT_LEFTMULTIPLY);
}

void CIND17359View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply) {

	XFORM xform;
	xform.eM11 = 1.0;
	xform.eM12 = 0.0;
	xform.eM21 = 0.0;
	xform.eM22 = 1.0;
	xform.eDx = dX;
	xform.eDy = dY;

	if (rightMultiply)
		ModifyWorldTransform(pDC->m_hDC, &xform, MWT_RIGHTMULTIPLY);
	else
		ModifyWorldTransform(pDC->m_hDC, &xform, MWT_LEFTMULTIPLY);
}

void CIND17359View::Rotate(CDC* pDC, float angle, bool rightMultiply) {

	XFORM xform;
	xform.eM11 = float(cos(angle));
	xform.eM12 = float(sin(angle));
	xform.eM21 = float(-sin(angle));
	xform.eM22 = float(cos(angle));
	xform.eDx = 0.0f;
	xform.eDy = 0.0f;

	if (rightMultiply)
		ModifyWorldTransform(pDC->m_hDC, &xform, MWT_RIGHTMULTIPLY);
	else
		ModifyWorldTransform(pDC->m_hDC, &xform, MWT_LEFTMULTIPLY);
}

void CIND17359View::NoTranform(CDC* pDC)
{
	XFORM f;
	f.eM11 = 1;
	f.eM12 = 0;
	f.eM21 = 0;
	f.eM22 = 1;
	f.eDx = 0;
	f.eDy = 0;
	pDC->SetWorldTransform(&f);
}

int CIND17359View::mod(int k, int n) { return ((k %= n) < 0) ? k + n : k; }

// CIND17359View printing

BOOL CIND17359View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CIND17359View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CIND17359View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CIND17359View diagnostics

#ifdef _DEBUG
void CIND17359View::AssertValid() const
{
	CView::AssertValid();
}

void CIND17359View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIND17359Doc* CIND17359View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIND17359Doc)));
	return (CIND17359Doc*)m_pDocument;
}
#endif //_DEBUG


// CIND17359View message handlers


void CIND17359View::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	switch (nChar)
	{
	case 'G':
		showGrid = !showGrid;
		Invalidate();
		break;
	case 'J':
		firstCactusPartDeg = mod((firstCactusPartDeg - 6), 360);
		Invalidate();
		break;
	case 'L':
		firstCactusPartDeg = mod((firstCactusPartDeg + 6), 360);
		Invalidate();
		break;
	case 'A':
		secondCactusPartDeg = mod((secondCactusPartDeg - 6), 360);
		Invalidate();
		break;
	case 'D':
		secondCactusPartDeg = mod((secondCactusPartDeg + 6), 360);
		Invalidate();
		break;
	}

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}
