#pragma once
#include "GameObject.h"
class Bossbomb :
	public CGameObject
{
public:
	Bossbomb(int x,int y, int nMontion);
	~Bossbomb();

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
};

