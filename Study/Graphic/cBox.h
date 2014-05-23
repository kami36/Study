#pragma once

namespace graphic
{
	class cBox
	{
	public:
		cBox(void);
		~cBox(void);

		void SetBox(const Vector3 &vMin, const Vector3 &vMax);
		bool IsCollision(const cBox &box);
		void SetWorldTM(const Matrix44 &tm);

		Vector3 m_min, m_max;
		vector<Vector3> m_box;
		Matrix44 m_tm;
	};

}