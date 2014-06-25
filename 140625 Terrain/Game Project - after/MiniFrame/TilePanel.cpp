// TilePanel.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MiniFrame.h"
#include "TilePanel.h"


// CTilePanel
CTilePanel::CTilePanel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTilePanel::IDD, pParent)
{

}

CTilePanel::~CTilePanel()
{
}

void CTilePanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTilePanel, CWnd)
END_MESSAGE_MAP()



// CTilePanel 메시지 처리기입니다.


