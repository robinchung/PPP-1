// UpComputerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UpComputer.h"
#include "UpComputerDlg.h"
#include "math.h"
#include "ScreenCapture.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CUpComputerDlg �Ի���




CUpComputerDlg::CUpComputerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUpComputerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_time	= 0.0f;////////////////////////////////////////////yingmou
	m_iBtnExitFromRight = 10;
	m_iBtnExitFromBottom =10;
}

void CUpComputerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TURN, m_turn);
	DDX_Control(pDX, IDC_PRESSURE, m_pressure);
	DDX_Control(pDX, IDC_OIL, m_oil);
	DDX_Control(pDX, IDC_GAS, m_gas);
	DDX_Control(pDX, IDC_TEMPERATURE, m_temperature);
	DDX_Control(pDX, IDC_PLOT, m_plot);
}

BEGIN_MESSAGE_MAP(CUpComputerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()             ////////////////////////////////////////��ӳ�����ڶ�ʱ��--------��Ӣı
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_START, &CUpComputerDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_STOP, &CUpComputerDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_DISP_LINE1, &CUpComputerDlg::OnBnClickedDispLine1)
	ON_BN_CLICKED(IDC_DISP_LINE2, &CUpComputerDlg::OnBnClickedDispLine2)
	ON_WM_SIZING()
	ON_COMMAND(ID_32783, &CUpComputerDlg::OnCaptureScreen)
	ON_BN_CLICKED(IDC_BTNOPENPORT, &CUpComputerDlg::OnBnClickedBtnopenport)
	ON_BN_CLICKED(IDC_BTNSEND, &CUpComputerDlg::OnBnClickedBtnsend)
END_MESSAGE_MAP()
#ifndef YMBUG
BEGIN_EASYSIZE_MAP(CUpComputerDlg)
	EASYSIZE(IDC_STATIC,ES_BORDER,ES_BORDER,ES_BORDER,ES_BORDER,0)
	EASYSIZE(IDC_TURN,ES_KEEPSIZE ,ES_BORDER ,IDC_PRESSURE,ES_KEEPSIZE,0)
	EASYSIZE(IDC_PRESSURE,IDC_TURN,ES_BORDER,IDC_OIL,ES_KEEPSIZE,0)
	EASYSIZE(IDC_OIL,IDC_PRESSURE,ES_BORDER,IDC_GAS,ES_KEEPSIZE,0)
	EASYSIZE(IDC_GAS,IDC_OIL,ES_BORDER,IDC_TEMPERATURE,ES_KEEPSIZE,0)
	EASYSIZE(IDC_TEMPERATURE,IDC_GAS,ES_BORDER,ES_KEEPSIZE,ES_KEEPSIZE,0)
END_EASYSIZE_MAP
#endif

// CUpComputerDlg ��Ϣ�������

BOOL CUpComputerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
#ifndef YMBUG
	CMenu* psetmenu = new CMenu;
	psetmenu -> LoadMenu(IDR_SETMENU);
#endif
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	COLORREF m_colorNeedle;
	m_colorNeedle = RGB(255, 255, 255);//etSysColor(COLOR_ACTIVEBORDER);
	m_turn.SetNeedleColor(m_colorNeedle);
	m_turn.SetColorTick(TRUE);
	m_pressure.SetNeedleColor(m_colorNeedle);
	m_pressure.SetColorTick(TRUE);
	m_oil.SetNeedleColor(m_colorNeedle);
	m_oil.SetColorTick(TRUE);
	m_gas.SetNeedleColor(m_colorNeedle);
	m_gas.SetColorTick(TRUE);
	m_temperature.SetNeedleColor(m_colorNeedle);
	m_temperature.SetColorTick(TRUE);
	//SetTimer(1,200,NULL);//////////////////////////////yingmou
	/////////////////////////////////////////////////init axes yingmou
	((CButton*)GetDlgItem(IDC_DISP_LINE1))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_DISP_LINE2))->SetCheck(TRUE);
	
	//remember initial position
	GetWindowRect(&m_rectOldWindow);
