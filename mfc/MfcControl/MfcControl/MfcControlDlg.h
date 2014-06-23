
// MfcControlDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CMfcControlDlg 대화 상자
class CMfcControlDlg : public CDialogEx
{
// 생성입니다.
public:
	CMfcControlDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MFCCONTROL_DIALOG };

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
	BOOL m_Check;
	afx_msg void OnBnClickedCheck1();
	CString m_Static;
	afx_msg void OnEnChangeEdit1();
	CString m_Edit;
	CComboBox m_Control;
	afx_msg void OnCbnSelchangeCombo1();
	CListBox m_ListBox;
	afx_msg void OnSelchangeList1();
	CStatic m_Picture;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_Slider;
};
