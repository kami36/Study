
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
	//LPDIRECT3DDEVICE9 _peng;
	LPDIRECT3DVERTEXBUFFER9 _pVB;
	LPDIRECT3DINDEXBUFFER9 _pIB;
	int _VtxSize;
	int _FaceSize;
	D3DMATERIAL9 _Mtrl;
	D3DLIGHT9 _Light;
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

