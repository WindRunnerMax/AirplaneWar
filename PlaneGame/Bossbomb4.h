#pragma once
#include "GameObject.h"
class Bossbomb4 :
	public CGameObject
{
public:
	Bossbomb4(int x, int y, int nMontion,int kind);
	~Bossbomb4();

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + 10, m_ptPos.y + BOMB_HEIGHT));
	}
private:
	static const int BOMB_HEIGHT = 60;
	static CImageList m_Images;
	static CImageList m_Images2;
	static CImageList m_Images3;
	static CImageList m_Images4;
	int    m_nMotion;
	int    kind;

};

