#include "StdAfx.h"
#include "Bossbomb.h"
#include "resource.h"


CImageList Bossbomb::m_Images;


Bossbomb::Bossbomb(int x, int y, int nMontion) :CGameObject(x, y), m_nMotion(nMontion)
{

}

Bossbomb::~Bossbomb(void)
{
}
BOOL Bossbomb::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BOSS1BALL, RGB(0, 0, 0), 30, 58, 1);
}
BOOL Bossbomb::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * 8;
	}

	if (m_ptPos.y > GAME_HEIGHT + BOMB_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BOMB_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}