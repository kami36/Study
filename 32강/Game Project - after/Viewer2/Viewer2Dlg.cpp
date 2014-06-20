
// Viewer2Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Viewer2.h"
#include "Viewer2Dlg.h"
#include "afxdialogex.h"
#include "ModelView.h"
#include "../wxMemMonitorLib/wxMemMonitor.h"
#include "mmsystem.h"

#pragma comment( lib, "winmm.lib" )

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CViewer2Dlg::CViewer2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CViewer2Dlg::IDD, pParent)
,	m_pView(NULL)
,	m_loop(true)
,	m_dxInit(false)
, m_WireFrame(FALSE)
{
//	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CViewer2Dlg::~CViewer2Dlg()
{
}

void CViewer2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILE_LIST, m_FileList);
	DDX_Check(pDX, IDC_CHECK_WIREFRAME, m_WireFrame);
}

BEGIN_MESSAGE_MAP(CViewer2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_FILE_LIST, OnItemchangedFileList)
	ON_BN_CLICKED(IDOK, &CViewer2Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CViewer2Dlg::OnBnClickedCancel)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_CHECK_WIREFRAME, &CViewer2Dlg::OnBnClickedCheckWireframe)
END_MESSAGE_MAP()


// CViewer2Dlg �޽��� ó����

BOOL CViewer2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);		// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.


	DragAcceptFiles(TRUE);

	MoveWindow(CRect(0,0,1024,768));

	m_pView = new CModelView();
	m_pView->Create(NULL, _T("CView"), WS_CHILDWINDOW, 
		CRect(0,40, 800, 640), this, 0);

	graphic::cRenderer::Get()->CreateDirectX(
		m_pView->GetSafeHwnd(), 800, 600);

	m_dxInit = true;
	m_pView->Init();
	m_pView->ShowWindow(SW_SHOW);

	m_FileList.SetExtendedStyle( m_FileList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	m_FileList.InsertColumn(0, L"path");
	m_FileList.SetColumnWidth(0, 300);
	m_FileList.InsertItem(0, L"Test1");
	m_FileList.InsertItem(1, L"Test2");
	m_FileList.InsertItem(2, L"Test3");
	m_FileList.InsertItem(3, L"Test4");

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CViewer2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CViewer2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CViewer2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CViewer2Dlg::OnBnClickedOk()
{
	m_loop = false;
	CDialogEx::OnOK();
}


void CViewer2Dlg::OnBnClickedCancel()
{
	m_loop = false;
	CDialogEx::OnCancel();
}


void CViewer2Dlg::MainLoop()
{
	while (m_loop)
	{
		MSG msg;
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&msg, NULL, 0, 0)) 
			{
				break;
			}
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		const int curT = timeGetTime();
		static int oldT = curT;
		const int elapseT = curT - oldT;
		const float t = elapseT * 0.001f;
		oldT = curT;

		if (m_dxInit && m_pView)
		{
			m_pView->Update(t);
			m_pView->Render();
		}

		Sleep(0);
	}
}


void CViewer2Dlg::OnItemchangedFileList(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if ((pNMListView->uChanged & LVIF_STATE) 
		&& (pNMListView->uNewState & LVNI_SELECTED))
	{
		CString str = m_FileList.GetItemText(pNMListView->iItem, 0);
		
		string filePath = common::wstr2str( (LPCTSTR)str );
		m_pView->LoadModel(filePath);
	}
}


void CViewer2Dlg::OnDropFiles(HDROP hDropInfo)
{
	HDROP hdrop = hDropInfo;
	char filePath[ MAX_PATH];
	const UINT size = DragQueryFileA(hdrop, 0, filePath, MAX_PATH);
	if (size == 0) 
		return;// handle error...

	m_pView->LoadModel(filePath);

	wstring wstr = common::str2wstr(filePath);
	CString str = wstr.c_str();
	m_FileList.InsertItem(m_FileList.GetItemCount(), str);

	CDialogEx::OnDropFiles(hDropInfo);
}


void CViewer2Dlg::OnBnClickedCheckWireframe()
{
	UpdateData();
	graphic::GetDevice()->SetRenderState(D3DRS_CULLMODE, !m_WireFrame);
	graphic::GetDevice()->SetRenderState(D3DRS_FILLMODE, !m_WireFrame? D3DFILL_SOLID : D3DFILL_WIREFRAME);
}


