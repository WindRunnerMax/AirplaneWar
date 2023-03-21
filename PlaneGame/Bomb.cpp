#include "StdAfx.h"
#include "Bomb.h"
#include "resource.h"

CImageList CBomb::m_Images;


CBomb::CBomb(int x, int y) :CGameObject(x, y) {xx = 0;}
CBomb::CBomb(int x, int y,int z) : CGameObject(x, y),xx(z) 
{
}

CBomb::~CBomb(void)
{
}
BOOL CBomb::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_BOMB,RGB(0,0,0),10,20,1);
}
BOOL CBomb::Draw(CDC* pDC,BOOL bPause)
{
	if(!bPause)
	{
		m_ptPos.y = m_ptPos.y - 12;
		m_ptPos.x = m_ptPos.x - xx;
	}

	if(m_ptPos.y < -BOMB_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC,0,m_ptPos,ILD_TRANSPARENT);

	return TRUE;
}