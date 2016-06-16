#pragma once

#include <vector>

using namespace std;

namespace RealtimeCurve{
	const int MaxPointsCount = 512;	// �������洢����
	const int MaxLinesCount = 10;	// �ؼ�����������߸���

	class CLine
	{
	public:
		CLine(CString name=_T(""),
		int lineStyle = PS_SOLID, 
		COLORREF lineColor = RGB(255,0,0),
		int lineWidth = 2);
		CLine(const CLine& nLine);
		CLine& operator = (const CLine& nLine);
		~CLine();
		
		_declspec(property(get = getLineName,put = setLineName))	CString lineName;
		_declspec(property(get = getShowStatus,put = setShowStatus)) BOOL showStatus;
		_declspec(property(get = getLineColor,put = setLineColor)) COLORREF lineColor;
		_declspec(property(get = getLineType,put = setLineType)) int lineType;
		_declspec(property(get = getLineWidth,put = setLineWidth)) int lineWidth;

		void	AddPoint(float x, float y);
		float	GetPointX(int nIndex);
		float	GetPointY(int nIndex);
		int		GetPointCount();
		
		inline CString	getLineName()				{	return this->LineName;	}
		inline void		setLineName(CString name)	{	this->LineName = name;	}
		inline BOOL		getShowStatus()				{	return this->IsShow;	}
		inline void		setShowStatus(BOOL showStatus){	this->IsShow = showStatus;	}
		inline COLORREF getLineColor()				{	return this->LineColor;}
		inline void		setLineColor(COLORREF color){	this->LineColor = lineColor;	};
		inline int		getLineType()				{	return this->LineType;}
		inline void		setLineType(int lineType)	{	this->LineType = lineType;	};
		inline int		getLineWidth()				{	return this->LineWidth;}
		inline void		setLineWidth(int lineWidth)	{	this->LineWidth = lineWidth;	};

	public:
		CString		LineName;		// ��������
		BOOL        IsShow;			// �����Ƿ���ʾ
		COLORREF	LineColor;		// ��ɫ
		int         LineType;		// ���� solid,dash
		int         LineWidth;		// �߿� pixel
		struct Point{
			float x;
			float y;
		};
	private:		
		int			m_currentSize;		// ��Ч���������
		Point *		m_pointArrayPtr;	// �洢������Point������
		CRITICAL_SECTION g_cs ;
	};

	class CAxis
	{
	
	public:		
		struct AxisRangeStruct{		// �����᷶Χ
			float AxisMinValue;		// ����Сֵ
			float AxisMaxValue;		// �����ֵ
		};
		
		CAxis(COLORREF color = RGB(0,255,0),
				int style = PS_SOLID, 
				int width = 2,
				float minValue = 0.0f, 
				float maxValue = 500.0);
		~CAxis(){	}
		CAxis(const CAxis& axis);
		CAxis &operator = (const CAxis& axis);

		inline void SetAxisRange(float minValue=0.0f,float maxValue=500.0f){
			m_axisRange.AxisMinValue = minValue;
			m_axisRange.AxisMaxValue = maxValue;
		}
		inline float GetAxisRange(){	
			return this->m_axisRange.AxisMaxValue-this->m_axisRange.AxisMinValue;
		}
		inline float GetRangeLowerLimit()	{	return this->m_axisRange.AxisMinValue;	}
		inline float GetRangeUpperLimit()	{	return this->m_axisRange.AxisMaxValue;	}
			
	public:
		BOOL        IsShow;			// �Ƿ���ʾ������
		COLORREF	AxisColor;		// ��ɫ
		int         AxisStyle;		// ����
		int         AxisWidth;		// �߿�		

		int			CoorTextBoxWidth;	// �����ı��� ���
		int			CoorTextBoxHeight;	// �����ı��� �߶�
	private:
		AxisRangeStruct m_axisRange;	// �����ֵ�ķ�Χ
	};

