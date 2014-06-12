﻿#include "stdafx.h"
#include "SoftwareRendererLighting.h"
#include "math/Math.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "DrawTriangle.h"


using namespace std;

#define MAX_LOADSTRING 100

HINSTANCE hInst;
HWND g_hWnd;
TCHAR szTitle[MAX_LOADSTRING];
TCHAR szWindowClass[MAX_LOADSTRING];
vector<Vector3> g_axises;
vector<Vector3> g_vertices;
vector<Vector3> g_normals;
vector<int> g_indices;
Matrix44 g_matWorld;
Matrix44 g_matLocal;
Matrix44 g_matProjection;
Matrix44 g_matView;
Matrix44 g_matViewPort;
bool g_WireFrame = false;
Vector3 g_cameraPos(0,1000,-1000);
Vector3 g_cameraLookat(0,0,0);

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void					MainLoop(int elapse_time);
void					Render(HWND hWnd);
void					Paint(HWND hWnd, HDC hdc);
void					ComputeNormals(const vector<Vector3> &vertices, const vector<int> &indices, vector<Vector3> &normals);
bool					ReadModelFile( const string &fileName );

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR  lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SOFTWARERENDERERLIGHTING, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	//                   Y    Z
	//                   |   /
	//                   | /
	//    -----------------------> X
	const float axisLineLength = 300.f;
	g_axises.reserve(8);
	g_axises.push_back( Vector3(0,0,0) );
	g_axises.push_back( Vector3(axisLineLength,0,0) ); // x-axis
	g_axises.push_back( Vector3(0,0,0) );
	g_axises.push_back( Vector3(0,axisLineLength,0) ); // y-axis
	g_axises.push_back( Vector3(0,0,0) );
	g_axises.push_back( Vector3(0,0,axisLineLength) ); // z-axis


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
/*
	const float w = 30.f;
	vector<Vector3> vertices;
	vertices.reserve(8);
	vertices.push_back( Vector3(-w,w,w) );
	vertices.push_back( Vector3(w,w,w) );
	vertices.push_back( Vector3(w,w,-w) );
	vertices.push_back( Vector3(-w,w,-w) );
	vertices.push_back( Vector3(-w,-w,w) );
	vertices.push_back( Vector3(w,-w,w) );
	vertices.push_back( Vector3(w,-w,-w) );
	vertices.push_back( Vector3(-w,-w,-w) );

	g_vertices.reserve(64);
	// top
	g_vertices.push_back( vertices[ 0] );
	g_vertices.push_back( vertices[ 1] );
	g_vertices.push_back( vertices[ 2] );
	g_vertices.push_back( vertices[ 3] );

	// front
	g_vertices.push_back( vertices[ 3] );
	g_vertices.push_back( vertices[ 2] );
	g_vertices.push_back( vertices[ 6] );
	g_vertices.push_back( vertices[ 7] );

	//  back
	g_vertices.push_back( vertices[ 0] );
	g_vertices.push_back( vertices[ 4] );
	g_vertices.push_back( vertices[ 5] );
	g_vertices.push_back( vertices[ 1] );

	// left
	g_vertices.push_back( vertices[ 0] );
	g_vertices.push_back( vertices[ 3] );
	g_vertices.push_back( vertices[ 7] );
	g_vertices.push_back( vertices[ 4] );

	// right
	g_vertices.push_back( vertices[ 2] );
	g_vertices.push_back( vertices[ 1] );
	g_vertices.push_back( vertices[ 5] );
	g_vertices.push_back( vertices[ 6] );

	// bottom
	g_vertices.push_back( vertices[ 6] );
	g_vertices.push_back( vertices[ 5] );
	g_vertices.push_back( vertices[ 4] );
	g_vertices.push_back( vertices[ 7] );

	g_indices.reserve(128);
	for (int i=0; i < 6; ++i)
string strArray[5]; // ���ڿ� ���� ����.
int count = 0; 	// �ִ� 5���� �ܾ �Է¹޴´�.  end�� ������ �����Ѵ�.
while (count < 5)
	{
		g_indices.push_back(0 + (i*4));
		g_indices.push_back(2 + (i*4));
		g_indices.push_back(3 + (i*4));
		g_indices.push_back(0 + (i*4));
		g_indices.push_back(1 + (i*4));
		g_indices.push_back(2 + (i*4));
	}
/**/

	ReadModelFile("plane.dat");

	g_matWorld.SetIdentity();
	g_matWorld.Translate(Vector3(0,0,0));
	g_matLocal.SetIdentity();

	g_matView.SetIdentity();
	Vector3 dir = g_cameraLookat - g_cameraPos;
	dir.Normalize();
	g_matView.SetView(g_cameraPos, dir, Vector3(0,1,0));
	g_matProjection.SetProjection( MATH_PI / 4.f, 1.0f, 1.0f, 100.0f );

	const float width = 800.f;
	const float height = 600.f;
	g_matViewPort.SetIdentity();
	g_matViewPort._11 = width/2;
	g_matViewPort._22 = -height/2;
	g_matViewPort._33 = 0;
	g_matViewPort._41 = width/2;
	g_matViewPort._42 = height/2;
	g_matViewPort._43 = 0;


	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	MSG msg;
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SOFTWARERENDERERLIGHTING));
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
		if (elapseT > 15)
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SOFTWARERENDERERLIGHTING));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	
	return RegisterClassEx(&wcex);
}
	
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	
	hInst = hInstance;
	
	g_hWnd = hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	    0, 0, 800, 620, NULL, NULL, hInstance, NULL);
	
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
		switch (wmId)
		{
		case IDM_ABOUT:
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Paint(hWnd, hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_ERASEBKGND:
		return 1;
	
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_TAB:
			g_WireFrame = !g_WireFrame;
			break;
	
		case VK_UP:
		case VK_DOWN:
			{
				Matrix44 mat;
				mat.SetRotationX((wParam==VK_UP)? 0.1f : -0.1f);
				g_matLocal *= mat;
			}
			break;
	
		case VK_LEFT:
		case VK_RIGHT:
			{
				Matrix44 mat;
				mat.SetRotationY((wParam==VK_LEFT)? 0.1f : -0.1f);
				g_matLocal *= mat;
	 			}
			break;
	
		case 'W':
		case 'S':
			{
				Vector3 dir = g_cameraLookat - g_cameraPos;
				dir.Normalize();
				const bool isForward = 'W' == wParam;
				g_cameraPos += dir * (isForward? 10.f : -10.f);
				g_cameraLookat += dir * (isForward? 10.f : -10.f);
	
				Vector3 dir2 = g_cameraLookat - g_cameraPos;
				dir2.Normalize();
				g_matView.SetView(g_cameraPos, dir2, Vector3(0,1,0));
			}
			break;

		case 'A':
		case 'D':
			{
				Vector3 dir = g_cameraLookat - g_cameraPos;
				dir.Normalize();
				Vector3 left = Vector3(0,1,0).CrossProduct(dir);
				left.Normalize();
				const bool isLeft = 'A' == wParam;
				g_cameraPos += left * (isLeft? 10.f : -10.f);
				g_cameraLookat += left * (isLeft? 10.f : -10.f);
	
				Vector3 dir2 = g_cameraLookat - g_cameraPos;
				dir2.Normalize();
				g_matView.SetView(g_cameraPos, dir2, Vector3(0,1,0));
			}
			break;
	
		case 'E':
		case 'C':
			{
				Matrix44 mat;
				mat.SetRotationY((wParam=='E')? 0.1f : -0.1f);
				g_cameraPos = g_cameraPos * mat;
	
				Vector3 dir2 = g_cameraLookat - g_cameraPos;
				dir2.Normalize();
				g_matView.SetView(g_cameraPos, dir2, Vector3(0,1,0));
			}
			break;
	
		case VK_ESCAPE:
			DestroyWindow(hWnd);
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
	
	
	
/**
	@brief 
	*/
void	MainLoop(int elapse_time)
{
	// Render
	Render(g_hWnd);
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
	
	
bool ReadModelFile( const string &fileName )
{
	using namespace std;
	ifstream fin(fileName);
	if (!fin.is_open())
		return false;
	
	string vtx, vtx_eq;
	int numVertices;
	fin >> vtx >> vtx_eq >> numVertices;
	
	if (numVertices <= 0)
		return  false;
	
	g_vertices.resize(numVertices);
	
	float num1, num2, num3;
	for (int i = 0; i < numVertices; i++)
	{
		fin >> num1 >> num2 >> num3;
		g_vertices[i] = Vector3(num1, num2, num3);
	}
	
	string idx, idx_eq;
	int numIndices;
	fin >> idx >> idx_eq >> numIndices;
	
	if (numIndices <= 0)
		return false;
	
	g_indices.resize(numIndices*3);
	
	int num4, num5, num6;
	for (int i = 0; i < numIndices*3; i+=3)
	{
		fin >> num4 >> num5 >> num6;
		g_indices[ i] = num4;
		g_indices[ i+1] = num5;
		g_indices[ i+2] = num6;	
	}
	
	ComputeNormals(g_vertices, g_indices, g_normals);
	
	return true;
}
	
	
	
/**
	@brief 
	@date 2014-04-07
*/
void ComputeNormals(const vector<Vector3> &vertices, const vector<int> &indices, vector<Vector3> &normals)
{
	g_normals.resize(vertices.size());
	
	for (unsigned int i=0; i < indices.size(); i+=3)
	{
		Vector3 p1 = vertices[ indices[ i]];
		Vector3 p2 = vertices[ indices[ i+1]];
		Vector3 p3 = vertices[ indices[ i+2]];
	
		Vector3 v1 = p2 - p1;
		Vector3 v2 = p3 - p1;
		v1.Normalize();
		v2.Normalize();
		Vector3 n = v1.CrossProduct(v2);
		n.Normalize();
	
		if (Vector3(0,0,0) == g_normals[ indices[ i]])
		{
				g_normals[ indices[ i]] = n;
		}
		else
		{
				g_normals[ indices[ i]] += n;
				g_normals[ indices[ i]] /= 2.f;
		}
	
		if (Vector3(0,0,0) == g_normals[ indices[ i+1]])
		{
			g_normals[ indices[ i+1]] = n;
		}
		else
		{
			g_normals[ indices[ i+1]] += n;
			g_normals[ indices[ i+1]] /= 2.f;
		}
	
		if (Vector3(0,0,0) == g_normals[ indices[ i+2]])
		{
			g_normals[ indices[ i+2]] = n;
		}
		else
 		{
			g_normals[ indices[ i+2]] += n;
			g_normals[ indices[ i+2]] /= 2.f;
 		}
	
		//normals[ i] = n;
		//normals[ i+1] = n;
		//normals[ i+2] = n;
	}
}
	
	
/**
	@brief 
	@date 2014-04-07
*/
void GroudShading(vector<Vector3> &vertices, const vector<int> &indices, vector<Vector3> &normals)
{
	
	for (unsigned int i=0; i < indices.size(); i+=3)
	{
		//Vector3 p1 = vertices[ indices[ i]];
		//Vector3 p2 = vertices[ indices[ i+1]];
		//Vector3 p3 = vertices[ indices[ i+2]];
	
		//Vector3 v1 = p2 - p1;
		//Vector3 v2 = p3 - p1;
		//v1.Normalize();
		//v2.Normalize();
		//Vector3 n = v1.CrossProduct(v2);
		//n.Normalize();
	
		//normals[ indices[ i]] = n;
		//normals[ indices[ i+1]] = n;
		//normals[ indices[ i+2]] = n;
	 	}
	
	
	
}
	
	
void RenderVertices(HDC hdc, const vector<Vector3> &vertices, const Matrix44 &tm)
{
	for (unsigned int i=0; i < vertices.size(); ++i)
	{
		Vector3 p = vertices[ i];
		p = p * tm;
	
		if (0 == i)
			MoveToEx(hdc, (int)p.x, (int)p.y, NULL);
		else
			LineTo(hdc, (int)p.x, (int)p.y);
	}
}
	
void RenderIndices(HDC hdc, const vector<Vector3> &vertices, const vector<Vector3> &normals, 
	const vector<int> &indices, const Matrix44 &tm, const Matrix44 &vpv)
{
	Vector3 lightDir(0,-1,0);
	
	Vector3 camDir = g_cameraLookat - g_cameraPos;
	camDir.Normalize();
	
	Matrix44 dirTm = tm;	
	dirTm._41 = dirTm._42 = dirTm._43 = 0.f;
	
	Vector3 H = -camDir - lightDir;
	H.Normalize();
	
	for (unsigned int i=0; i < indices.size(); i+=3)
	{
		Vector3 p1 = vertices[ indices[ i]];
		Vector3 p2 = vertices[ indices[ i+1]];
		Vector3 p3 = vertices[ indices[ i+2]];
	
		p1 = p1 * tm;
		p2 = p2 * tm;
		p3 = p3 * tm;
	
		// culling
		Vector3 n1 = normals[  indices[ i]] * dirTm;
		Vector3 n2 = normals[  indices[ i+1]] * dirTm;
		Vector3 n3 = normals[  indices[ i+2]] * dirTm;
	
		const float dot1 = n1.DotProduct(camDir);
		const float dot2 = n2.DotProduct(camDir);
		const float dot3 = n3.DotProduct(camDir);
		if ((dot1 > 0.f) && (dot2 > 0.f) && (dot3 > 0.f))
			continue;
	
		p1 = p1 * vpv;
		p2 = p2 * vpv;
		p3 = p3 * vpv;
	
		Rasterizer::Color c0(0,255,0,1);
		Rasterizer::Color c1 = c0 * max(0, n1.DotProduct(-lightDir));
		Rasterizer::Color c2 = c0 * max(0, n2.DotProduct(-lightDir));
		Rasterizer::Color c3 = c0 * max(0, n3.DotProduct(-lightDir));
	
		const float s1 = max(0, n1.DotProduct(H));
		const float s2 = max(0, n2.DotProduct(H));
		const float s3 = max(0, n3.DotProduct(H));
		c1 = c1 + c0 * pow(s1, 32);
		c2 = c2 + c0 * pow(s2, 32);
		c3 = c3 + c0 * pow(s3, 32);
	
		c1 = c1 + Rasterizer::Color(0,10,0,1);
		c2 = c2 + Rasterizer::Color(0,10,0,1);
		c3 = c3 + Rasterizer::Color(0,0,0,1);
	
		Rasterizer::DrawTriangle(hdc, 
			c1, p1.x, p1.y, n1, 
			c2, p2.x, p2.y, n2, 
			c3, p3.x, p3.y, n3);
	}
}
	
	
void RenderWire(HDC hdc, const vector<Vector3> &vertices, const vector<Vector3> &normals, const vector<int> &indices, 
	const Matrix44 &tm, const Matrix44 &vpv)
{
	Vector3 camDir = g_cameraLookat - g_cameraPos;
	camDir.Normalize();
	Matrix44 dirTm = tm;	
	dirTm._41 = dirTm._42 = dirTm._43 = 0.f;
	
	for (unsigned int i=0; i < indices.size(); i+=3)
	{
		Vector3 p1 = vertices[ indices[ i]];
		Vector3 p2 = vertices[ indices[ i+1]];
		Vector3 p3 = vertices[ indices[ i+2]];
	
		p1 = p1 * tm;
		p2 = p2 * tm;
		p3 = p3 * tm;
	
		// culling
		Vector3 n1 = normals[  indices[ i]] * dirTm;
		Vector3 n2 = normals[  indices[ i+1]] * dirTm;
		Vector3 n3 = normals[  indices[ i+2]] * dirTm;
	
		const float dot1 = n1.DotProduct(camDir);
		const float dot2 = n2.DotProduct(camDir);
		const float dot3 = n3.DotProduct(camDir);
		if ((dot1 > 0.f) && (dot2 > 0.f) && (dot3 > 0.f))
			continue;
	
		p1 = p1 * vpv;
		p2 = p2 * vpv;
		p3 = p3 * vpv;
	
		Rasterizer::Color color(0,0,0,1);
		Rasterizer::DrawLine(hdc, color, p1.x, p1.y, color, p2.x, p2.y);
		Rasterizer::DrawLine(hdc, color, p1.x, p1.y, color, p3.x, p3.y);
		Rasterizer::DrawLine(hdc, color, p3.x, p3.y, color, p2.x, p2.y);
	}
}
	
	
/**
	@brief 
	*/
void Paint(HWND hWnd, HDC hdc)
{
	RECT rc;
	GetClientRect(hWnd, &rc);
	HDC memDc = CreateCompatibleDC(hdc);
	HBITMAP hbmMem = CreateCompatibleBitmap(hdc, rc.right-rc.left, rc.bottom-rc.top);
	HBITMAP hbmOld = (HBITMAP)SelectObject(memDc, hbmMem);
	HBRUSH hbrBkGnd = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
	FillRect(memDc, &rc, hbrBkGnd);
	DeleteObject(hbrBkGnd);
		
	const Matrix44 vpv = g_matView * g_matProjection * g_matViewPort;
	
	RenderVertices(memDc, g_axises, vpv);
	
	const Matrix44 tm = g_matLocal * g_matWorld;
	if (g_WireFrame)
		RenderIndices(memDc, g_vertices, g_normals, g_indices, tm, vpv);
	else
		RenderWire(memDc, g_vertices, g_normals, g_indices, tm, vpv);
	
	BitBlt(hdc, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, memDc, 0, 0, SRCCOPY);
	SelectObject(memDc, hbmOld);
	DeleteObject(hbmMem);
	DeleteDC(memDc);
}
	 	
