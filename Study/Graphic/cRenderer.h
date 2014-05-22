#pragma once

namespace graphic
{
	class cRenderer : public common::cSingleton< cRenderer >
	{
	public:
		cRenderer(void);
		virtual ~cRenderer(void);

		bool CreateDevice(HWND hWnd, const int width, const int height);
		LPDIRECT3DDEVICE9 GetDevice();
	private:
		LPDIRECT3DDEVICE9 m_pDevice;
	};

	bool InitRenderer(HWND hWnd, const int width, const int height);
	void RealeaseRenderer();
	cRenderer* GetRenderer();
	LPDIRECT3DDEVICE9 GetDevice();

}