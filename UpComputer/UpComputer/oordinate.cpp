// oordinate.cpp : implementation file
//

#include "stdafx.h"
#include "UpComputer.h"
#include "oordinate.h"
#include "MemDC.h"
#include "MeterGas.h"

// Coordinate

IMPLEMENT_DYNAMIC(Coordinate, CStatic)

Coordinate::Coordinate()
{

}

Coordinate::~Coordinate()
{
}


BEGIN_MESSAGE_MAP(Coordinate, CStatic)
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// Coordinate message handlers



void Coordinate::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CStatic::OnPaint() for painting messages
	GetClientRect (&m_rectCtrl);
	CMemDC memDC(&dc, &m_rectCtrl);
	if(m_dcBackground.GetSafeHdc()== NULL|| (m_bmBackground.m_hObject == NULL))
	{
		m_dcBackground.CreateCompatibleDC(&dc);
		m_bmBackground.CreateCompatibleBitmap(&dc, m_rectCtrl.Width(), m_rectCtrl.Height()) ;
		//m_dcBackground.FillSolidRect(m_rectCtrl,RGB(0,0,0));
		m_bmOldBackground = m_dcBackground.SelectObject(&m_bmBackground) ;
		DrawAxes(&m_dcBackground,m_rectCtrl);
	}
	memDC.BitBlt(0, 0, m_rectCtrl.Width(), m_rectCtrl.Height(), 
		&m_dcBackground, 0, 0, SRCCOPY) ;
}

void Coordinate::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
}

void Coordinate::DrawAxes(CDC *pDC,CRect &rect)
{
	CRgn rgn;
	POINT pt1[4] = {{0,0},{90,80},{90,220},{0,297}};//(0,0)->(450,297)
	POINT pt2[4] = {{90,80},{360,80},{360,220},{90,220}};
	POINT pt3[4] = {{90,220},{360,220},{450,297},{0,297}};
	BYTE style[4] = {{ PT_MOVETO},{PT_LINETO},{PT_LINETO},{PT_LINETO}}; 
	CBrush brush(RGB(60,179,113));
	CBrush brush2(RGB(255,255,255));
	pDC->FillRect(rect,&brush2);
	pDC->SelectObject(&brush);
	pDC->Polygon(pt1,4);
	pDC->Polygon(pt2,4);
	pDC->Polygon(pt3,4);
}

void  Coordinate::DrawArrow(POINT startPoint,POINT endPoint)
{
	/*CClientDC dc(this);
	CPen pen(PS_SOLID,1,RGB(0,0,255));
	dc.SelectObject(&pen);
	dc.MoveTo(startPoint);
	dc.LineTo(endPoint);

	double PI = 3.1415926;
	double t=PI/4; //箭头与直线夹角
	double l=0.2; //箭头边长度占直线长度的百分比

	POINT arrowPoint;

	arrowPoint.x = (int)(l*((startPoint.x-endPoint.x)*cos(t)-(startPoint.y-endPoint.y)*sin(t))+endPoint.x);
	arrowPoint.y = (int)(l*((startPoint.x-endPoint.x)*sin(t)+(startPoint.y-endPoint.y)*cos(t))+endPoint.y);
	dc.MoveTo(endPoint);
	dc.LineTo(arrowPoint);

	arrowPoint.x = (int)(l*((startPoint.x-endPoint.x)*cos(-t)-(startPoint.y-endPoint.y)*sin(-t))+endPoint.x);
	arrowPoint.y = (int)(l*((startPoint.x-endPoint.x)*sin(-t)+(startPoint.y-endPoint.y)*cos(-t))+endPoint.y);
	dc.MoveTo(endPoint);
	dc.LineTo(arrowPoint);*/

}