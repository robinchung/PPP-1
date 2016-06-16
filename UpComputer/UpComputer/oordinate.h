#pragma once


// Coordinate





class Coordinate : public CStatic
{
	DECLARE_DYNAMIC(Coordinate)

public:
	Coordinate();
	virtual ~Coordinate();
	void DrawAxes(CDC *pDC,CRect &rect);
	void DrawArrow(POINT startpoint,POINT endpoint);
protected:
	CDC m_dcBackground;
	CBitmap m_bmBackground;
	CBitmap* m_bmOldBackground;
	CRect m_rectCtrl;
	CPoint left,right;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


