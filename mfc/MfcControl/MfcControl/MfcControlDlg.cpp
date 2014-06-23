
// MfcControlDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MfcControl.h"
#include "MfcControlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMfcControlDlg 대화 상자




CMfcControlDlg::CMfcControlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMfcControlDlg::IDD, pParent)
	, m_Check(FALSE)
	, m_Static(_T(""))
	, m_Edit(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMfcControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, m_Check);
	DDX_Text(pDX, IDC_STATIC1, m_Static);
	DDX_Text(pDX, IDC_EDIT1, m_Edit);
	DDX_Control(pDX, IDC_COMBO1, m_Control);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_STATIC2, m_Picture);
	DDX_Control(pDX, IDC_SLIDER1, m_Slider);
}

BEGIN_MESSAGE_MAP(CMfcControlDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMfcControlDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK1, &CMfcControlDlg::OnBnClickedCheck1)
	ON_EN_CHANGE(IDC_EDIT1, &CMfcControlDlg::OnEnChangeEdit1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMfcControlDlg::OnCbnSelchangeCombo1)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMfcControlDlg::OnSelchangeList1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CMfcControlDlg::OnNMCustomdrawSlider1)
END_MESSAGE_MAP()


// CMfcControlDlg 메시지 처리기

BOOL CMfcControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_Check = TRUE;
	m_Static = L"ASDF";
	m_Control.InsertString(0, L"TEST1");
	m_Control.InsertString(1, L"TEST2");
	m_Control.InsertString(2, L"TEST3");
	m_Control.InsertString(3, L"TEST4");
	m_Control.InsertString(4, L"TEST5");
	m_Control.SetCurSel(0);

	m_ListBox.InsertString(0, L"001");
	m_ListBox.InsertString(1, L"002");
	m_ListBox.InsertString(2, L"003");
	m_ListBox.InsertString(3, L"004");
	m_ListBox.InsertString(4, L"005");
	m_ListBox.SetCurSel(1);

	CRect wr;
	m_Picture.GetWindowRect(wr);

	m_Slider.SetRange(200, 500);

	UpdateData(FALSE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMfcControlDlg::OnPaint()
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
HCURSOR CMfcControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMfcControlDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}



void CMfcControlDlg::OnBnClickedCheck1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Check = TRUE;
	m_Edit = "aaaa";
	UpdateData(FALSE);
}


void CMfcControlDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	OutputDebugString(m_Edit);
	OutputDebugString(L"\n");
}


void CMfcControlDlg::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int sel = m_Control.GetCurSel();
	CString str;
	m_Control.GetLBText(sel, str);
	OutputDebugString(str + '\n');
}


void CMfcControlDlg::OnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int sel = m_ListBox.GetCurSel();
	CString str;
	m_ListBox.GetText(sel, str);
	OutputDebugString(str + '\n');
}


void CMfcControlDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int pos = m_Slider.GetPos();
	CString str;
	str.Format(L"%d", pos);
	OutputDebugString(str + '\n');

	*pResult = 0;
}
