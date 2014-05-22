#include "StdAfx.h"
#include "cMaterial.h"

using namespace graphic;

cMaterial::cMaterial(void)
{
}


cMaterial::~cMaterial(void)
{
}

void cMaterial::Init(const Vector4 &ambient, const Vector4 &diffuse, const Vector4 &specular, const Vector4 &emissive, const float pow)
{
	ZeroMemory(&m_mtrl, sizeof(m_mtrl));
	m_mtrl.Ambient =	*(D3DXCOLOR*)&ambient;
	m_mtrl.Diffuse =	*(D3DXCOLOR*)&diffuse;
	m_mtrl.Specular =	*(D3DXCOLOR*)&specular;
	m_mtrl.Emissive =	*(D3DXCOLOR*)&emissive;
	m_mtrl.Power =		pow;

}

void cMaterial::InitRed()
{
	Init(Vector4(1,0,0,1),
		Vector4(1,0,0,1),
		Vector4(1,0,0,1),
		Vector4(0,0,0,1),
		0);
}
void cMaterial::InitBlue()
{
	Init(Vector4(0,0,1,1),
		Vector4(0,0,1,1),
		Vector4(0,0,1,1),
		Vector4(0,0,0,1),
		0);
}

void cMaterial::Bind()
{
	GetDevice()->SetMaterial(&m_mtrl);
}