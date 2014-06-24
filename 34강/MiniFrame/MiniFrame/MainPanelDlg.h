#pragma once
#include "afxcmn.h"

// CMainPanelDlg 대화 상자입니다.

class CTerrainPanel;
class CTilePanel;

class CMainPanelDlg : public CDialogEx
{
public:
	CMainPanelDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMainPanelDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_MAINPANEL };

	CTerrainPanel *m_pTerrainPanel;
	CTilePanel *m_pTilePanel;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	CTabCtrl m_Tab;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
