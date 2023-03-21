#include "StdAfx.h"
#include "Laser.h"
#include "resource.h"


CImageList Laser::m_Images;


Laser::Laser(int x, int y, int idx) :CGameObject(x, y), kind(idx)
{

}

Laser::~Laser(void)
{
}
BOOL Laser::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_LASER, RGB(255, 0, 0), 128, 512, 4);
}
BOOL Laser::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y - 5;
	}
	int cnt = 0;
	if (kind == 3)
	{
		kind = 0;
		cnt++;
		if(cnt == 2)
		return FALSE;
	}
	//用新位置绘制图像
	m_Images.Draw(pDC, kind, m_ptPos, ILD_TRANSPARENT);
	kind++;
	return TRUE;
}