//	m_btnExit.GetClientRect(&m_rectBtnExit);
	m_plot.GetWindowRect(&m_rectOldPlotWindow);
	TRACE("m_rectOldPlotWindow.left=%d,m_rectOldPlotWindow.width=%d\n",m_rectOldPlotWindow.left,m_rectOldPlotWindow.Width());
	ScreenToClient(&m_rectOldPlotWindow);
	TRACE("m_rectOldPlotWindow.left=%d,m_rectOldPlotWindow.width=%d\n",m_rectOldPlotWindow.left,m_rectOldPlotWindow.Width());

	m_plot.AddNewLine(_T("PV"),PS_SOLID,RGB(255,0,0));
	m_plot.AddNewLine(_T("SV"),PS_SOLID,RGB(0,255,0));

	m_plot.GetAxisX().AxisColor=RGB(0,255,0);
	m_plot.GetAxisY().AxisColor=RGB(0,255,0);
#ifndef YMBUG
	INIT_EASYSIZE;///////////////////important yingmou
	comoperating = new ComOperating();//ע�⣺û����delete������Ҫ���һ�£���ֹ�ڴ�й¶
	CheckAndDisplayCom();
#endif
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CUpComputerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CUpComputerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CUpComputerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CUpComputerDlg::OnTimer(UINT nIDEvent) ///////////////////////////////////////////�˺���������Ӧ��ʱ�����ٽ��в���----yingmou
{
	// TODO: Add your message handler code here and/or call default
	static double dMStep = 0.5 ;
	static double dMValue = 0.0 ;

	dMValue += dMStep ;
	if (dMValue > m_turn.m_dMaxValue)
	{
		dMStep = -fabs(dMStep) ;
		dMValue = m_turn.m_dMaxValue-dMStep ;
	}
	else if (dMValue < m_turn.m_dMinValue)
	{	
		dMStep = fabs(dMStep) ;
		dMValue = m_turn.m_dMinValue+dMStep ;
	}
	m_turn.UpdateNeedle(dMValue) ;
	m_pressure.UpdateNeedle(dMValue);
	m_oil.UpdateNeedle(dMValue);
	m_gas.UpdateNeedle(dMValue);
	m_temperature.UpdateNeedle(dMValue);

	CDialog::OnTimer(nIDEvent);
	///////////////////////////////////////////////display axes
	float  y0 = 500*sin(m_time/5.0f);
	float y1 = 500*cos(m_time/15.0f);
	
	m_plot.AddNewPoint(m_time,y0,0);
	m_plot.AddNewPoint(m_time,y1,1);
	m_time += 0.20f;
}
void CUpComputerDlg::OnSize(UINT nType, int cx, int cy)              /////////////////////////�Ի�������϶���С
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	//CWnd* pWnd=GetDlgItem(IDC_STATIC);   
	//if(pWnd->GetSafeHwnd())   
	//pWnd->MoveWindow(15,15,cx-30,cy-30); 
	CRect rect;
	GetClientRect(&rect);
	//if(m_btnExit.GetSafeHwnd())
	//{
		//m_btnExit.MoveWindow(rect.right-m_iBtnExitFromRight-m_rectBtnExit.Width(),
	//	rect.bottom-m_iBtnExitFromBottom-m_rectBtnExit.Height(),
	//	m_rectBtnExit.Width(),m_rectBtnExit.Height());
	//}
	if(m_plot.GetSafeHwnd())
	{
		//TRACE("m_rectOldPlotWindow.left=%d,m_rectOldPlotWindow.width=%d\n",m_rectOldPlotWindow.left,m_rectOldPlotWindow.Width());

		m_plot.MoveWindow(m_rectOldPlotWindow.left,
			m_rectOldPlotWindow.top,
			rect.right-m_iBtnExitFromRight-5-m_rectOldPlotWindow.left,
			rect.bottom-m_iBtnExitFromBottom-m_rectBtnExit.Height()-7-m_rectOldPlotWindow.top);
	}
#ifndef YMBUG
	UPDATE_EASYSIZE;/////////////////////////////about easysize yingmou
#endif

}

void CUpComputerDlg::OnBnClickedStart()
{
	// TODO: Add your control notification handler code here
	SetTimer(1,10,NULL);
	m_plot.SetRate(10);//
	m_plot.Start();

	GetDlgItem(IDC_START)->EnableWindow(FALSE);
}

