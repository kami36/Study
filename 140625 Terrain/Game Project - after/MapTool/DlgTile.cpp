// DlgTile.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MapTool.h"
#include "DlgTile.h"


// CDlgTile ��ȭ �����Դϴ�.
CDlgTile::CDlgTile(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTile::IDD, pParent)
{

}

CDlgTile::~CDlgTile()
{
}

void CDlgTile::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTile, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgTile::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgTile::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgTile �޽��� ó�����Դϴ�.


void CDlgTile::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialogEx::OnOK();
}


void CDlgTile::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialogEx::OnCancel();
}
