// MainPanelDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MiniFrame.h"
#include "MainPanelDlg.h"
#include "afxdialogex.h"
#include "TerrainPanel.h"
#include "TilePanel.h"


// CMainPanelDlg ��ȭ �����Դϴ�.
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


// CMainPanelDlg �޽��� ó�����Դϴ�.


void CMainPanelDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialogEx::OnOK();
}


void CMainPanelDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialogEx::OnCancel();
}


BOOL CMainPanelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog(); 

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
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
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CMainPanelDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