void CUpComputerDlg::OnBnClickedStop()
{
	// TODO: Add your control notification handler code here
	KillTimer(1);
	m_plot.Stop();
	//for(int i=0;i<m_plot.GetLineCount();i++)
	//{
	//	m_plot.GetLineByIndex(i).RemoveAllPoints();
	//}
	GetDlgItem(IDC_START)->EnableWindow();
	m_plot.Invalidate();
}

void CUpComputerDlg::OnBnClickedDispLine1()
{
	// TODO: Add your control notification handler code here
	m_plot.GetLineByIndex(0)->IsShow = ((CButton*)GetDlgItem(IDC_DISP_LINE1))->GetCheck(); 
}

void CUpComputerDlg::OnBnClickedDispLine2()
{
	// TODO: Add your control notification handler code here
	m_plot.GetLineByIndex(1)->IsShow = ((CButton*)GetDlgItem(IDC_DISP_LINE2))->GetCheck();
}

void CUpComputerDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialog::OnSizing(fwSide, pRect);

	// TODO: Add your message handler code here
	/*if(pRect->right - pRect->left <=m_rectOldWindow.Width())
     	pRect->right = pRect->left + m_rectOldWindow.Width();
	
     if(pRect->bottom - pRect->top <=m_rectOldWindow.Height())
     	pRect->bottom = pRect->top + m_rectOldWindow.Height();*/
	CDialog::OnSizing(fwSide, pRect);
}

#ifndef YMBUG
void CUpComputerDlg::Test_captureScreen()
{
	/* CDC *pDesktopDC = CDC::FromHandle(::GetDC(NULL));//��ȡ��ǰ������ĻDC
	 int width = pDesktopDC->GetDeviceCaps(HORZRES);
	 int height = pDesktopDC->GetDeviceCaps(VERTRES);

	 CBitmap    memBmp;
	 CDC memDC;
	 memBmp.CreateCompatibleBitmap(pDesktopDC, width, height);
	 memDC.CreateCompatibleDC(pDesktopDC);
	 memDC.SelectObject(&memBmp);  //��memBitmapѡ���ڴ�DC

	 memDC.BitBlt(0, 0, width, height, pDesktopDC, 0, 0, SRCCOPY);//������Ļͼ���ڴ�DC

	 BITMAP bmp;
	 memBmp.GetBitmap(&bmp); //CBitmap��BITMAP

	 BITMAPINFOHEADER m_bihScreen;  
	 ZeroMemory(&m_bihScreen, sizeof(BITMAPINFOHEADER));//λͼ��Ϣͷ
	 m_bihScreen.biBitCount = bmp.bmBitsPixel;//ÿ�������ֽڴ�С
	 m_bihScreen.biCompression = BI_RGB;
	 m_bihScreen.biHeight = bmp.bmHeight;//�߶�
	 m_bihScreen.biPlanes = 1;
	 m_bihScreen.biSize = sizeof(BITMAPINFOHEADER);
	 m_bihScreen.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;//ͼ�����ݴ�С
	 m_bihScreen.biWidth = bmp.bmWidth;//���
	 byte *m_pbmScreenData = new byte[bmp.bmWidthBytes * bmp.bmHeight];
	// GetDIBits(/*pDesktopDC->m_hDC*///memDC.m_hDC, (HBITMAP)memBmp.m_hObject, 0, height, m_pbmScreenData,  
	//	 (LPBITMAPINFO) &m_bihScreen, DIB_RGB_COLORS);//��ȡλͼ����  ��BITMAP���ڴ�����

	 //TwoDimesionArray<RGBQUAD> colors(width,height);
	/* for (int j=0;j<height;++j)
	 {
		 for (int i=0;i<width;++i)
		{
			 byte *p=m_pbmScreenData+(height-1-j)*bmp.bmWidthBytes+i*4;
			RGBQUAD c={int(*p),int(*(p+1)),int(*(p+2))};
			//colors.SetValue(i,j,c);
		}
	 }

	//ImageIO writer;
	//writer.WriteBmp(colors,"D:\\z.bmp");*/

	CDC *pDC=GetDesktopWindow()->GetDC();//��ĻDC
    int BitPerPixel = pDC->GetDeviceCaps(BITSPIXEL);//�����ɫģʽ
    int Width = pDC->GetDeviceCaps(HORZRES);
    int Height = pDC->GetDeviceCaps(VERTRES);
    
    CDC memDC;//�ڴ�DC
    memDC.CreateCompatibleDC(pDC);
    
    CBitmap memBitmap, *oldmemBitmap;//��������Ļ���ݵ�bitmap
    memBitmap.CreateCompatibleBitmap(pDC, Width, Height);

    oldmemBitmap = memDC.SelectObject(&memBitmap);//��memBitmapѡ���ڴ�DC
    memDC.BitBlt(0, 0, Width, Height, pDC, 0, 0, SRCCOPY);//������Ļͼ���ڴ�DC

    //���´��뱣��memDC�е�λͼ���ļ�
    BITMAP bmp;
    memBitmap.GetBitmap(&bmp);//���λͼ��Ϣ
    
    FILE *fp = fopen("d:\\PaperPlane.jpg", "w+b");

    BITMAPINFOHEADER bih = {0};//λͼ��Ϣͷ
    bih.biBitCount = bmp.bmBitsPixel;//ÿ�������ֽڴ�С
    bih.biCompression = BI_RGB;
    bih.biHeight = bmp.bmHeight;//�߶�
    bih.biPlanes = 1;
    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;//ͼ�����ݴ�С
    bih.biWidth = bmp.bmWidth;//���
    
    BITMAPFILEHEADER bfh = {0};//λͼ�ļ�ͷ
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);//��λͼ���ݵ�ƫ����
    bfh.bfSize = bfh.bfOffBits + bmp.bmWidthBytes * bmp.bmHeight;//�ļ��ܵĴ�С
    bfh.bfType = (WORD)0x4d42;
    
    fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);//д��λͼ�ļ�ͷ
    
    fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);//д��λͼ��Ϣͷ
    
    byte * p = new byte[bmp.bmWidthBytes * bmp.bmHeight];//�����ڴ汣��λͼ����

    GetDIBits(memDC.m_hDC, (HBITMAP) memBitmap.m_hObject, 0, Height, p, 
        (LPBITMAPINFO) &bih, DIB_RGB_COLORS);//��ȡλͼ����

    fwrite(p, 1, bmp.bmWidthBytes * bmp.bmHeight, fp);//д��λͼ����

    delete [] p;

    fclose(fp);

    memDC.SelectObject(oldmemBitmap);
	memDC.DeleteDC();
	ReleaseDC(pDC);
}

