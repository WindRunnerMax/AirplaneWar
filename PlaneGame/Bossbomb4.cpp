#include "StdAfx.h"
#include "Bossbomb4.h"
#include "resource.h"


CImageList Bossbomb4::m_Images;
CImageList Bossbomb4::m_Images2;
CImageList Bossbomb4::m_Images3;
CImageList Bossbomb4::m_Images4;


Bossbomb4::Bossbomb4(int x, int y, int nMontion,int z) :CGameObject(x, y), m_nMotion(nMontion),kind(z)
{

}

Bossbomb4::~Bossbomb4(void)
{
}
BOOL Bossbomb4::LoadImage()
{
	//加载游戏对象的图标对象
	CBitmap bomb1;//下
	if (!bomb1.LoadBitmapW(IDB_BOSS4BALL1))
		return FALSE;
	CBitmap bomb2;//右
	if (!bomb2.LoadBitmapW(IDB_BOSS4BALL2))
		return FALSE;
	CBitmap bomb3;//上
	if (!bomb3.LoadBitmapW(IDB_BOSS4BALL3))
		return FALSE;
	CBitmap bomb4;//左
	if (!bomb4.LoadBitmapW(IDB_BOSS4BALL4))
		return FALSE;
	//创建CImageList对象
	if (!m_Images.Create(30, 60, ILC_COLOR24 | ILC_MASK, 1, 0))//nInitial初始个数
		return FALSE;//cx,cy 图片的宽度
	if (!m_Images2.Create(60, 30, ILC_COLOR24 | ILC_MASK, 1, 0))//nInitial初始个数
		return FALSE;//cx,cy 图片的宽度
	if (!m_Images3.Create(30, 60, ILC_COLOR24 | ILC_MASK, 1, 0))//nInitial初始个数
		return FALSE;//cx,cy 图片的宽度
	if (!m_Images4.Create(60, 30, ILC_COLOR24 | ILC_MASK, 1, 0))//nInitial初始个数
		return FALSE;//cx,cy 图片的宽度

					 //图像链表中加入对象对应的图标对象，之后直接通过该链表访问图标对象
	m_Images.Add(&bomb1, RGB(0, 0, 0));
	m_Images2.Add(&bomb2, RGB(0, 0, 0));
	m_Images3.Add(&bomb3, RGB(0, 0, 0));
	m_Images4.Add(&bomb4, RGB(0, 0, 0));

	return TRUE;
}
BOOL Bossbomb4::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		if (kind == 1)
		{
			m_ptPos.y = m_ptPos.y + m_nMotion * 8;
			m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
		}
		else if (kind == 2)
		{
			m_ptPos.x = m_ptPos.x + m_nMotion * 20;
			m_Images2.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
		}
		else if (kind == 3)
		{
			m_ptPos.y = m_ptPos.y - m_nMotion * 8;
			m_Images3.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
		}
		else if (kind == 4)
		{
			m_ptPos.x = m_ptPos.x - m_nMotion * 20;
			m_Images4.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);
		}
		//m_ptPos.y = m_ptPos.y + m_nMotion * 8;
		//m_ptPos.x = (int)100 * sin(m_ptPos.y*0.01);
		//if (m_ptPos.x < 0)
		//{
		//	m_ptPos.x = -m_ptPos.x;
		//}
		//m_ptPos.x =100+ (int)50 * sin(m_ptPos.y*0.1); // 子弹效果
		//m_ptPos.y = m_ptPos.y - 8;

	}

	if (m_ptPos.y > GAME_HEIGHT + BOMB_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BOMB_HEIGHT)
		return FALSE;
	
	return TRUE;
}