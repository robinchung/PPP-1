// ScreenCapture.cpp : implementation file
//

#include "stdafx.h"
#include "UpComputer.h"
#include "ScreenCapture.h"


// ScreenCapture dialog

IMPLEMENT_DYNAMIC(ScreenCapture, CDialog)

ScreenCapture::ScreenCapture(CWnd* pParent /*=NULL*/)
	: CDialog(ScreenCapture::IDD, pParent)
{

}

ScreenCapture::~ScreenCapture()
{
}

void ScreenCapture::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ScreenCapture, CDialog)
END_MESSAGE_MAP()


// ScreenCapture message handlers
