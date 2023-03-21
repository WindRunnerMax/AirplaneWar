#pragma once
#include "GameObject.h"
class Boss4 :
	public CGameObject
{
public:
	Boss4();
	~Boss4();

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + BOSS_WIDTH, m_ptPos.y + BOSS_HEIGHT));
	}

	int GetMontion() const
	{
		return m_nMotion;
	}
	//是否可以开火发子弹
	BOOL Fired();
private:
	static const int BOSS_HEIGHT = 120;
	static const int BOSS_WIDTH = 148;
	static CImageList m_Images;
	int m_nMotion;
	//方向 ：
	//1 向下；0停止；-1向上
	//图像索引
	int m_nImgIndex;
	//速度;
	int m_V;
	int m_nWait; //发射延时；
public:
	void setblood(int b);
	int getblood(void);
	int b4_blood;
};

