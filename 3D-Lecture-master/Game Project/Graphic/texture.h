#pragma once

namespace graphic
{
	class cTexture
	{
	public:
		cTexture();
		virtual ~cTexture();

		bool Create(const string &fileName);
		void Bind(int stage);
		void Clear();
		

	protected:


	private:
		IDirect3DTexture9* m_texture;
	};
}