	class CPlot :
		public CStatic
	{
		DECLARE_DYNAMIC(CPlot)

	public:
		CPlot(void);
		virtual ~CPlot(void);

		void Start();
		void Stop();
	
		
		void AddNewLine(CString name = _T(""),
					int style = PS_SOLID, 
					COLORREF color = RGB(255,0,0), 
					int iThick = 2);
		void AddNewPoint(float x,float y,int nLineIndex);	//��ĳһ���������������
		CLine* GetLineByIndex(int nIndex);	// �õ���nIndex����0��ʼ�������ߵ�����
		CLine* GetLineByName(CString name);	// �����������ƻ�ȡ����
		int    GetLineCount();				// ��ȡ��ǰ��Ч���߸���

		void SetRate(int nRate);
		void SetBkColor(COLORREF clrBkColor);
		CAxis& GetAxisY();
		CAxis& GetAxisX();

	private:
		void RefreshLayout();			// ˢ��ҳ�沼��
		void RefreshPlot(CDC* pDC);		// ˢ�¿ؼ�
		void DrawBackground(CDC* pDC);	// ���Ʊ���
		void DrawAxises(CDC* pDC);		// ����������
		void DrawGrids(CDC* pDC);		// ��������
		void DrawLine(CDC* pDC,const CRect& rectZone,const CPoint* pPtr,int nCount);
		void DrawLines(CDC* pDC);		// ����ȫ������
		void DrawLegend(CDC* pDC,CRect& rectZone);		// ����ͼ��
		void DrawTile(CDC* pDC,CRect& rectZone);		// ���Ʊ���

		void ScaleProcess();		// �Ŵ����
		
		// ���������� rect1 �� rect2 �Ľ�������
		CRect IntersectionRect(const CRect& rect1,const CRect& rect2);
		// �ж�һ�����Ƿ��ھ�����
		BOOL PointOnRect(const CRect& rect,const CPoint& point );
		// �ж�һ����point�Ƿ��ھ���rect�ڲ�
		BOOL PointInRect(const CRect& rect,const CPoint& point );	
		// ��������֮��������rect�ߵĽ���
		CPoint IntersectionRectLine(const CRect& rect,const CPoint& inPoint,const CPoint& exPoint );
	public:
		//float		XMoveStep;		// ÿ���ƶ�X�����ӵ�ֵ

		BOOL        ShowGrid;		// �Ƿ���ʾ����
		COLORREF	GridColor;		// ������ɫ
		int			GridStyle;		// ��������
		int			GridWidth;		// �����߿�
		int			GridSize;		// ������		
		int			ShowTextGrap;	// ÿ���������ʾһ������ֵ
		COLORREF	BkGndColor;		// ������ɫ
		int			RefreshRate;	// ˢ��ͼ�����ڣ�ms
	private:
		BOOL	m_bAdjustable;		// �Ƿ���Ҫ�Զ�����
		// �������
		CRect	m_rectCtrl;                 // �ؼ���������
		CRect	m_rectPlot;                 // ��ͼ��������
		CRect	m_rectTitle;				// �����������
		CRect	m_rectLegend;				// ͼ����������
		int		m_marginLeft;				// ������׿��
		int		m_marginRight;				// �Ҳ����׿��
		int		m_marginTop;				// �ϲ����׿��
		int		m_marginBottom;				// �²����׿��
		int		m_titleHight;				// ����߶�
		int		m_legendHeight;				// ͼ���߶�
		//	���������
		CAxis m_axisX;		// X ��
		CAxis m_axisY;      // Y ��

		float		m_vppXAxis;		// ÿ�����ش����X��ֵ
		float		m_vppYAxis;		// ÿ�����ص�����Y��ֵ
		// �������
		CLine * m_linePtrArray[MaxLinesCount];	// ָ������
		int validLinesCount;					// ��Ч�ߵĸ���
		// �������
		float m_originXLwLmt,m_originXUpLmt;	// �Ѿ�������Ӧ����µ�X��Y�᷶Χ
		float m_originYLwLmt,m_originYUpLmt;	
		CPoint m_startPoint,m_endPoint;			// ��������ֹ��

	public:
		DECLARE_MESSAGE_MAP()
		afx_msg void OnTimer(UINT nIDEvent);
		afx_msg void OnPaint();
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg void OnLButtonDown(UINT nFlag,CPoint point);
		afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
		afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	
	};


}
