#pragma once


// CTilePanel

class CTilePanel : public CDialogEx
{
public:
	CTilePanel(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTilePanel();

	enum { IDD = IDD_DIALOG_TILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};


