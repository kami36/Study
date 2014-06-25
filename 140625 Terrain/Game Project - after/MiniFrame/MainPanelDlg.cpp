// MainPanelDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MiniFrame.h"
#include "MainPanelDlg.h"
#include "afxdialogex.h"
#include "TerrainPanel.h"
#include "TilePanel.h"


// CMainPanelDlg 대화 상자입니다.
CMainPanelDlg::CMainPanelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainPanelDlg::IDD, pParent)
{

}

CMainPanelDlg::~CMainPanelDlg()
{
}

void CMainPanelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}


BEGIN_MESSAGE_MAP(CMainPanelDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMainPanelDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMainPanelDlg::OnBnClickedCancel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMainPanelDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CMainPanelDlg 메시지 처리기입니다.


void CMainPanelDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}


void CMainPanelDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnCancel();
}


BOOL CMainPanelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog(); 

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_Tab.InsertItem(0, L"Terrain");
	m_Tab.InsertItem(1, L"Tile");
	m_Tab.InsertItem(2, L"Object");

	m_pTerrainPanel = new CTerrainPanel();
	m_pTerrainPanel->Create(CTerrainPanel::IDD, this);
	m_pTerrainPanel->MoveWindow(15, 40, 180, 500, 0);
	m_pTerrainPanel->ShowWindow(SW_SHOW);

	m_pTilePanel = new CTilePanel();
	m_pTilePanel->Create(CTilePanel::IDD, this);
	m_pTilePanel->MoveWindow(15, 40, 180, 500, 0);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CMainPanelDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	switch(m_Tab.GetCurSel())
	{
	case 0:
		m_pTerrainPanel->ShowWindow(SW_SHOW);
		m_pTilePanel->ShowWindow(SW_HIDE);
		break;
	case 1:
		m_pTilePanel->ShowWindow(SW_SHOW);
		m_pTerrainPanel->ShowWindow(SW_HIDE);
		break;
	case 2:
		m_pTilePanel->ShowWindow(SW_HIDE);
		m_pTerrainPanel->ShowWindow(SW_HIDE);
		break;
	}

	*pResult = 0;
}
