#include "StdAfx.h"
#include "cRenderer.h"
#include "DxInit.h"

using namespace graphic;

cRenderer::cRenderer(void)
{
}

cRenderer::~cRenderer(void)
{
}

bool cRenderer::CreateDevice(HWND hWnd, const int width, const int height)
{
	if(!InitDirectX(hWnd, width, height, m_pDevice))
		return false;

	return true;
}
LPDIRECT3DDEVICE9 cRenderer::GetDevice()
{
	return m_pDevice;
}



bool graphic::InitRenderer(HWND hWnd, const int width, const int height)
{
	if(cRenderer::Get()->CreateDevice(hWnd, width, height))
		return false;

	return true;
}
void graphic::RealeaseRenderer()
{
	return cRenderer::Release();
}
cRenderer* graphic::GetRenderer()
{
	return cRenderer::Get();
}
LPDIRECT3DDEVICE9 graphic::GetDevice()
{
	return cRenderer::Get()->GetDevice();
}