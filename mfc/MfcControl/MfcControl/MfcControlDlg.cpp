
// MfcControlDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MfcControl.h"
#include "MfcControlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMfcControlDlg ��ȭ ����




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


// CMfcControlDlg �޽��� ó����

BOOL CMfcControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
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

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMfcControlDlg::OnPaint()
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
HCURSOR CMfcControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMfcControlDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}



void CMfcControlDlg::OnBnClickedCheck1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_Check = TRUE;
	m_Edit = "aaaa";
	UpdateData(FALSE);
}


void CMfcControlDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData();
	OutputDebugString(m_Edit);
	OutputDebugString(L"\n");
}


void CMfcControlDlg::OnCbnSelchangeCombo1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int sel = m_Control.GetCurSel();
	CString str;
	m_Control.GetLBText(sel, str);
	OutputDebugString(str + '\n');
}


void CMfcControlDlg::OnSelchangeList1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int sel = m_ListBox.GetCurSel();
	CString str;
	m_ListBox.GetText(sel, str);
	OutputDebugString(str + '\n');
}


void CMfcControlDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int pos = m_Slider.GetPos();
	CString str;
	str.Format(L"%d", pos);
	OutputDebugString(str + '\n');

	*pResult = 0;
}
