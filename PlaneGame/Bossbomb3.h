#pragma once
#include "GameObject.h"
class Bossbomb3 :
	public CGameObject
{
public:
	Bossbomb3(int x, int y, int nMontion,int z);
	~Bossbomb3();

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + 10, m_ptPos.y + BOMB_HEIGHT));
	}
private:
	static const int BOMB_HEIGHT = 59;
	static CImageList m_Images;
	int    m_nMotion;
	int    z;
};

