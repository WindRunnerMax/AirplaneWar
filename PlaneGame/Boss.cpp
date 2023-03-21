#include "stdafx.h"
#include "Boss.h"
#include "resource.h"


CImageList Boss::m_Images;

int nn = 0; int m = 0;//0为正方向，1为负方向

Boss::Boss():blood (500)
{
	m_ptPos.x = 50;
	m_nImgIndex = 0;
	//根据图像索引确定方向
	m_nMotion = 1;
	m_ptPos.y = 20;
	m_V = 5;
	m_nWait = 0;
}


Boss::~Boss()
{

}
BOOL Boss::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BOSS1, RGB(0,0,0), 107, 81, 1);
}

BOOL Boss::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait>50)
		m_nWait = 0;

	if (!bPause)
	{
		if (nn == 0)
			m_ptPos.x = m_ptPos.x + m_nMotion * m_V;
		if (nn == 1)
			m_ptPos.x = m_ptPos.x - m_nMotion * m_V;
		if (m_ptPos.x >= GAME_WIDTH-BOSS_HEIGHT+50)
			nn = 1;
		if (m_ptPos.x <= -50)
			nn = 0;

		if (m == 0)
			m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
		if (m == 1)
			m_ptPos.y = m_ptPos.y - m_nMotion * m_V;
		if (m_ptPos.y >= GAME_HEIGHT -200)
			m = 1;
		if (m_ptPos.y <= -50)
			m = 0;

	}
	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);
	//绘制血条
	CPen nPen1(PS_SOLID, 1, RGB(255, 255, 255));
	CBrush nBrush1(RGB(219, 59, 101));
	pDC->SelectObject(&nPen1);
	pDC->SelectObject(&nBrush1);
	pDC->Rectangle(m_ptPos.x+8, m_ptPos.y, m_ptPos.x+8+blood/5, m_ptPos.y+10);
	return TRUE;
}


BOOL Boss::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;
}
void Boss::setblood(int b)
{
	blood -= b;
}

int Boss::getblood(void)
{
	return blood;
}
