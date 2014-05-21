
#pragma once

// 버텍스 구조체
struct Vertex
{
	Vertex() {}
	Vertex(float x0, float y0, float z0) : x(x0), y(y0), z(z0) {}
	float x, y, z;
	static const DWORD FVF;
};
//버텍스 구조체 포맷.
const DWORD Vertex::FVF  = D3DFVF_XYZ | D3DFVF_NORMAL;

class cGameApp : public framework::cGameMain
{
private:
	LPDIRECT3DDEVICE9 g_peng;
	LPDIRECT3DVERTEXBUFFER9 g_pVB;
	LPDIRECT3DINDEXBUFFER9 g_pIB;
	int g_VtxSize;
	int g_FaceSize;
	D3DMATERIAL9 g_Mtrl;
	D3DLIGHT9 g_Light;
public:
	cGameApp();
	virtual ~cGameApp();

	virtual bool OnInit() override;
	virtual void OnUpdate(const float elapseT) override;
	virtual void OnRender(const float elapseT) override;
	virtual void OnShutdown() override;
	virtual void MessageProc( UINT message, WPARAM wParam, LPARAM lParam) override;


protected:

};

