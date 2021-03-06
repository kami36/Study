#include <windows.h>
#include "math/Math.h"
#include "DrawTriangle.h"
#include "Renderer.h"
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
#include <algorithm>
#include "particle.h"

using namespace std;

const int WINSIZE_X = 800;		//초기 윈도우 가로 크기
const int WINSIZE_Y = 600;	//초기 윈도우 세로 크기
const int WINPOS_X = 0; //초기 윈도우 시작 위치 X
const int WINPOS_Y = 0; //초기 윈도우 시작 위치 Y

HWND g_hWnd;
vector<Vector3> g_vertices;
vector<Vector3> g_normals;
vector<int> g_indices;
Matrix44 g_matWorld;
Matrix44 g_matLocal;

vector<Vector3> g_wingVertices;
vector<Vector3> g_wingNormals;
vector<int> g_wingIndices;

Vector3 g_PenguinPos(0,0,-300);
Vector3 g_PenguinVel(0, 0, 3000.f);
float g_wingRot = 0;

const int MAX_GROUND = 6;
vector<Vector3> g_groundVtx;
vector<Vector3> g_groundNormals;
vector<int> g_groundIdx;
vector<Matrix44> g_matGrounds(MAX_GROUND);

vector<Vector3> g_obstructVtx;
vector<Vector3> g_obstructNormals;
vector<int> g_obstructdIdx;
vector<Matrix44> g_matObstructs(MAX_GROUND);

Box g_obstructBox;
Box g_penguinBox;

bool g_Stop = false;

Matrix44 g_matView;
Matrix44 g_matProjection;
Matrix44 g_matViewPort;
Vector3 g_cameraPos(0,300,-1000);
Vector3 g_cameraLookat(0,0,1000);

cParticleManager g_particleMng;



// 콜백 프로시져 함수 프로토 타입
LRESULT CALLBACK WndProc( HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam );
void MainLoop(int elapse_time);
void	Render(HWND hWnd);
void	Paint(HWND hWnd, HDC hdc);
void	ComputeNormals(const vector<Vector3> &vertices, const vector<int> &indices, vector<Vector3> &normals);
bool ReadModelFile( const string &fileName, vector<Vector3> &vertices, vector<int> &indices, vector<Vector3> &normals );
bool Init();
void GetVerticesMinMax( const vector<Vector3> &vertices, OUT Vector3 &vMin, OUT Vector3 &vMax);


