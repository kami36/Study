#pragma once


// CDlgTerrain ��ȭ �����Դϴ�.

class CDlgTerrain : public CDialogEx
{
public:
	CDlgTerrain(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgTerrain();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_TERRAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
