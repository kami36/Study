
// MapToolDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MapTool.h"
#include "MapToolDlg.h"
#include "afxdialogex.h"
#include "DlgTerrain.h"
#include "DlgTile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMapToolDlg 대화 상자




CMapToolDlg::CMapToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMapToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMapToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}

BEGIN_MESSAGE_MAP(CMapToolDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMapToolDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMapToolDlg::OnBnClickedCancel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMapToolDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CMapToolDlg 메시지 처리기

BOOL CMapToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_Tab.InsertItem(0, L"Terrain");
	m_Tab.InsertItem(1, L"Tile");
	m_Tab.InsertItem(2, L"Object");

	m_pTerrainPanel = new CDlgTerrain();
	m_pTerrainPanel->Create(CDlgTerrain::IDD, this);
	m_pTerrainPanel->MoveWindow(15, 35, 177, 484, 0);
	m_pTerrainPanel->ShowWindow(SW_SHOW);

	m_pTilePanel = new CDlgTile();
	m_pTilePanel->Create(CDlgTile::IDD, this);
	m_pTilePanel->MoveWindow(15, 35, 177, 484, 0);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMapToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMapToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMapToolDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}


void CMapToolDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void CMapToolDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
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
