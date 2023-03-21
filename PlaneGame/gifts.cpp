#include "stdafx.h"
#include "gifts.h"
#include "resource.h"

CImageList Gifts::m_ImagesHeart;
CImageList Gifts::m_ImagesStar;
CImageList Gifts::m_ImagesDefense;
CImageList Gifts::m_ImagesWeapon;


Gifts::Gifts(int x,int y,int indexType):type(indexType), CGameObject(x, y)
{
	m_V = rand() % 6 + 1;//随机速度
}

Gifts::~Gifts(){}

BOOL Gifts::LoadImage()
{
	CGameObject::LoadImage(m_ImagesHeart, 166, RGB(255, 255, 255), 30, 30, 2);//心
	CGameObject::LoadImage(m_ImagesStar, 165, RGB(255, 255, 255), 35, 35, 2);//核弹
	CGameObject::LoadImage(m_ImagesDefense, 167, RGB(0, 0, 0), 30, 30, 2);//防护罩
	CGameObject::LoadImage(m_ImagesWeapon,178 , RGB(0, 0, 0), 32, 30, 2);//武器升级
	return true;
}

BOOL  Gifts::Draw(CDC* pDC, BOOL gPause)
{

		m_ptPos.y = m_ptPos.y +  m_V;

	if (m_ptPos.y > GAME_HEIGHT +GIFTS_HEIGHT)
		return FALSE;

	//m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	if(type==1)
		m_ImagesHeart.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	else if(type==2)
		m_ImagesStar.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	else if(type==3)
		m_ImagesDefense.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
	else if(type==4)
		m_ImagesWeapon.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}

