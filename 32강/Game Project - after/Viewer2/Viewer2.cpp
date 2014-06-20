
// Viewer2.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "Viewer2.h"
#include "Viewer2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CViewer2App
BEGIN_MESSAGE_MAP(CViewer2App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CViewer2App ����
CViewer2App::CViewer2App()
{
	// �ٽ� ���� ������ ����
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}


// ������ CViewer2App ��ü�Դϴ�.
CViewer2App theApp;


// CViewer2App �ʱ�ȭ
BOOL CViewer2App::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);

	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	CShellManager *pShellManager = new CShellManager;


	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));

	CViewer2Dlg *pdlg = new CViewer2Dlg();
	pdlg->Create(CViewer2Dlg::IDD);
	m_pMainWnd = pdlg;
	pdlg->ShowWindow(SW_SHOW);

	pdlg->MainLoop();

	//INT_PTR nResponse = dlg.DoModal();
	//if (nResponse == IDOK)
	//{
	//}
	//else if (nResponse == IDCANCEL)
	//{
	//}

	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	delete pdlg;
	graphic::ReleaseRenderer();
	memmonitor::Cleanup();

	return FALSE;
}

