#include "stdafx.h"
#include "Boss2.h"
#include "resource.h"

CImageList Boss2::m_Images;

int b2_nn = 0; //0向右，1向左
int b2_m = 0;//0向下，1向上

Boss2::Boss2()
	: b2_blood(500)
{
	//随机确定x位置
	m_ptPos.x = 500;

	//随机确定图像索引
	m_nImgIndex = 0;
	//根据图像索引确定方向
	m_nMotion = 1;
	m_ptPos.y = 70;
	//随机确定速度
	m_V = 5;
	m_nWait = 0;
}


Boss2::~Boss2()
{
}

BOOL Boss2::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BOSS2, RGB(0, 0, 0), 100, 85, 1);
}

BOOL Boss2::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait>50)
		m_nWait = 0;

	if (!bPause)
	{
		if (b2_nn == 0)
			m_ptPos.x = m_ptPos.x + m_nMotion * m_V;
		if (b2_nn == 1)
			m_ptPos.x = m_ptPos.x - m_nMotion * m_V;
		if (m_ptPos.x >= GAME_WIDTH-BOSS_WIDTH+50)
			b2_nn = 1;
		if (m_ptPos.x <= -50)
			b2_nn = 0;

		if (b2_m == 0)
			m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
		if (b2_m == 1)
			m_ptPos.y = m_ptPos.y - m_nMotion * m_V;
		if (m_ptPos.y >= GAME_HEIGHT - 200)
			b2_m = 1;
		if (m_ptPos.y <= -50)
			b2_m = 0;

	}
	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);

	//画血条
	CPen nPen1(PS_SOLID, 1, RGB(255, 255, 255));
	CBrush nBrush1(RGB(219, 59, 101));
	pDC->SelectObject(&nPen1);
	pDC->SelectObject(&nBrush1);
	pDC->Rectangle(m_ptPos.x+5, m_ptPos.y, m_ptPos.x+5+b2_blood/5, m_ptPos.y+10);

	return TRUE;
}


BOOL Boss2::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;
}
void Boss2::setblood(int b)
{
	b2_blood -= b;
}

int Boss2::getblood(void)
{
	return b2_blood;
}
