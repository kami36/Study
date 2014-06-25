// DlgTerrain.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapTool.h"
#include "DlgTerrain.h"


// CDlgTerrain 대화 상자입니다.
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


// CDlgTerrain 메시지 처리기입니다.


void CDlgTerrain::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}


void CDlgTerrain::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnCancel();
}
