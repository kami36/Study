
// MapToolDlg.h : 헤더 파일
//

#pragma once


class CDlgTerrain;
class CDlgTile;

// CMapToolDlg 대화 상자
class CMapToolDlg : public CDialogEx
{
// 생성입니다.
public:
	CMapToolDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MAPTOOL_DIALOG };

	CDlgTerrain *m_pTerrainPanel;
	CDlgTile *m_pTilePanel;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CTabCtrl m_Tab;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
