// DlgTerrain.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MapTool.h"
#include "DlgTerrain.h"


// CDlgTerrain ��ȭ �����Դϴ�.
CDlgTerrain::CDlgTerrain(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTerrain::IDD, pParent)
{

}

CDlgTerrain::~CDlgTerrain()
{
}

void CDlgTerrain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTerrain, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgTerrain::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgTerrain::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgTerrain �޽��� ó�����Դϴ�.


void CDlgTerrain::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialogEx::OnOK();
}


void CDlgTerrain::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialogEx::OnCancel();
}
