#include "StdAfx.h"
#include "Defense.h"
#include "Resource.h"

CImageList CShield::m_Images;

CShield::CShield(void)
{
	m_nProcess = 0;
	on = 0;
	w_nWait = 5000;
}

CShield::~CShield(void)
{
}

BOOL CShield::Draw(CDC* pDC, BOOL bPause)
{
	m_Images.Draw(pDC, m_nProcess, m_ptPos, ILD_TRANSPARENT);
	++m_nProcess;
	if (m_nProcess > 14)//循环播放，每到15张
	{
		m_nProcess = 0;//重置图像索引的步进计数
	}
	return true;
}

BOOL CShield::LoadImage()
{
	return CGameObject::LoadImage(m_Images, 169, RGB(0, 0, 0), _WIDTH, _HEIGHT, 1);
}

void CShield::SetPos(int _x, int _y)
{
	m_ptPos.x = _x;
	m_ptPos.y = _y;
}

BOOL CShield::CloseShield(unsigned long long int  Time)//根据系统时间判断
{
	if (Time - st_time > w_nWait)
	{
		on = 0;
		return true;
	}
	return false;
}