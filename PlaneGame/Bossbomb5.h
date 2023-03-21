#pragma once
#include "GameObject.h"
class Bossbomb5 :
	public CGameObject
{
public:
	Bossbomb5(int x, int y, int nMontion);
	~Bossbomb5();

	BOOL Draw(CDC* pDC, BOOL bPause); 
	int gettype();

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + 10, m_ptPos.y + BOMB_HEIGHT));
	}


private:
	static const int BOMB_HEIGHT = 60;
	static CImageList m_Images;
	int    m_nMotion;
public:
	int type;
};

