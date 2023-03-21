#include "stdafx.h"
#include "Boss3.h"
#include "resource.h"

CImageList Boss3::m_Images;

int b3_nn = 0; int b3_m = 0;

Boss3::Boss3():b3_blood(2000)
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


Boss3::~Boss3()
{
}

BOOL Boss3::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BOSS3, RGB(0, 0, 0), 152, 115, 1);
}

BOOL Boss3::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait>50)
		m_nWait = 0;

	if (!bPause)
	{
		if (b3_nn == 0)
			m_ptPos.x = m_ptPos.x + m_nMotion * m_V;
		if (b3_nn == 1)
			m_ptPos.x = m_ptPos.x - m_nMotion * m_V;
		if (m_ptPos.x >= GAME_WIDTH-BOSS_WIDTH+50)
			b3_nn = 1;
		if (m_ptPos.x <= -50)
			b3_nn = 0;

		if (b3_m == 0)
			m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
		if (b3_m == 1)
			m_ptPos.y = m_ptPos.y - m_nMotion * m_V;
		if (m_ptPos.y >= GAME_HEIGHT-200)
			b3_m = 1;
		if (m_ptPos.y <= -50)
			b3_m = 0;

	}
	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);
	CPen nPen1(PS_SOLID, 1, RGB(255, 255, 255));
	CBrush nBrush1(RGB(219, 59, 101));
	pDC->SelectObject(&nPen1);
	pDC->SelectObject(&nBrush1);
	pDC->Rectangle(m_ptPos.x, m_ptPos.y, m_ptPos.x + b3_blood/16, m_ptPos.y+10);

	return TRUE;
}


BOOL Boss3::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;
}
void Boss3::setblood(int b)
{
	b3_blood -= b;
}

int Boss3::getblood(void)
{
	return b3_blood;
}
