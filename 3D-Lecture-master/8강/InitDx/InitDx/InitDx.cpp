// InitDx.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "InitDx.h"
#include <d3d9.h>
#pragma comment( lib, "d3d9.lib" )

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;								// ���� �ν��Ͻ��Դϴ�.
TCHAR szTitle[MAX_LOADSTRING];					// ���� ǥ���� �ؽ�Ʈ�Դϴ�.
TCHAR szWindowClass[MAX_LOADSTRING];			// �⺻ â Ŭ���� �̸��Դϴ�.
HWND g_hWnd;
LPDIRECT3DDEVICE9	g_pDevice;

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: ���⿡ �ڵ带 �Է��մϴ�.
	MSG msg;
	HACCEL hAccelTable;

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_INITDX, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_INITDX));

	// �⺻ �޽��� �����Դϴ�.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
//  ����:
//
//    Windows 95���� �߰��� 'RegisterClassEx' �Լ����� ����
//    �ش� �ڵ尡 Win32 �ý��۰� ȣȯ�ǵ���
//    �Ϸ��� ��쿡�� �� �Լ��� ����մϴ�. �� �Լ��� ȣ���ؾ�
//    �ش� ���� ���α׷��� �����
//    '�ùٸ� ������' ���� �������� ������ �� �ֽ��ϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_INITDX));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_INITDX);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   g_hWnd = hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      0, 0, 800, 600, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   LPDIRECT3D9			d3d9;
   d3d9 = Direct3DCreate9( D3D_SDK_VERSION );

   //2. �ϵ���� ������ ������ �ͼ� �ڽ��� ���� ���μ��� Ÿ���� ������
   D3DCAPS9 caps;

   //Direct3D9 ��ü ���� ���� ī���� �ϵ���� ������ ������ �´�.
   d3d9->GetDeviceCaps(
	   D3DADAPTER_DEFAULT,			//�� ���÷��� �׷��� ī�� �׳� D3DADAPTER_DEFAULT
	   D3DDEVTYPE_HAL,				//����̽�Ÿ�� ���� �׳� D3DDEVTYPE_HAL
	   &caps						//����̽� ������ �޾ƿ� D3DCAPS9 ������
	   );

   //������� ó������� ������ �÷��� ��
   int vertexProcessing = 0;

   //���� ��ġ�� ���� ���� �ϵ���� ����� �����Ѱ�
   if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
	   vertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
   else
	   vertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;



   //3. D3DPRESENT_PARAMETERS ����ü ������ ����
   //���� �̷��� Device �� ����ٴٶ�� ����

   D3DPRESENT_PARAMETERS d3dpp;		
   d3dpp.AutoDepthStencilFormat		= D3DFMT_D24S8;				//���� ���ۿ� ���׽� ���� ũ�� ���� 24bit ���ٽ� ���� 8 ��Ʈ
   d3dpp.BackBufferCount				= 1;						//����� ���� �׳� 1��
   d3dpp.BackBufferFormat				= D3DFMT_A8R8G8B8;			//����� ���� ���� ����8��Ʈ,����8��Ʈ,�׸�8��Ʈ,���8��Ʈ
   d3dpp.BackBufferHeight				= 800;				//����� �ȼ� ũ��
   d3dpp.BackBufferWidth				= 600;				//����� �ȼ� ũ��
   d3dpp.EnableAutoDepthStencil		= true;						//�ڵ� ���̹��� ��� ���� ( �׳� true )
   d3dpp.Flags							= 0;						//�߱� �÷��� ( �ϴ� 0 )
   d3dpp.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;	//ȭ�� �ֻ��� ( �׳� D3DPRESENT_RATE_DEFAULT ����� �ֻ����� ���Ͻ� )
   d3dpp.hDeviceWindow					= g_hWnd;					//Device �� ��µ� ������ �ڵ�
   d3dpp.MultiSampleQuality			= 0;						//��Ƽ ���ø� ��
   d3dpp.MultiSampleType				= D3DMULTISAMPLE_NONE;		//��Ƽ ���ø� Ÿ�� 
   d3dpp.PresentationInterval			= D3DPRESENT_INTERVAL_ONE;	//ȭ�� ���� ���� ( �׳� D3DPRESENT_INTERVAL_ONE ����� �ֻ����� ���Ͻ� )
   d3dpp.SwapEffect					= D3DSWAPEFFECT_DISCARD;	//ȭ�� ���� ü�� ���
   d3dpp.Windowed						= true;						//������ ����? ( �̰� false �� Ǯ��ũ�� �ȴ�! )



   //4. Device ����
   if( FAILED( d3d9->CreateDevice(
	   D3DADAPTER_DEFAULT,					//�� ���÷��� �׷��� ī�� �׳� D3DADAPTER_DEFAULT
	   D3DDEVTYPE_HAL,						//����̽�Ÿ�� ���� �׳� D3DDEVTYPE_HAL
	   g_hWnd,								//����̽��� ����� ������ �ڵ�
	   vertexProcessing,					//���� ó�� ��Ŀ� ���� �÷���
	   &d3dpp,								//�տ��� ������ D3DPRESENT_PARAMETERS ����ü ������
	   &g_pDevice							//���� ����̽� ����������
	   ) ) )
   {
	   //����̽� ���� ����

	   d3d9->Release(); // Deivce �� ����� ���� ������ Direct3D9 ��ü�� ����
	   d3d9 = NULL;

	   MessageBoxA( g_hWnd, "CreateDevice() - FAILED", "FAILED", MB_OK );
	   return E_FAIL;
   }


   //����̽� ���� ����
   d3d9->Release(); // Deivce �� ��������� �� ���̻� �ʿ���� ( �������! )
   d3d9 = NULL;


   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND	- ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT	- �� â�� �׸��ϴ�.
//  WM_DESTROY	- ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �޴� ������ ���� �м��մϴ�.
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		{
			//ȭ�� û��
			if( SUCCEEDED( g_pDevice->Clear( 
				0,			//û���� ������ D3DRECT �迭 ����		( ��ü Ŭ���� 0 )
				NULL,		//û���� ������ D3DRECT �迭 ������		( ��ü Ŭ���� NULL )
				D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,	//û�ҵ� ���� �÷��� ( D3DCLEAR_TARGET �÷�����, D3DCLEAR_ZBUFFER ���̹���, D3DCLEAR_STENCIL ���ٽǹ���
				0xffffff00,			//�÷����۸� û���ϰ� ä���� ����( 0xAARRGGBB )
				1.0f,				//���̹��۸� û���Ұ� ( 0 ~ 1 0 �� ī�޶󿡼� ���ϰ���� 1 �� ī�޶󿡼� ���� �� )
				0					//���ٽ� ���۸� ä�ﰪ
				) ) )
			{
				//ȭ�� û�Ұ� ���������� �̷�� ���ٸ�... ������ ����
				g_pDevice->BeginScene();

				//���⼭���� ������ ����� ����ȴ�..




				//������ ��
				g_pDevice->EndScene();


				//�������� �������� �������� ���� ȭ������ ����
				g_pDevice->Present( NULL, NULL, NULL, NULL );
			}

		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
