#include "StdAfx.h"
#include "Bossbomb2.h"
#include "resource.h"


CImageList Bossbomb2::m_Images;


Bossbomb2::Bossbomb2(int x, int y,int kx,int ky,int nMontion) :CGameObject(x, y), dx(kx),dy(ky),m_nMotion(nMontion)
{
}

Bossbomb2::Bossbomb2(int x, int y, int nMontion) :CGameObject(x, y), m_nMotion(nMontion)
{
}

Bossbomb2::~Bossbomb2(void)
{
}
BOOL Bossbomb2::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BOSS2BALL, RGB(0, 0, 0), 32, 55, 1);
}
BOOL Bossbomb2::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y +15;
		if(dy == 0) m_ptPos.x += 15;
		else m_ptPos.x = m_ptPos.x + 15 * dx/dy;
		if (m_ptPos.x < 0)
		{
			m_ptPos.x = -m_ptPos.x;
		}
	}

	if (m_ptPos.y > GAME_HEIGHT + BOMB_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BOMB_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}