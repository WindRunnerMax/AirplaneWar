#pragma once
#include "GameObject.h"
class Bossbomb6 :
	public CGameObject
{
public:
	Bossbomb6(int x, int y, int nMontion,int z);
	~Bossbomb6();

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + 10, m_ptPos.y + BOMB_HEIGHT));
	}
private:
	static const int BOMB_HEIGHT = 58;
	static CImageList m_Images;
	int    m_nMotion;
	int z;
};

