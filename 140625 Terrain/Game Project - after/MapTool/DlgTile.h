#pragma once


// CDlgTile 대화 상자입니다.

class CDlgTile : public CDialogEx
{
public:
	CDlgTile(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgTile();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_TILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
