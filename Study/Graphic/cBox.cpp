#include "StdAfx.h"
#include "cBox.h"

using namespace graphic;

cBox::cBox(void)
{
}


cBox::~cBox(void)
{
}

void cBox::SetBox(const Vector3 &vMin, const Vector3 &vMax)
{
	//		3------2
	//	   /|     /|
	//	  / |    / |
	//	 4------1  |
	//	 |  7---|--6
	//	 | /    | /
	//   |/     |/
	//	 8------5
	m_box[0] = Vector3( vMax.x, vMax.y, vMin.z);
	m_box[1] = Vector3( vMin.x, vMax.y, vMin.z);
	m_box[2] = Vector3( vMax.x, vMax.y, vMax.z);
	m_box[3] = Vector3( vMin.x, vMax.y, vMax.z);
	m_box[4] = Vector3( vMax.x, vMin.y, vMin.z);
	m_box[5] = Vector3( vMin.x, vMin.y, vMin.z);
	m_box[6] = Vector3( vMax.x, vMin.y, vMax.z);
	m_box[7] = Vector3( vMin.x, vMin.y, vMax.z);

	m_min = vMin;
	m_max = vMax;
}

bool cBox::IsCollision(const cBox &box)
{
	return true;
}
void cBox::SetWorldTM(const Matrix44 &tm)
{
}