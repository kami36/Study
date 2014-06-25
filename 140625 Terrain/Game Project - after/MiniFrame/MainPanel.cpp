// MainPanel.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MiniFrame.h"
#include "MainPanel.h"
#include "MainPanelDlg.h"


// CMainPanel

CMainPanel::CMainPanel()
{

}

CMainPanel::~CMainPanel()
{
}


BEGIN_MESSAGE_MAP(CMainPanel, CWnd)
END_MESSAGE_MAP()



// CMainPanel 메시지 처리기입니다.


void CMainPanel::Init()
{
	CMainPanelDlg *panel = new CMainPanelDlg();
	panel->Create(CMainPanelDlg::IDD, this);
	panel->ShowWindow(SW_SHOW);
}