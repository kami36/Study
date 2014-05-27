// 2DRenderer.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "2DRenderer.h"
#include "math/Math.h"
#include "DrawTriangle.h"
#include <vector>
#include <algorithm>

using namespace std;


#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;								// ���� �ν��Ͻ��Դϴ�.
HWND g_hWnd;
TCHAR szTitle[MAX_LOADSTRING];					// ���� ǥ���� �ؽ�Ʈ�Դϴ�.
TCHAR szWindowClass[MAX_LOADSTRING];			// �⺻ â Ŭ���� �̸��Դϴ�.
vector<Vector3> g_vertices1;
vector<Vector3> g_vertices2;
vector<int> g_indices;
Matrix44 g_matWorld1;
Matrix44 g_matLocal1;
Matrix44 g_matWorld2;
Matrix44 g_matLocal2;
Matrix44 g_matWorld3;
Matrix44 g_matLocal3;


// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void					MainLoop(int elapse_time);
void					Render(HWND hWnd);
void					Paint(HWND hWnd, HDC hdc);


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
	LoadString(hInstance, IDC_MY2DRENDERER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// vertices1
	//       (-50,+50, +50)  ----------------- (+50, +50, +50)
	//       |                                                       |
	//       |                         +                           |
	//       |                                                       |
	//       (-50,+50, -50)  ----------------- (+50, +50, -50)
	//
	//       (-50,-50, +50)  ----------------- (+50, -50, +50)
	//       |                                                       |
	//       |                         +                           |
	//       |                                                       |
	//       (-50,-50, -50)  ----------------- (+50, -50, -50)

	const float w = 80.f;
	g_vertices1.reserve(128);
	g_vertices1.push_back( Vector3(-w,w,w) );
	g_vertices1.push_back( Vector3(w,w,w) );
	g_vertices1.push_back( Vector3(w,w,-w) );
	g_vertices1.push_back( Vector3(-w,w,-w) );

	g_vertices1.push_back( Vector3(-w,-w,w) );
	g_vertices1.push_back( Vector3(w,-w,w) );
	g_vertices1.push_back( Vector3(w,-w,-w) );
	g_vertices1.push_back( Vector3(-w,-w,-w) );


	g_indices.reserve(128);
	// top
	g_indices.push_back(0);
	g_indices.push_back(2);
	g_indices.push_back(3);
	g_indices.push_back(0);
	g_indices.push_back(1);
	g_indices.push_back(2);
	// front
	g_indices.push_back(3);
	g_indices.push_back(2);
	g_indices.push_back(7);
	g_indices.push_back(2);
	g_indices.push_back(6);
	g_indices.push_back(7);
	// back
	g_indices.push_back(1);
	g_indices.push_back(4);
	g_indices.push_back(5);
	g_indices.push_back(1);
	g_indices.push_back(0);
	g_indices.push_back(4);
	// left
	g_indices.push_back(3);
	g_indices.push_back(4);
	g_indices.push_back(0);
	g_indices.push_back(7);
	g_indices.push_back(4);
	g_indices.push_back(3);
	// right
	g_indices.push_back(2);
	g_indices.push_back(5);
	g_indices.push_back(6);
	g_indices.push_back(2);
	g_indices.push_back(1);
	g_indices.push_back(5);
	// bottom
	g_indices.push_back(4);
	g_indices.push_back(7);
	g_indices.push_back(6);
	g_indices.push_back(4);
	g_indices.push_back(6);
	g_indices.push_back(5);


	g_matWorld1.SetTranslate(Vector3(150,200,0));
	g_matWorld2.SetTranslate(Vector3(400,200,0));	
	g_matWorld3.SetTranslate(Vector3(600,200,0));	


	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2DRENDERER));

	// �⺻ �޽��� �����Դϴ�.
	int oldT = GetTickCount();
	while (1)
	{
		if (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			if(msg.message == WM_QUIT)
				break;
		}

		const int curT = GetTickCount();
		const int elapseT = curT - oldT;
		if (elapseT > 30)
		{
			oldT = curT;
			MainLoop(elapseT);	
		}
	}

	return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2DRENDERER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;//MAKEINTRESOURCE(IDC_MY2DRENDERER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   g_hWnd = hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �޴��� ���� ������ ���� �м��մϴ�.
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
	case WM_ERASEBKGND:
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Paint(hWnd, hdc);
		EndPaint(hWnd, &ps);
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



/**
 @brief 
 */
void	MainLoop(int elapse_time)
{
	// Render
	Render(g_hWnd);
	::InvalidateRect(g_hWnd, NULL, TRUE);
}


/**
 @brief 
 */
void	Render(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	Paint(hWnd, hdc);
	::ReleaseDC(hWnd, hdc);
}


void RenderVertices(HDC hdc, const vector<Vector3> &vertices, const Matrix44 &tm)
{
	for (unsigned int i=0; i < vertices.size(); ++i)
	{
		Vector3 p = vertices[ i] * tm;

		if (0 == i)
			MoveToEx(hdc, (int)p.x, (int)p.y, NULL);
		else
			LineTo(hdc, (int)p.x, (int)p.y);
	}
}


void RenderIndices(HDC hdc, const vector<Vector3> &vertices, const vector<int> &indices, const Matrix44 &tm)
{
	Vector3 camDir(0,0,1);

	for (unsigned int i=0; i < indices.size(); i+=3)
	{
		Vector3 p1 = vertices[ indices[ i]];
		Vector3 p2 = vertices[ indices[ i+1]];
		Vector3 p3 = vertices[ indices[ i+2]];

		p1 = p1 * tm;
		p2 = p2 * tm;
		p3 = p3 * tm;

		// culling

		Rasterizer::Color color(255,0,0,1);
		Rasterizer::DrawLine(hdc, color, p1.x, p1.y,color, p2.x, p2.y);
		Rasterizer::DrawLine(hdc, color, p1.x, p1.y,color, p3.x, p3.y);
		Rasterizer::DrawLine(hdc, color, p3.x, p3.y,color, p2.x, p2.y);
		//Rasterizer::DrawTriangle(hdc, color, p1.x, p1.y, color, p2.x, p2.y, color, p3.x, p3.y);
	}
}


/**
 @brief 
 */
void Paint(HWND hWnd, HDC hdc)
{
	RECT rc;
	GetClientRect(hWnd, &rc);
	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hbmMem = CreateCompatibleBitmap(hdc, rc.right-rc.left, rc.bottom-rc.top);
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmMem);
	HBRUSH hbrBkGnd = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
	FillRect(hdcMem, &rc, hbrBkGnd);
	DeleteObject(hbrBkGnd);

	Matrix44 mat1;
	mat1.SetRotationX(0.5f);
	Matrix44 mat2;
	mat2.SetRotationY(0.5f);

	RenderIndices(hdcMem, g_vertices1, g_indices, g_matLocal1 * mat1 * mat2 * g_matWorld1);

	BitBlt(hdc, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, hdcMem, 0, 0, SRCCOPY);
	SelectObject(hdcMem, hbmOld);
	DeleteObject(hbmMem);
	DeleteDC(hdcMem);
}

