#pragma once
#include "gameobject.h"

class Gifts : public CGameObject
{
public:
	~Gifts();
	Gifts(int x,int y,int indexType);
	static BOOL LoadImage();
	BOOL Draw(CDC * pDC, BOOL gPause);
	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + GIFTS_HEIGHT, m_ptPos.y + GIFTS_HEIGHT));
	}
	int getType()
	{
		return type;
	}
private:
	static CImageList m_ImagesHeart;
	static CImageList m_ImagesStar;
	static CImageList m_ImagesDefense;
	static CImageList m_ImagesWeapon;
	static const int GIFTS_HEIGHT = 20;
	int type;
	int m_V;
};

