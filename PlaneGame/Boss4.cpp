#include "stdafx.h"
#include "Boss4.h"
#include "resource.h"

CImageList Boss4::m_Images;

int b4_nn = 0; int b4_m = 0;

Boss4::Boss4() :b4_blood(4000)
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


Boss4::~Boss4()
{
}

BOOL Boss4::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BOSS4, RGB(0, 0, 0), 148, 120, 1);
}

BOOL Boss4::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait>50)
		m_nWait = 0;

	if (!bPause)
	{
		if (b4_nn == 0)
			m_ptPos.x = m_ptPos.x + m_nMotion * m_V;
		if (b4_nn == 1)
			m_ptPos.x = m_ptPos.x - m_nMotion * m_V;
		if (m_ptPos.x >= GAME_WIDTH-BOSS_WIDTH+50)
			b4_nn = 1;
		if (m_ptPos.x <= -50)
			b4_nn = 0;

		if (b4_m == 0)
			m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
		if (b4_m == 1)
			m_ptPos.y = m_ptPos.y - m_nMotion * m_V;
		if (m_ptPos.y >= GAME_HEIGHT - 200)
			b4_m = 1;
		if (m_ptPos.y <= -50)
			b4_m = 0;

	}
	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);
	CPen nPen1(PS_SOLID, 1, RGB(255, 255, 255));
	CBrush nBrush1(RGB(219, 59, 101));
	pDC->SelectObject(&nPen1);
	pDC->SelectObject(&nBrush1);
	pDC->Rectangle(m_ptPos.x, m_ptPos.y, m_ptPos.x +b4_blood/25, m_ptPos.y+10);

	return TRUE;
}


BOOL Boss4::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;
}
void Boss4::setblood(int b)
{
	b4_blood -= b;
}

int Boss4::getblood(void)
{
	return b4_blood;
}