int APIENTRY WinMain(HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPSTR lpCmdLine, 
	int nCmdShow)
{
	wchar_t className[32] = L"Sample";
	wchar_t windowName[32] = L"Sample";

	//윈도우 클레스 정보 생성
	//내가 이러한 윈도를 만들겠다 라는 정보
	WNDCLASS WndClass;
	WndClass.cbClsExtra = 0;			//윈도우에서 사용하는 여분의 메모리설정( 그냥 0 이다  신경쓰지말자 )
	WndClass.cbWndExtra = 0;			//윈도우에서 사용하는 여분의 메모리설정( 그냥 0 이다  신경쓰지말자 )
	WndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);		//윈도우 배경색상
	WndClass.hCursor = LoadCursor( NULL, IDC_ARROW );			//윈도우의 커서모양 결정
	WndClass.hIcon = LoadIcon( NULL, IDI_APPLICATION );		//윈도우아이콘모양 결정
	WndClass.hInstance = hInstance;				//프로그램인스턴스핸들 
	WndClass.lpfnWndProc = (WNDPROC)WndProc;			//윈도우 프로시져 함수 포인터
	WndClass.lpszMenuName = NULL;						//메뉴이름 없으면 NULL
	WndClass.lpszClassName = className;				//지금 작성하고 있는 윈도우 클레스의 이름
	WndClass.style	 = CS_HREDRAW | CS_VREDRAW;	//윈도우 그리기 방식 설정 ( 사이즈가 변경될때 화면갱신 CS_HREDRAW | CS_VREDRAW )

	//위에서 작성한 윈도우 클레스정보 등록
	RegisterClass( &WndClass );

	//윈도우 생성
	//생성된 윈도우 핸들을 전역변수 g_hWnd 가 받는다.
	HWND hWnd = CreateWindow(
		className,				//생성되는 윈도우의 클래스이름
		windowName,				//윈도우 타이틀바에 출력되는 이름
		WS_OVERLAPPEDWINDOW,	//윈도우 스타일 WS_OVERLAPPEDWINDOW
		WINPOS_X,				//윈도우 시작 위치 X 
		WINPOS_Y,				//윈도우 시작 위치 Y
		WINSIZE_X,				//윈도우 가로 크기 ( 작업영역의 크기가 아님 )
		WINSIZE_Y,				//윈도우 세로 크기 ( 작업영역의 크기가 아님 )
		GetDesktopWindow(),		//부모 윈도우 핸들 ( 프로그램에서 최상위 윈도우면 NULL 또는 GetDesktopWindow() )
		NULL,					//메뉴 ID ( 자신의 컨트롤 객체의 윈도우인경우 컨트롤 ID 가 된	
		hInstance,				//이 윈도우가 물릴 프로그램 인스턴스 핸들
		NULL					//추가 정보 NULL ( 신경끄자 )
		);

	g_hWnd = hWnd;

	//윈도우를 정확한 작업영역 크기로 맞춘다
	RECT rcClient = { 0, 0, WINSIZE_X, WINSIZE_Y };
	AdjustWindowRect( &rcClient, WS_OVERLAPPEDWINDOW, FALSE );	//rcClient 크기를 작업 영영으로 할 윈도우 크기를 rcClient 에 대입되어 나온다.

	//윈도우 크기와 윈도우 위치를 바꾸어준다.
	SetWindowPos( hWnd, NULL, 0, 0, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top, 
		SWP_NOZORDER | SWP_NOMOVE );

	Init();

	ShowWindow( hWnd, nCmdShow );

	//메시지 구조체
	MSG msg;		
	ZeroMemory( &msg, sizeof( MSG ) );

	int oldT = GetTickCount();
	while (msg.message != WM_QUIT)
	{
		//PeekMessage 는 메시지 큐에 메시지가 없어도 프로그램이 멈추기 않고 진행이 된다.
		//이때 메시지큐에 메시지가 없으면 false 가 리턴되고 메시지가 있으면 true 가 리턴이된다.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage( &msg ); //눌린 키보드 의 문자를 번역하여 WM_CHAR 메시지를 발생시킨다.
			DispatchMessage( &msg );  //받아온 메시지 정보로 윈도우 프로시져 함수를 실행시킨다.
		}
		else
		{
			const int curT = GetTickCount();
			const int elapseT = curT - oldT;
			if (elapseT > 10)
			{
				oldT = curT;
				MainLoop(elapseT);	
			}
		}
	}

	return 0;
}


//
// 윈도우 프로시져 함수 ( 메시지 큐에서 받아온 메시지를 처리한다 )
//
LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (msg)
	{
	case WM_ERASEBKGND:
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Paint(hWnd, hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		{
			switch (wParam)
			{
			case VK_ESCAPE:
				::DestroyWindow(hWnd);
				break;

			case 'E':
			case 'C':
				{
					Matrix44 mat;
					mat.SetRotationY( (wParam == 'E')? 0.1f : -0.1f);
					g_cameraPos *= mat;
					Vector3 dir = g_cameraLookat - g_cameraPos;
					dir.Normalize();
					g_matView.SetView(g_cameraPos, dir, Vector3(0,1,0));
				}
				break;

			case 'P':
				g_Stop = !g_Stop;
				break;
			}

		}
		break;
	case WM_DESTROY: //윈도우가 파괴된다면..
		PostQuitMessage(0);	//프로그램 종료 요청 ( 메시지 루프를 빠져나가게 된다 )
		break;
	}
	return DefWindowProc( hWnd, msg, wParam, lParam );
}


/**
 @brief 
 */
void	MainLoop(int elapse_time)
{
	float elapse_fT = (elapse_time * 0.001f);
	float static incT = elapse_fT;

	// 충돌 체크.
	g_penguinBox.SetWorldTM(g_matLocal * g_matWorld);
	g_penguinBox.Update();
	for (int i=0; i < (int)g_matObstructs.size(); ++i)
	{
		Matrix44 matS;
		matS.SetScale(Vector3(1,1,4)); // 충돌박스를 Z축으로 좀더 키운다. 프레임속도가 느리면, 충돌 폭이 좁아지기 때문.
		g_obstructBox.SetWorldTM(matS * g_matObstructs[ i]);
		g_obstructBox.Update();
		if (g_penguinBox.Collision(g_obstructBox))
		{
			Vector3 dispPos = g_PenguinPos * (g_matLocal * g_matWorld *  g_matView * g_matProjection * g_matViewPort);

			// 충돌.
			POINT pos = {(int)dispPos.x, 600-(int)dispPos.y};
			for (int k=0; k < 6; ++k)
				g_particleMng.AddParticle(new cParticle(pos));
		}
	}


	// keyboard
	const float movOffset = 20.f;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		g_PenguinPos.x += -movOffset;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		g_PenguinPos.x += movOffset;
	}
	
	// 펭귄 날개 흔들거리기.
	g_wingRot += elapse_fT;
