#include "stdafx.h"
#include "Boss5.h"
#include "resource.h"

CImageList Boss5::m_Images;

int b5_nn = 0; int b5_m = 0;

Boss5::Boss5() :b5_blood(6000)
{
	//随机确定x位置
	m_ptPos.x = 50;

	//随机确定图像索引
	m_nImgIndex = 0;
	//根据图像索引确定方向
	m_nMotion = 1;
	m_ptPos.y = 20;
	//随机确定速度
	m_V = 5;
	m_nWait = 0;
}


Boss5::~Boss5()
{
}

BOOL Boss5::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BOSS5, RGB(0, 0, 0), 171, 111, 1);
}

BOOL Boss5::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait>50)
		m_nWait = 0;

	if (!bPause)
	{
		if (b5_nn == 0)
			m_ptPos.x = m_ptPos.x + m_nMotion * m_V;
		if (b5_nn == 1)
			m_ptPos.x = m_ptPos.x - m_nMotion * m_V;
		if (m_ptPos.x >= GAME_WIDTH-BOSS_WIDTH+50)
			b5_nn = 1;
		if (m_ptPos.x <= -50)
			b5_nn = 0;

		if (b5_m == 0)
			m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
		if (b5_m == 1)
			m_ptPos.y = m_ptPos.y - m_nMotion * m_V;
		if (m_ptPos.y >= GAME_HEIGHT - BOSS_HEIGHT + 50)
			b5_m = 1;
		if (m_ptPos.y <= -50)
			b5_m = 0;
	}
	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);
	CPen nPen1(PS_SOLID, 1, RGB(255, 255, 255));
	CBrush nBrush1(RGB(219, 59, 101));
	pDC->SelectObject(&nPen1);
	pDC->SelectObject(&nBrush1);
	pDC->Rectangle(m_ptPos.x, m_ptPos.y, m_ptPos.x+b5_blood/45, m_ptPos.y+10);

	return TRUE;
}


BOOL Boss5::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;
}
void Boss5::setblood(int b)
{
	b5_blood -= b;
}

int Boss5::getblood(void)
{
	return b5_blood;
}
