
// 140619View.h : CMy140619View Ŭ������ �������̽�
//

#pragma once


class CMy140619View : public CView
{
protected: // serialization������ ��������ϴ�.
	CMy140619View();
	DECLARE_DYNCREATE(CMy140619View)

// Ư���Դϴ�.
public:
	CMy140619Doc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMy140619View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 140619View.cpp�� ����� ����
inline CMy140619Doc* CMy140619View::GetDocument() const
   { return reinterpret_cast<CMy140619Doc*>(m_pDocument); }
#endif

