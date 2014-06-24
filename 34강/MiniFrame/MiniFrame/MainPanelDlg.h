#pragma once
#include "afxcmn.h"

// CMainPanelDlg ��ȭ �����Դϴ�.

class CTerrainPanel;
class CTilePanel;

class CMainPanelDlg : public CDialogEx
{
public:
	CMainPanelDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMainPanelDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_MAINPANEL };

	CTerrainPanel *m_pTerrainPanel;
	CTilePanel *m_pTilePanel;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	CTabCtrl m_Tab;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
