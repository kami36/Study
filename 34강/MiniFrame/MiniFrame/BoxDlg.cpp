// BoxDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MiniFrame.h"
#include "BoxDlg.h"
#include "afxdialogex.h"


// CBoxDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CBoxDlg, CDialogEx)

CBoxDlg::CBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBoxDlg::IDD, pParent)
{

}

CBoxDlg::~CBoxDlg()
{
}

void CBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBoxDlg, CDialogEx)
END_MESSAGE_MAP()


// CBoxDlg �޽��� ó�����Դϴ�.