#endif
void CUpComputerDlg::OnCaptureScreen()
{
	// TODO: Add your command handler code here
	Test_captureScreen();
	ScreenCapture scp;
	scp.DoModal();

}

void CUpComputerDlg::OnBnClickedBtnopenport()
{
	// TODO: Add your control notification handler code here
	//string strtemp;
	//if(comoperating->GetCom(3,&strtemp));
	//((CComboBox *)GetDlgItem(IDC_CBXCOM))->AddString(strtemp.c_str());
	 //((CComboBox *)GetDlgItem(IDC_CBXCOM))->SetCurSel(0);
	SettingParam_t testparam = {3,9600,0,8};
	comoperating->ComSetting(&testparam);
	comoperating->OpenCom(&testparam);
}

void CUpComputerDlg::OnBnClickedBtnsend()
{
	// TODO: Add your control notification handler code here
	CEdit *pbox;
	pbox = (CEdit*)GetDlgItem(IDC_EDITSENDDATA);
	CString str;
	pbox->GetWindowTextA(str);
	BYTE *strsend;
	strsend = (BYTE*)str.GetBuffer(str.GetLength());
	comoperating->SendData(strsend,2);
}

void CUpComputerDlg::CheckAndDisplayCom()
{
	string strtemp;
	for(int num = 1;num<=9;num++)
	{
		if(comoperating->GetCom(num,&strtemp))
		{
		((CComboBox *)GetDlgItem(IDC_CBXCOM))->AddString(strtemp.c_str());
		((CComboBox *)GetDlgItem(IDC_CBXCOM))->SetCurSel(num - 1);
		}
		else 
		((CComboBox *)GetDlgItem(IDC_CBXCOM))->EnableWindow(false);
	}
	
}