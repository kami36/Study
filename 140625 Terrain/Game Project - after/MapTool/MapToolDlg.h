
// MapToolDlg.h : ��� ����
//

#pragma once


class CDlgTerrain;
class CDlgTile;

// CMapToolDlg ��ȭ ����
class CMapToolDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMapToolDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MAPTOOL_DIALOG };

	CDlgTerrain *m_pTerrainPanel;
	CDlgTile *m_pTilePanel;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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