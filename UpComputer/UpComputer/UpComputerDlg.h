// UpComputerDlg.h : ͷ�ļ�
//

#pragma once
#include "Plot.h"
#include "meterturn.h"
#include "meterpressure.h"
#include "meteroil.h"
#include "metergas.h"
#include "metertemperature.h"
#include "oordinate.h"
#include "ComOperating.h"

using namespace RealtimeCurve;

// CUpComputerDlg �Ի���
class CUpComputerDlg : public CDialog
{
// ����
public:
	CUpComputerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_UPCOMPUTER_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	void Test_captureScreen();/////////////////////////////////////////////////////yingmou
	void CheckAndDisplayCom();

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);///////////////////////////////���ڲ���-----yingmou
	CRect m_rectBtnExit;
	CRect m_rectOldWindow;
	CRect m_rectOldPlotWindow;
	int m_iBtnExitFromRight;
	int m_iBtnExitFromBottom;
	CPlot m_plot;
	DECLARE_MESSAGE_MAP()
private:
	float m_time;
#ifndef YMBUG
	DECLARE_EASYSIZE          //////////���� easysize yingmou
	ComOperating *comoperating;
#endif
public:
	MeterTurn m_turn;
	MeterPressure m_pressure;
	MeterOil m_oil;
	MeterGas m_gas;
	MeterTemperature m_temperature;
	//Coordinate m_coordinate;
	
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedDispLine1();
	afx_msg void OnBnClickedDispLine2();
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);


	afx_msg void OnCaptureScreen();
	afx_msg void OnBnClickedBtnopenport();
	afx_msg void OnBnClickedBtnsend();
};
