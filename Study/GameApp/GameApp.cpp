
#include "stdafx.h"
#include "GameApp.h"


INIT_FRAMEWORK(cGameApp)

cGameApp::cGameApp()
{
	m_windowName = L"GameApp";
	const RECT r = {0, 0, 800, 600};
	m_windowRect = r;
}

cGameApp::~cGameApp()
{

}


bool cGameApp::OnInit()
{
	g_peng = NULL;
	g_pVB = NULL;
	g_pIB = NULL;
	g_VtxSize = 8;
	g_FaceSize = 12;

	// ���ؽ� ���� ����.
	if (FAILED(g_peng->CreateVertexBuffer( g_VtxSize * sizeof(Vertex),
		D3DUSAGE_WRITEONLY, Vertex::FVF,
		D3DPOOL_MANAGED, &g_pVB, NULL)))
	{
		return false;
	}
	// ���ؽ� ���� �ʱ�ȭ.
	Vertex* vertices;
	if (FAILED(g_pVB->Lock( 0, sizeof(Vertex), (void**)&vertices, 0)))
		return false;

	vertices[0] = Vertex(-10, -10, -10);
	vertices[1] = Vertex( 10, -10, -10);
	vertices[2] = Vertex( 10,  10, -10);
	vertices[3] = Vertex(-10,  10, -10);
	vertices[4] = Vertex(-10, -10,  10);
	vertices[5] = Vertex( 10, -10,  10);
	vertices[6] = Vertex( 10,  10,  10);
	vertices[7] = Vertex(-10,  10,  10);

	g_pVB->Unlock();

	//if (g_FaceSize <= 0)
	//	return false;
	
	if (FAILED(g_peng->CreateIndexBuffer(g_FaceSize*3*sizeof(WORD), 
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIB, NULL)))
	{
		return false;
	}

	WORD *indices = NULL;
	g_pIB->Lock(0, 0, (void**)&indices, 0);

	indices[0] = 7;
	indices[1] = 5;
	indices[2] = 6;
	indices[3] = 7;
	indices[4] = 4;
	indices[5] = 5;
	indices[6] = 3;
	indices[7] = 2;
	indices[8] = 1;
	indices[9] = 3;
	indices[10] = 1;
	indices[11] = 0;
	indices[12] = 2;
	indices[13] = 6;
	indices[14] = 5;
	indices[15] = 2;
	indices[16] = 5;
	indices[17] = 1;
	indices[18] = 3;
	indices[19] = 7;
	indices[20] = 6;
	indices[21] = 3;
	indices[22] = 6;
	indices[23] = 2;
	indices[24] = 0;
	indices[25] = 4;
	indices[26] = 7;
	indices[27] = 0;
	indices[28] = 7;
	indices[29] = 3;
	indices[30] = 1;
	indices[31] = 5;
	indices[32] = 4;
	indices[33] = 1;
	indices[34] = 4;
	indices[35] = 0;

	g_pIB->Unlock();


	return true;
}


void cGameApp::OnUpdate(const float elapseT)
{

}


void cGameApp::OnRender(const float elapseT)
{
	if (SUCCEEDED(g_peng->Clear( 
		0,			//û���� ������ D3DRECT �迭 ����		( ��ü Ŭ���� 0 )
		NULL,		//û���� ������ D3DRECT �迭 ������		( ��ü Ŭ���� NULL )
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,	//û�ҵ� ���� �÷��� ( D3DCLEAR_TARGET �÷�����, D3DCLEAR_ZBUFFER ���̹���, D3DCLEAR_STENCIL ���ٽǹ���
		D3DCOLOR_XRGB(0, 0, 255),			//�÷����۸� û���ϰ� ä���� ����( 0xAARRGGBB )
		1.0f,				//���̹��۸� û���Ұ� ( 0 ~ 1 0 �� ī�޶󿡼� ���ϰ���� 1 �� ī�޶󿡼� ���� �� )
		0					//���ٽ� ���۸� ä�ﰪ
		)))
	{
		//ȭ�� û�Ұ� ���������� �̷�� ���ٸ�... ������ ����
		g_peng->BeginScene();

		g_peng->SetStreamSource( 0, g_pVB, 0, sizeof( Vertex ) );
		g_peng->SetFVF( Vertex::FVF );
		g_peng->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 1 );

		//������ ��
		g_peng->EndScene();
		//�������� �������� �������� ���� ȭ������ ����
		g_peng->Present( NULL, NULL, NULL, NULL );
	}
}


void cGameApp::OnShutdown()
{

}


void cGameApp::MessageProc( UINT message, WPARAM wParam, LPARAM lParam)
{

}