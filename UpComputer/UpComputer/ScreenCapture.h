#pragma once


// ScreenCapture dialog

class ScreenCapture : public CDialog
{
	DECLARE_DYNAMIC(ScreenCapture)

public:
	ScreenCapture(CWnd* pParent = NULL);   // standard constructor
	virtual ~ScreenCapture();

// Dialog Data
	enum { IDD = IDD_DIALOGCAPTURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
