#pragma once


// CDlgTile ��ȭ �����Դϴ�.

class CDlgTile : public CDialogEx
{
public:
	CDlgTile(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgTile();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_TILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
