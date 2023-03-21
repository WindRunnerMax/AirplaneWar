// PlaneGameView.h : CPlaneGameView 类的接口
//
#include "Defense.h"
#include"MyPlane.h"

#pragma once

class CMyPlane;
class CPlaneGameView : public CView
{
	CShield shield;
	enum ObjType{enEnemy,enBomb,enBall,enExplosion,gifts, enBoss1, enBossbomb1, enBoss2, enBossbomb2, enBoss3, enBossbomb3, enBoss4, enBossbomb4, enBoss5, enBossbomb5, enBossbomb6, enLaser};

protected: // 仅从序列化创建
	CPlaneGameView();
	DECLARE_DYNCREATE(CPlaneGameView)

// 属性
public:
	CPlaneGameDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CPlaneGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	int count;
protected:
	//内存DC
	CDC*        m_pMemDC;
	//设备DC
	CClientDC*  m_pDC;
	//内存位图
	CBitmap*    m_pMemBitmap;


protected:
	//初始化游戏
	BOOL InitGame();
	//结束游戏
	void StopGame();

	//刷新游戏的帧画面
	void UpdateFrame(CDC* pMemDC);


	void AI();

	//获得键的状态1->down
	int GetKey(int nVirtKey)
	{
		return (GetKeyState(nVirtKey) & 0x8000)? 1 : 0;
	}
	
	CMyPlane*  m_pMe;
	CObList    m_ObjList[17];

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:

	int HP; //生命值
	bool vict; //胜利判断
	int nuclearBomp; //核弹
	bool invincible;//无敌
	int pause ;//暂停
	int heart;//生命
	int defenseNum;//防护罩
	int weaponLevel;//武器等级
	int start;
	int bossflag;//boss标志
	int step;//关卡数
	int scores1;//第一个boss产生的触发条件
	int scores2;//第二个
	int scores3;//第三个
	int scores4;//第四个
	int scores5;//第五个
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
	// 创建boss
	void createBoss(void);
	// boss产生子弹
	void bossCreateBomb(void);
	// boss子弹打中战机
	void bossBombHitMyPlane(void);
	// 战机子弹打中boss
	void bombHitBoss(void);
	// boss和战机相撞
	void bossHitMyPlane(void);
	// 创建boss2
	void createBoss2(void);
	// boss2产生子弹
	void boss2CreateBomb(void);
	// boss2子弹打中战机
	void boss2BombHitMyPlane(void);
	// 战机子弹打中boss
	void bombHitBoss2(void);
	// boss和战机相撞
	void boss2HitMyPlane(void);
	// 创建boss3
	void createBoss3(void);
	// boss3产生子弹
	void boss3CreateBomb(void);
	// boss3子弹打中战机
	void bossBomb3HitMyPlane(void);
	// 战机子弹打中boss3
	void bombHitBoss3(void);
	// boss3和战机相撞
	void boss3HitMyPlane(void);
	// 创建boss4
	void createBoss4(void);
	// boss4产生子弹
	void boss4CreateBomb(void);
	// boss4子弹打中战机
	void bossBomb4HitMyPlane(void);
	// 战机子弹打中boss4
	void bombHitBoss4(void);
	// boss4和战机相撞
	void boss4HitMyPlane(void);
	// 创建boss5
	void createBoss5(void);
	// boss5产生子弹
	void boss5CreateBomb(void);
	// boss5子弹打中战机
	void bossBomb5HitMyPlane(void);
	// 战机子弹打中boss5
	void bombHitBoss5(void);
	// boss5和战机相撞
	void boss5HitMyPlane(void);
	// 发射激光
	void createLaser(void);
	// 激光消耗能量
	void LaserReduceEnergy(void);
	// 激光碰撞敌机
	void laserHitEnemy(void);
	// 激光和boss1碰撞
	void laserHitBoss1(void);
	// 激光和boss2相撞
	void laserHitBoss2(void);
	void laserHitBoss3(void);
	// 激光和boss4相撞
	void laserHitBoss4(void);
	// 激光碰撞boss5
	void laserHitboss5(void);
	// boss驱动程序
	void bossDriver(void);
	void passCartoon();
	// bomb6打中战机
	void bossbomb6HitMyPlane(void);
};

#ifndef _DEBUG  // PlaneGameView.cpp 中的调试版本
inline CPlaneGameDoc* CPlaneGameView::GetDocument() const
   { return reinterpret_cast<CPlaneGameDoc*>(m_pDocument); }
#endif

