#pragma once

namespace graphic
{
	class cMaterial
	{
	public:
		cMaterial(void);
		virtual ~cMaterial(void);

		void Init(const Vector4 &ambient,
			const Vector4 &diffuse,
			const Vector4 &specular,
			const Vector4 &emissive,
			const float pow);
		void InitRed();
		void InitBlue();
		void Bind();

		D3DMATERIAL9 m_mtrl;
	};
}

