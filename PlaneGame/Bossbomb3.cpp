#include "StdAfx.h"
#include "Bossbomb3.h"
#include "resource.h"


CImageList Bossbomb3::m_Images;


Bossbomb3::Bossbomb3(int x, int y, int nMontion,int zz) :CGameObject(x, y), m_nMotion(nMontion),z(zz)
{

}

Bossbomb3::~Bossbomb3(void)
{
}
BOOL Bossbomb3::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BOSS3BALL, RGB(0, 0, 0), 32, 59, 1);
}
BOOL Bossbomb3::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * 8;
		m_ptPos.x = m_ptPos.x + m_nMotion * z; 
		//m_ptPos.x = (int)100 * sin(m_ptPos.y*0.01);
		//if (m_ptPos.x < 0)
		//{
		//	m_ptPos.x = -m_ptPos.x;
		//}
		//m_ptPos.x =100+ (int)50 * sin(m_ptPos.y*0.1); // ×Óµ¯Ð§¹û
		//m_ptPos.y = m_ptPos.y - 8;
	}

	if (m_ptPos.y > GAME_HEIGHT + BOMB_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BOMB_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}