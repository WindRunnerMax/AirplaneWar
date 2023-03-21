// PlaneGameView.h : CPlaneGameView ��Ľӿ�
//
#include "Defense.h"
#include"MyPlane.h"

#pragma once

class CMyPlane;
class CPlaneGameView : public CView
{
	CShield shield;
	enum ObjType{enEnemy,enBomb,enBall,enExplosion,gifts, enBoss1, enBossbomb1, enBoss2, enBossbomb2, enBoss3, enBossbomb3, enBoss4, enBossbomb4, enBoss5, enBossbomb5, enBossbomb6, enLaser};

protected: // �������л�����
	CPlaneGameView();
	DECLARE_DYNCREATE(CPlaneGameView)

// ����
public:
	CPlaneGameDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CPlaneGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	int count;
protected:
	//�ڴ�DC
	CDC*        m_pMemDC;
	//�豸DC
	CClientDC*  m_pDC;
	//�ڴ�λͼ
	CBitmap*    m_pMemBitmap;


protected:
	//��ʼ����Ϸ
	BOOL InitGame();
	//������Ϸ
	void StopGame();

	//ˢ����Ϸ��֡����
	void UpdateFrame(CDC* pMemDC);


	void AI();

	//��ü���״̬1->down
	int GetKey(int nVirtKey)
	{
		return (GetKeyState(nVirtKey) & 0x8000)? 1 : 0;
	}
	
	CMyPlane*  m_pMe;
	CObList    m_ObjList[17];

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:

	int HP; //����ֵ
	bool vict; //ʤ���ж�
	int nuclearBomp; //�˵�
	bool invincible;//�޵�
	int pause ;//��ͣ
	int heart;//����
	int defenseNum;//������
	int weaponLevel;//�����ȼ�
	int start;
	int bossflag;//boss��־
	int step;//�ؿ���
	int scores1;//��һ��boss�����Ĵ�������
	int scores2;//�ڶ���
	int scores3;//������
	int scores4;//���ĸ�
	int scores5;//�����
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void bossBomb6driver(UINT_PTR nIDEvent);

	afx_msg void OnDestroy();
	void drawBackground(CDC * pMemDC);
	void drawHP(CDC * pMemDC);
	void drawTips(CDC * pMemDC);
	void drawMyPlane(CDC * pMemDC);
	void drawOthers(CDC * pMemDC);
	void drawEnemyHP(CDC * pMemDC);
	void creatEnemyPlane();
	void reduceHP();
	void moveMyPlane();
	void creatMyPlaneBullet();
	void creatEnemyBullet();
	void enemyBulletHitMyPlane();
	void crashMyplaneANDEnemy();
	void myPlaneHitEnemyPlane();
	void keyProcessing();
	afx_msg void On32772();
	afx_msg void On32773();
	afx_msg void On32774();
	afx_msg void On32777();
	void drawGiftsCount(CDC * pMemDC);
	void gameInit();
	void myPlaneGetGifts();
	void handleDefense(CDC * pMemDC);
	void welcomeAnsNextLevel(CDC * pMemDC);
	// ����boss
	void createBoss(void);
	// boss�����ӵ�
	void bossCreateBomb(void);
	// boss�ӵ�����ս��
	void bossBombHitMyPlane(void);
	// ս���ӵ�����boss
	void bombHitBoss(void);
	// boss��ս����ײ
	void bossHitMyPlane(void);
	// ����boss2
	void createBoss2(void);
	// boss2�����ӵ�
	void boss2CreateBomb(void);
	// boss2�ӵ�����ս��
	void boss2BombHitMyPlane(void);
	// ս���ӵ�����boss
	void bombHitBoss2(void);
	// boss��ս����ײ
	void boss2HitMyPlane(void);
	// ����boss3
	void createBoss3(void);
	// boss3�����ӵ�
	void boss3CreateBomb(void);
	// boss3�ӵ�����ս��
	void bossBomb3HitMyPlane(void);
	// ս���ӵ�����boss3
	void bombHitBoss3(void);
	// boss3��ս����ײ
	void boss3HitMyPlane(void);
	// ����boss4
	void createBoss4(void);
	// boss4�����ӵ�
	void boss4CreateBomb(void);
	// boss4�ӵ�����ս��
	void bossBomb4HitMyPlane(void);
	// ս���ӵ�����boss4
	void bombHitBoss4(void);
	// boss4��ս����ײ
	void boss4HitMyPlane(void);
	// ����boss5
	void createBoss5(void);
	// boss5�����ӵ�
	void boss5CreateBomb(void);
	// boss5�ӵ�����ս��
	void bossBomb5HitMyPlane(void);
	// ս���ӵ�����boss5
	void bombHitBoss5(void);
	// boss5��ս����ײ
	void boss5HitMyPlane(void);
	// ���伤��
	void createLaser(void);
	// ������������
	void LaserReduceEnergy(void);
	// ������ײ�л�
	void laserHitEnemy(void);
	// �����boss1��ײ
	void laserHitBoss1(void);
	// �����boss2��ײ
	void laserHitBoss2(void);
	void laserHitBoss3(void);
	// �����boss4��ײ
	void laserHitBoss4(void);
	// ������ײboss5
	void laserHitboss5(void);
	// boss��������
	void bossDriver(void);
	void passCartoon();
	// bomb6����ս��
	void bossbomb6HitMyPlane(void);
};

#ifndef _DEBUG  // PlaneGameView.cpp �еĵ��԰汾
inline CPlaneGameDoc* CPlaneGameView::GetDocument() const
   { return reinterpret_cast<CPlaneGameDoc*>(m_pDocument); }
#endif