//	if (g_wingRot > 0.5f)
//		g_wingRot -= elapse_fT;


	// 펭귄 이동
	const Vector3 mov = (g_Stop)? Vector3(0,0,0) : g_PenguinVel * incT;
	g_PenguinPos += mov;
	Matrix44 matMov;
	matMov.SetTranslate(g_PenguinPos);
	g_matWorld  = matMov;

	// 카메라 이동
	g_cameraLookat += mov;
	g_cameraPos += mov;
	Vector3 dir = g_cameraLookat - g_cameraPos;
	dir.Normalize();
	g_matView.SetView(g_cameraPos, dir, Vector3(0,1,0));


	// scroll & generate obstacle
	static int groundFront = 0;
	if (g_matGrounds[ groundFront]._43 < g_cameraPos.z+600)
	{
		const int backIdx = (groundFront + g_matGrounds.size() - 1) % g_matGrounds.size();
		g_matGrounds[ groundFront]._43 = g_matGrounds[ backIdx]._43 + 600.F;
		
		g_matObstructs[ groundFront]._43 = g_matGrounds[ backIdx]._43 + 600.F;
		g_matObstructs[ groundFront]._41 = (rand() % 500) - 250.f;

		++groundFront;
		groundFront %= g_matGrounds.size();
	}
	

	g_particleMng.Move(elapse_time);

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


bool Init()
{
	srand((int)time(NULL));

	// 모델 생성.
	ReadModelFile("cube.dat", g_vertices, g_indices, g_normals);
	ReadModelFile("wing.dat", g_wingVertices, g_wingIndices, g_wingNormals);
	ReadModelFile("plane.dat", g_groundVtx, g_groundIdx, g_groundNormals);
	ReadModelFile("cone.dat", g_obstructVtx, g_obstructdIdx, g_obstructNormals);

	g_matLocal.SetScale(Vector3(0.25f, 0.4f, 0.25f));

	// 충돌 박스 생성
	Vector3 vMin, vMax;
	GetVerticesMinMax(g_vertices, vMin, vMax);
	g_penguinBox.SetBox(vMin, vMax);

	GetVerticesMinMax(g_obstructVtx, vMin, vMax);
	g_obstructBox.SetBox(vMin, vMax);

	
	for (int i=0; i < (int)g_matGrounds.size(); ++i)
	{
		Matrix44 matS;
		matS.SetScale(Vector3(10, 10, 10));
		Matrix44 matT;
		matT.SetTranslate(Vector3(10, 10, 550.f*i));
		g_matGrounds[ i] = matS * matT;
	}

	for (int i=0; i < (int)g_matObstructs.size(); ++i)
	{
		Matrix44 matS;
		matS.SetScale(Vector3(3, 3, 3));

		Vector3 pos;
		pos.x = (rand() % 500) - 250.f;
		pos.z = 550.f * i;
		Matrix44 matT;
		matT.SetTranslate(pos);

		g_matObstructs[ i] = matS * matT;
	}

	Vector3 dir = g_cameraLookat - g_cameraPos;
	dir.Normalize();
	g_matView.SetView(g_cameraPos, dir, Vector3(0,1,0));
	g_matProjection.SetProjection( MATH_PI / 4.f, 1.0f, 1.0f, 100.0f );

	RECT cr;
	::GetClientRect(g_hWnd, &cr);
	g_matViewPort._11 = WINSIZE_X/2;
	g_matViewPort._22 = -WINSIZE_Y/2;
	g_matViewPort._33 = 0;
	g_matViewPort._41 = WINSIZE_X/2;
	g_matViewPort._42 = WINSIZE_Y/2;
	g_matViewPort._43 = 0;

	return true;
}


// vertices의 최대,최소 정점위치를 리턴한다.
void GetVerticesMinMax( const vector<Vector3> &vertices, OUT Vector3 &vMin, OUT Vector3 &vMax)
{
	vMax = Vector3(FLT_MIN, FLT_MIN, FLT_MIN);
	vMin = Vector3(FLT_MAX, FLT_MAX, FLT_MAX);

	for (int i=0; i < (int)vertices.size(); ++i)
	{
		const Vector3 &v = vertices[i];

		if (vMax.x < v.x)
			vMax.x = v.x;
		if (vMax.y < v.y)
			vMax.y = v.y;
		if (vMax.z < v.z)
			vMax.z = v.z;

		if (vMin.x > v.x)
			vMin.x = v.x;
		if (vMin.y > v.y)
			vMin.y = v.y;
		if (vMin.z > v.z)
			vMin.z = v.z;
	}
}


