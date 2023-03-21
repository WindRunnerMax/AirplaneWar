#include "StdAfx.h"
#include "Bossbomb6.h"
#include "resource.h"


CImageList Bossbomb6::m_Images;


Bossbomb6::Bossbomb6(int x, int y, int nMontion,int zz) :CGameObject(x, y), m_nMotion(nMontion),z(zz)
{

}

Bossbomb6::~Bossbomb6(void)
{
}
BOOL Bossbomb6::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BOSS6BALL, RGB(0, 0, 0), 35, 58, 1);
}
BOOL Bossbomb6::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * 8;
		m_ptPos.x = m_ptPos.x + m_nMotion * z;
	}

	if (m_ptPos.y > GAME_HEIGHT + BOMB_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BOMB_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}