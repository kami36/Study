#pragma once


// CTerrainPanel

class CTerrainPanel : public CDialogEx
{
public:
	CTerrainPanel(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTerrainPanel();

	enum { IDD = IDD_DIALOG_TERRAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};


