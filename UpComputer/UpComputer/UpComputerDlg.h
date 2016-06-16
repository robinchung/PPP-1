// UpComputerDlg.h : 头文件
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

// CUpComputerDlg 对话框
class CUpComputerDlg : public CDialog
{
// 构造
public:
	CUpComputerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_UPCOMPUTER_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	void Test_captureScreen();/////////////////////////////////////////////////////yingmou
	void CheckAndDisplayCom();

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);///////////////////////////////用于测试-----yingmou
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
	DECLARE_EASYSIZE          //////////声明 easysize yingmou
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
