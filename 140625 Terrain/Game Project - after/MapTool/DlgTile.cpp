// DlgTile.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapTool.h"
#include "DlgTile.h"


// CDlgTile 대화 상자입니다.
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


// CDlgTile 메시지 처리기입니다.


void CDlgTile::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}


void CDlgTile::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnCancel();
}