/**
 @brief 
 @date 2014-04-07
*/
void ComputeNormals(const vector<Vector3> &vertices, const vector<int> &indices, vector<Vector3> &normals)
{
	normals.resize(vertices.size());

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

		if (normals[ indices[ i]].IsEmpty())
		{
			normals[ indices[ i]] = n;
		}
		else
		{
			normals[ indices[ i]] += n;
			normals[ indices[ i]] /= 2.f;
		}

		if (normals[ indices[ i+1]].IsEmpty())
		{
			normals[ indices[ i+1]] = n;
		}
		else
		{
			normals[ indices[ i+1]] += n;
			normals[ indices[ i+1]] /= 2.f;
		}

		if (normals[ indices[ i+2]].IsEmpty())
		{
			normals[ indices[ i+2]] = n;
		}
		else
		{
			normals[ indices[ i+2]] += n;
			normals[ indices[ i+2]] /= 2.f;
		}
	}
}


bool ReadModelFile( const string &fileName, vector<Vector3> &vertices, vector<int> &indices, vector<Vector3> &normals )
{
	using namespace std;
	ifstream fin(fileName.c_str());
	if (!fin.is_open())
		return false;

	string vtx, vtx_eq;
	int numVertices;
	fin >> vtx >> vtx_eq >> numVertices;

	if (numVertices <= 0)
		return  false;

	vertices.resize(numVertices);

	float num1, num2, num3;
	for (int i = 0; i < numVertices; i++)
	{
		fin >> num1 >> num2 >> num3;
		vertices[i] = Vector3(num1, num2, num3);
	}

	string idx, idx_eq;
	int numIndices;
	fin >> idx >> idx_eq >> numIndices;

	if (numIndices <= 0)
		return false;

	indices.resize(numIndices*3);

	int num4, num5, num6;
	for (int i = 0; i < numIndices*3; i+=3)
	{
		fin >> num4 >> num5 >> num6;
		indices[ i] = num4;
		indices[ i+1] = num5;
		indices[ i+2] = num6;	
	}

	ComputeNormals(vertices, indices, normals);
	return true;
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

	Matrix44 vpv = g_matView * g_matProjection * g_matViewPort;

	RenderIndices(hdcMem, g_vertices, g_indices, g_normals, 
		g_matLocal * g_matWorld, vpv);


	Matrix44 wingS;
	wingS.SetScale(Vector3(0.4f, 0.04f, 0.2f));
	Matrix44 wingTR, wingTL;
	wingTR.SetTranslate(Vector3(25,20,0));
	wingTL.SetTranslate(Vector3(-25,20,0));

	Matrix44 wingR;
	wingR.SetRotationZ(g_wingRot);

	Matrix44 wingMR = wingS * wingR * wingTR * g_matWorld;
//	RenderIndices(hdcMem, g_vertices, g_indices, g_normals, 
//		wingMR, vpv);
	RenderIndices(hdcMem, g_wingVertices, g_wingIndices, 
		g_wingNormals, wingMR, vpv);
	Matrix44 wingML = wingS * wingR * wingTL * g_matWorld;
	RenderIndices(hdcMem, g_wingVertices, g_wingIndices, 
		g_wingNormals, wingML, vpv);
//	RenderIndices(hdcMem, g_vertices, g_indices, g_normals, 
//		wingML, vpv);



	for (int i=0; i < (int)g_matGrounds.size(); ++i)
		RenderIndices(hdcMem, g_groundVtx, g_groundIdx, g_groundNormals, g_matGrounds[ i], vpv);
	for (int i=0; i < (int)g_matObstructs.size(); ++i)
		RenderIndices(hdcMem, g_obstructVtx, g_obstructdIdx, g_obstructNormals, g_matObstructs[ i], vpv);

	// 충돌 박스 출력.
	//RenderVertices(hdcMem, g_penguinBox.m_box, g_matLocal * g_matWorld * vpv);
	//for (int i=0; i < (int)g_matObstructs.size(); ++i)
	//	RenderVertices(hdcMem, g_obstructBox.m_box, g_matObstructs[ i] * vpv);
	
	g_particleMng.Render(hdcMem);

	BitBlt(hdc, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, hdcMem, 0, 0, SRCCOPY);
	SelectObject(hdcMem, hbmOld);
	DeleteObject(hbmMem);
	DeleteDC(hdcMem);
}
