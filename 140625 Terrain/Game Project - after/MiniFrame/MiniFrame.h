
// MiniFrame.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMiniFrameApp:
// �� Ŭ������ ������ ���ؼ��� MiniFrame.cpp�� �����Ͻʽÿ�.
//

class CMiniFrameApp : public CWinApp
{
public:
	CMiniFrameApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMiniFrameApp theApp;