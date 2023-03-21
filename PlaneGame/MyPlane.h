#pragma once
#include "GameObject.h"

class CMyPlane :public CGameObject
{
public:
	CMyPlane(void);
	~CMyPlane(void);

	BOOL Draw(CDC* pDC,BOOL bPause);

	static BOOL LoadImage();
	void sety(int);
	void SetHorMotion(double nMotion)
	{
		m_nHorMotion = nMotion;
	}
	double GetHorMotion() const
	{
		return m_nHorMotion;
	}

	void SetVerMotion(double nMotion)
	{
		m_nVerMotion = nMotion;
	}
	double GetVerMotion() const
	{
		return m_nVerMotion;
	}

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+PLANE_WIDTH,m_ptPos.y+PLANE_HEIGHT));
	}

	//�Ƿ���Կ����䵼��
	BOOL Fired();

public:
	static const int PLANE_WIDTH=50;
	static const int PLANE_HEIGHT=60;
private:
	
	static CImageList m_Images;
	double   m_nHorMotion;//�ɻ�ˮƽ���з���0->��ֹ��1->�� -1->��
	double    m_nVerMotion;//�ɻ���ֱ���з���0->��ֹ��1->�� -1->��
	int    m_nWait;//������ʱ
};
