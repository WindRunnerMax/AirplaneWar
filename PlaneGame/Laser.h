#pragma once
#include "GameObject.h"

class Laser:
	public CGameObject
{
public:
	Laser(int x, int y, int idx);
	~Laser(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + LASER_WIDTH, m_ptPos.y + LASER_HEIGHT));
	}
private:
	static const int LASER_WIDTH = 128;
	static const int LASER_HEIGHT = 512;
	static CImageList m_Images;
	int kind;

};
