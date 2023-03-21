// PlaneGameView.cpp : CPlaneGameView 类的实现
//

#include "stdafx.h"
#include "PlaneGame.h"
#include "gifts.h"
#include "PlaneGameDoc.h"
#include "PlaneGameView.h"
#include "MyPlane.h"
#include "Enemy.h"
#include "Bomb.h"
#include "Ball.h"
#include "Explosion.h"
#include "atlimage.h"
#include "Defense.h"
#include "Boss.h"
#include "Bossbomb.h"
#include "Boss2.h"
#include "Bossbomb2.h"
#include "Boss3.h"
#include "Bossbomb3.h"
#include "Boss4.h"
#include "Bossbomb4.h"
#include "Boss5.h"
#include "Bossbomb5.h"
#include "Bossbomb6.h"
#include "Laser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define BACKGROUND 148
#define BACKGROUNDHEIGHT 1200

unsigned long long int scores=0;
unsigned long long int old_scores = 0;
int status = 1;
int scores1s = 100;
int scores2s = 100;
int scores3s = 100;
int scores4s = 100;
int scores5s = 100;
int zidanok = 1;
// CPlaneGameView

IMPLEMENT_DYNCREATE(CPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()

	ON_WM_DESTROY()
	ON_COMMAND(ID_32772, &CPlaneGameView::On32772)
	ON_COMMAND(ID_32773, &CPlaneGameView::On32773)
	ON_COMMAND(ID_32774, &CPlaneGameView::On32774)
	ON_COMMAND(ID_32777, &CPlaneGameView::On32777)
END_MESSAGE_MAP()

// CPlaneGameView 构造/析构

CPlaneGameView::CPlaneGameView():m_pMe(NULL),count(0)
{
	// TODO: 在此处添加构造代码
	HP=100; //生命值
	vict=0; //胜利判断
	nuclearBomp=3; //核弹
	defenseNum = 3;//防护罩
    invincible=0;//无敌
	pause = 0;//暂停
	heart = 3;//生命值
	weaponLevel = 1;//武器等级
	shield.on = 0; //防护罩
	start = 0;//开始
	step = 1;//关卡数
	bossflag = 0;//boss指针
	scores1 = 200;//boss分数
	scores2 = 400;
	scores3 = 600;
	scores4 = 800;
	scores5 = 1000;
}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPlaneGameView 绘制

void CPlaneGameView::OnDraw(CDC* /*pDC*/)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CPlaneGameView 打印

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CPlaneGameView 诊断

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView 消息处理程序
void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: 在此添加专用代码和/或调用基类
	//初始化游戏
	InitGame();
}

void CPlaneGameView::StopGame()
{
	delete m_pMe;
	delete m_pMemDC;
	delete m_pDC;
	delete m_pMemBitmap;
}

BOOL CPlaneGameView::InitGame()
{
	CRect rc;
	GetClientRect(rc);
	//产生随机数种子
	srand( (unsigned)time( NULL ) );
	//建立设备DC
	m_pDC = new CClientDC(this);

	//建立内存DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//建立内存位图
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);

	//将位图选入内存DC
	m_pMemDC->SelectObject(m_pMemBitmap);

	CMyPlane::LoadImage();
	CEnemy::LoadImage();
	CBomb::LoadImage();
	CBall::LoadImage();
	CExplosion::LoadImage();
	Gifts::LoadImage();
	CShield::LoadImage();
	Boss::LoadImage();
	Bossbomb::LoadImage();
	Boss2::LoadImage();
	Bossbomb2::LoadImage();
	Boss3::LoadImage();
	Bossbomb3::LoadImage();
	Boss4::LoadImage();
	Bossbomb4::LoadImage();
	Boss5::LoadImage();
	Bossbomb5::LoadImage();
	Bossbomb6::LoadImage();
	Laser::LoadImage();

	//产生主角(战机)
	m_pMe = new CMyPlane;

	//启动游戏
	SetTimer(1,30,NULL);
	
	/*if (AfxMessageBox(L"是否查看游戏说明" , MB_YESNO) == 6)  //之前设置提示等
	{
		AfxMessageBox(L"1.WSAD控制战机上下左右移动，J 键发射导弹\n2.F4键暂停，F5键取消暂停\n3.F2键开启无敌，F3关闭无敌");
	}*/
	return TRUE;
}

void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{
	welcomeAnsNextLevel(pMemDC);//绘制welcome && nextLevel //860
	if (pause == 1 || start==0) return;//暂停 
	drawBackground(pMemDC);//绘制滚动背景 //301
	drawTips(pMemDC);//绘制提示 //374
	drawHP(pMemDC);//绘制血量 //342
	drawGiftsCount(pMemDC);//绘制Gifts数量 //718
	drawMyPlane(pMemDC);//绘制战机 //398
	drawOthers(pMemDC);////绘制 导弹、爆炸、敌机、子弹、物品、护盾物品 //416
	handleDefense(pMemDC);//处理防护罩相关 //847
	m_pDC->BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, m_pMemDC, 0, 0, SRCCOPY);
	
}
void CPlaneGameView::AI()
{
	keyProcessing();//处理按键事件 //674
	if (pause == 1 || start == 0 ) return; //暂停
	if (m_pMe == NULL) return;
	creatEnemyPlane();//生成敌机 //453
	moveMyPlane();//移动战机 //486
	creatMyPlaneBullet();//生成战机子弹// 513
	creatEnemyBullet();//生成敌机子弹 //543
	enemyBulletHitMyPlane();//敌机子弹击中战机 //570
	crashMyplaneANDEnemy();//战机与敌机发生碰撞 //597
	myPlaneHitEnemyPlane();//战机击中敌机// 625
	createLaser();//发射激光 //1662
	laserHitEnemy();//激光和敌机相撞 //1674
	myPlaneGetGifts();//战机收获Gifts //816
	bossDriver();//boss驱动程序 //1926
}
void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
	//刷新游戏帧画面: 在内存DC上绘图
	UpdateFrame(m_pMemDC);
	AI();
	bossBomb6driver(nIDEvent);
	CView::OnTimer(nIDEvent);
}
void CPlaneGameView::bossBomb6driver(UINT_PTR nIDEvent)
{
	if (nIDEvent == 2)
	{
		KillTimer(2);
		POSITION b5pos1 = NULL, b5pos2 = NULL;
		Bossbomb5* pBall;
		for (b5pos1 = m_ObjList[enBossbomb5].GetHeadPosition(); (b5pos2 = b5pos1) != NULL;)
		{
			pBall = (Bossbomb5*)m_ObjList[enBossbomb5].GetNext(b5pos1);
			CPoint ePt = pBall->GetPoint();
			m_ObjList[enBossbomb5].RemoveAt(b5pos2);
			for (int i = 0; i < 5; i++)
			{
				m_ObjList[enBossbomb6].AddTail(new Bossbomb6(ePt.x + 50, ePt.y + 50, 1, -i));
				m_ObjList[enBossbomb6].AddTail(new Bossbomb6(ePt.x + 50, ePt.y + 50, 1, 0));
				m_ObjList[enBossbomb6].AddTail(new Bossbomb6(ePt.x + 50, ePt.y + 50, 1, i));
			}
		}
		zidanok = 1;
	}
}


void CPlaneGameView::OnDestroy()
{
	CView::OnDestroy();
	this->StopGame();
	// TODO: 在此处添加消息处理程序代码
}

void CPlaneGameView::drawBackground(CDC* pMemDC)//绘制滚动背景
{
	//绘制天空
	//pMemDC->FillSolidRect(0,0,GAME_WIDTH,GAME_HEIGHT,RGB(84, 142, 239));
	CDC m_MemDc;
	CDC m_cacheDC;
	CBitmap m_BKBmp, m_cacheCBitmap;
	BITMAP m_Bmplnfo;
	CDC *pDc = GetDC();
	if(step==1 )m_BKBmp.LoadBitmapW(IDB_BACKGROUND5);
	else if(step == 2)m_BKBmp.LoadBitmapW(IDB_BACKGROUND6);
	else if(step >= 3) m_BKBmp.LoadBitmapW(IDB_BACKGROUND3);
	m_BKBmp.GetBitmap(&m_Bmplnfo);
	m_MemDc.CreateCompatibleDC(pDc);
	m_MemDc.SelectObject(&m_BKBmp);
	CRect m_CliRect;
	GetClientRect(&m_CliRect);


	//创建缓冲窗口大小（解决刷新闪屏问题）
	m_cacheDC.CreateCompatibleDC(NULL);
	m_cacheCBitmap.CreateCompatibleBitmap(pDc, m_CliRect.Width(), BACKGROUNDHEIGHT);
	m_cacheDC.SelectObject(&m_cacheCBitmap);
	count++;
	//拼接图滑动
	pMemDC->BitBlt(0, 0, m_CliRect.Width(), BACKGROUNDHEIGHT, &m_MemDc, 0, 0, SRCCOPY);  //初始静态图
	pMemDC->BitBlt(0, 0, m_CliRect.Width(), count, &m_MemDc, 0, BACKGROUNDHEIGHT - count, SRCCOPY); //上侧下滑图片
	pMemDC->BitBlt(0, count, m_CliRect.Width(), BACKGROUNDHEIGHT - count, &m_MemDc, 0, 0, SRCCOPY);//下侧下滑图片
	if (count > BACKGROUNDHEIGHT)  count = 0;

	//在绘制完图后，使得窗口有效
	ValidateRect(&m_CliRect);
	//释放缓冲DC
	m_cacheDC.DeleteDC();
	//释放对象
	m_cacheCBitmap.DeleteObject();
	//释放窗口DC
	ReleaseDC(pDc);
}

void CPlaneGameView::drawHP(CDC *pMemDC)//绘制血量
{
	pMemDC->SetTextAlign(TA_LEFT);

	//绘制血条
	if (m_pMe != NULL)
	{
		CString HPTips;
		if (HP >= 60)
		{
			pMemDC->SetTextColor(RGB(0, 255, 0));
			HPTips.Format(L"战机HP（%d）", HP);
			pMemDC->TextOut(7, 30, HPTips);
			pMemDC->FillSolidRect(5, 50, HP, 10, RGB(0, 255, 0));
		}
		else if (HP >= 30)
		{
			pMemDC->SetTextColor(RGB(255, 255, 0));
			HPTips.Format(L"战机HP（%d）", HP);
			pMemDC->TextOut(7, 30, HPTips);
			pMemDC->FillSolidRect(5, 50, HP, 10, RGB(255, 255, 0));
		}
		else
		{
			pMemDC->SetTextColor(RGB(234, 032, 0));
			HPTips.Format(L"战机HP（%d）", HP);
			pMemDC->TextOut(7, 30, HPTips);
			pMemDC->FillSolidRect(5, 50, HP, 10, RGB(234, 032, 0));
		}
	}
}

void CPlaneGameView::drawTips(CDC * pMemDC)//绘制左上角提示
{
	CRect m_CliRect;
	GetClientRect(&m_CliRect);
	pMemDC->SetTextAlign(TA_LEFT);
	CString scoresTips;
	scoresTips.Format(L"得分 ：%llu", scores);
	pMemDC->SetTextColor(RGB(255, 0, 0));
	pMemDC->TextOut(7,6,scoresTips);

	CString missionTips;
	missionTips.Format(L"MISSION %d", step);
	pMemDC->SetTextColor(RGB(255, 255,255));
	pMemDC->TextOut(260, 10, missionTips);

	if (invincible == 1)
	{
		pMemDC->SetTextAlign(TA_RIGHT);
		pMemDC->SetTextColor(RGB( 0, 255, 0));
		pMemDC->TextOut(m_CliRect.Width()-5, m_CliRect.Height()-20,L"无敌模式开启");
	}
	
}

void CPlaneGameView::drawMyPlane(CDC * pMemDC)//绘制战机
{
	if (m_pMe != NULL)
	{
		m_pMe->Draw(m_pMemDC, FALSE);
	} else {   //Game Over
		CString str = _T("Game Over!");
		CString sstr = _T("按回车键重新开始");
		pMemDC->SetBkMode(TRANSPARENT);
		pMemDC->SetTextAlign(TA_CENTER);
		pMemDC->SetTextColor(RGB(255, 255, 0));
		pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2, str);
		pMemDC->TextOut(GAME_WIDTH / 2, GAME_HEIGHT / 2 + 20, sstr);
		//restart
		if (GetKey(VK_RETURN) == 1) gameInit();
	}
}

void CPlaneGameView::drawOthers(CDC * pMemDC)//绘制 导弹、爆炸、敌机、子弹、物品、护盾物品
{
	for (int i = 0; i<17; i++)
	{
		POSITION pos1, pos2;
		for (pos1 = m_ObjList[i].GetHeadPosition(); (pos2 = pos1) != NULL; )
		{
			CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext(pos1);
			if (!pObj->Draw(pMemDC, FALSE))
			{
				m_ObjList[i].RemoveAt(pos2);
				delete pObj;
			}
		}
	}
}

void CPlaneGameView::drawEnemyHP(CDC * pMemDC)//绘制敌机血条//已在敌机类中实现
{

	for (POSITION ePos = m_ObjList[enEnemy].GetHeadPosition(); ePos != NULL;)
	{
		CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
		CPoint  ePt = pEnemy->GetPoint();
			//m_ObjList[enBall].AddTail(new CBall(ePt.x + 10, ePt.y + 10, pEnemy->GetMontion()));

		pMemDC->SetTextAlign(TA_LEFT);

		//绘制血条
		if (pEnemy != NULL)
		{
			pMemDC->FillSolidRect(ePt.x + 2, ePt.y - 6, 30, 2, RGB(255, 0, 0));
			pMemDC->FillSolidRect(ePt.x+2, ePt.y-6, pEnemy->enemyHP, 2, RGB(0, 255, 0));
		}
	}
	
}
void CPlaneGameView::creatEnemyPlane()//生成敌机
{
	static int nCreator = rand() % 10 + 15;

	//随机产生敌机
	if (nCreator <= 0)
	{
		nCreator = rand() % 10 + 18;
		m_ObjList[enEnemy].AddTail(new CEnemy);
	}
	nCreator--;

	
}

void CPlaneGameView::reduceHP() //生命值减少
{
	if (invincible == 1 || shield.on == 1) return;
	HP -= 10;
	if(heart>0 && HP<=0)
	{
		--heart;
		HP += 100;
		shield.on = 1;
		shield.st_time = GetTickCount64();//记录时间
	}
	if (HP <= 0)
	{
		delete m_pMe;
		m_pMe = NULL;
	}
}

void CPlaneGameView::moveMyPlane()//移动战机
{
	//检测四个方向键，移动战机
	for (int i = 0; i<4; i++)
	{
		int nMeMotion = 0;
		m_pMe->SetVerMotion(0);
		m_pMe->SetHorMotion(0);

		nMeMotion = GetKey(87);
		if (nMeMotion == 1)
			m_pMe->SetVerMotion(1.5);

		nMeMotion = GetKey(83);
		if (nMeMotion == 1)
			m_pMe->SetVerMotion(-1.5);

		nMeMotion = GetKey(68);
		if (nMeMotion == 1)
			m_pMe->SetHorMotion(1.5);

		nMeMotion = GetKey(65);
		if (nMeMotion == 1)
			m_pMe->SetHorMotion(-1.5);
	}
}

void CPlaneGameView::creatMyPlaneBullet()//生成战机子弹
{
	if (GetKey(74) == 1)//按下了J键
	{
		if (m_pMe != NULL && m_pMe->Fired())
		{
			CPoint pt = m_pMe->GetPoint();
			if (weaponLevel % 2)
			{
				m_ObjList[enBomb].AddTail(new CBomb(pt.x + 20, pt.y + 10, 0));
				if (weaponLevel >= 3)
				{
					m_ObjList[enBomb].AddTail(new CBomb(pt.x + 10, pt.y + 10, 0));
					m_ObjList[enBomb].AddTail(new CBomb(pt.x + 30, pt.y + 10, 0));
				}
			}
			else
			{
					m_ObjList[enBomb].AddTail(new CBomb(pt.x + 10, pt.y + 10, 0));
					m_ObjList[enBomb].AddTail(new CBomb(pt.x + 30, pt.y + 10, 0));
				if (weaponLevel == 4)
				{
					m_ObjList[enBomb].AddTail(new CBomb(pt.x, pt.y + 10, 1));
					m_ObjList[enBomb].AddTail(new CBomb(pt.x + 40, pt.y + 10, -1));
				}
			}
		}
	}
}

void CPlaneGameView::creatEnemyBullet()//生成敌机子弹
{
	if (m_pMe == NULL) return;
	CPoint PlanePt = m_pMe->GetPoint();
	for (POSITION ePos = m_ObjList[enEnemy].GetHeadPosition(); ePos != NULL;)
	{
		CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
		if (!pEnemy->Fired())
			continue;
		CPoint  ePt = pEnemy->GetPoint();

		BOOL by = FALSE;

		//敌机在战机前面
		if (pEnemy->GetMontion() == 1 && ePt.y<PlanePt.y)
			by = TRUE;
		//敌机在战机后面
		if (pEnemy->GetMontion() == -1 && ePt.y>PlanePt.y)
			by = TRUE;

		if (by && ePt.x >= PlanePt.x && ePt.x<PlanePt.x + CMyPlane::PLANE_WIDTH)
		{
			m_ObjList[enBall].AddTail(new CBall(ePt.x + 10, ePt.y + 10, pEnemy->GetMontion()));
		}
	}
}

void CPlaneGameView::enemyBulletHitMyPlane()//敌机子弹击中战机
{
	if (m_pMe == NULL) return;
	POSITION bPos1 = NULL, bPos2 = NULL;
	CRect mRect = m_pMe->GetRect();
	for (bPos1 = m_ObjList[enBall].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
	{
		CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
		CRect bRect = pBall->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&bRect, mRect))
		{
			//添加爆炸效果
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left, mRect.top)
				);

			//删除子弹
			m_ObjList[enBall].RemoveAt(bPos2);
			delete pBall;

			reduceHP();
			break;
		}
	}
}

void CPlaneGameView::crashMyplaneANDEnemy()//战机与敌机碰撞
{
	if (m_pMe == NULL) return;
	POSITION ePosp1 = NULL, ePosp2 = NULL;
	CRect mRect = m_pMe->GetRect();
	for (ePosp1 = m_ObjList[enEnemy].GetHeadPosition(); (ePosp2 = ePosp1) != NULL;)
	{
		CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePosp1);
		CRect eRectp = pEnemy->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&eRectp, mRect))
		{
			//添加爆炸效果
			m_ObjList[enExplosion].AddTail(
				new CExplosion(mRect.left, mRect.top)
				);

			//删除子弹
			m_ObjList[enEnemy].RemoveAt(ePosp2);
			delete pEnemy;

			reduceHP();
			break;

		}
	}
}

void CPlaneGameView::myPlaneHitEnemyPlane()//战机击中敌机
{
	if (m_pMe == NULL) return;
	POSITION mPos1 = NULL, mPos2 = NULL;
	for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		CRect bRect = pBomb->GetRect();

		POSITION ePos1 = NULL, ePos2 = NULL;
		for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
			CRect mRectm = pEnemy->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRectm))
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRectm.left, mRectm.top)
					);
				//删除导弹
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;

				pEnemy->enemyHP -= 10;
				if (pEnemy->enemyHP <= 0)
				{
					scores += 10;
					//删除敌机
					m_ObjList[enEnemy].RemoveAt(ePos2);
					delete pEnemy;
					int giftType = rand() % 70;
					if (giftType <= 1)
						m_ObjList[gifts].AddTail(new  Gifts(bRect.left - 10, bRect.top - 10, 1)); //生命
					else if (giftType <= 3)
						m_ObjList[gifts].AddTail(new  Gifts(bRect.left - 10, bRect.top - 10, 2)); //核弹
					else if (giftType <= 5)
						m_ObjList[gifts].AddTail(new  Gifts(bRect.left - 10, bRect.top - 10, 3)); //保护罩
					else if(giftType <= (9-weaponLevel))
						m_ObjList[gifts].AddTail(new  Gifts(bRect.left - 10, bRect.top - 10, 4)); //武器升级
				}
				break;

			}
		}
	}
}

void CPlaneGameView::keyProcessing()
{
	if (GetKey(70) == 1) start = 1;
	if (start == 0) return;
	if (GetKey(73) == 1)  invincible = 1;
	if (GetKey(79) == 1) invincible = 0;
	if (GetKey(78) == 1) pause = 1;
	if (GetKey(77) == 1) pause = 0;
	if (defenseNum>0 && GetKey(85) == 1 && shield.on == 0)
	{
		shield.on = 1;
		shield.st_time = GetTickCount64();//记录时间
		--defenseNum;
	}
	if (GetKey(70) == 1) start = 1;
}


void CPlaneGameView::On32772()
{
	// TODO: 在此添加命令处理程序代码
	invincible = 1;
}


void CPlaneGameView::On32773()
{
	// TODO: 在此添加命令处理程序代码
	invincible = 0;
}


void CPlaneGameView::On32774()
{
	// TODO: 在此添加命令处理程序代码
	pause = 1;
}


void CPlaneGameView::On32777()
{
	// TODO: 在此添加命令处理程序代码
	gameInit();
}
void CPlaneGameView::drawGiftsCount(CDC * pMemDC) //绘制Gifts数量
{
	if (m_pMe == nullptr) return;
	int k = 555;
	for (int i = 1; i <= heart; i++)
	{
		CDC memDC;
		memDC.CreateCompatibleDC(m_pMemDC);
		CBitmap bmpDraw;
		bmpDraw.LoadBitmapW(164);
		CBitmap*pbmpOld = memDC.SelectObject(&bmpDraw);
		m_pMemDC->TransparentBlt(k, 10, 30, 30, &memDC, 0, 0, 35, 35, RGB(255 ,255, 255));
		k -=40;
		memDC.SelectObject(pbmpOld);
	}

	CRect m_CliRect;
	GetClientRect(&m_CliRect);

	CDC memDCS;
	memDCS.CreateCompatibleDC(m_pMemDC);
	CBitmap bmpDrawS;
	bmpDrawS.LoadBitmapW(165);
	CBitmap*pbmpOldS = memDCS.SelectObject(&bmpDrawS);
	m_pMemDC->TransparentBlt(3, m_CliRect.Height() - 109, 30, 30, &memDCS, 0, 0, 35, 35, RGB(255, 255, 255));

	CDC memDCD;
	memDCD.CreateCompatibleDC(m_pMemDC);
	CBitmap bmpDrawD;
	bmpDrawD.LoadBitmapW(167);
	CBitmap*pbmpOldD = memDCD.SelectObject(&bmpDrawD);
	m_pMemDC->TransparentBlt(3, m_CliRect.Height() - 73, 30, 30, &memDCD, 0, 0, 30, 30, RGB(0, 0, 0));

	CDC memDCW;
	memDCW.CreateCompatibleDC(m_pMemDC);
	CBitmap bmpDrawW;
	bmpDrawW.LoadBitmapW(178);
	CBitmap*pbmpOldW = memDCW.SelectObject(&bmpDrawW);
	m_pMemDC->TransparentBlt(3, m_CliRect.Height() - 37, 30, 30, &memDCW, 0, 0, 32, 30, RGB(0, 0, 0));

	pMemDC->SetTextAlign(TA_LEFT);
	CString nuclearBompTips;
	nuclearBompTips.Format(L"%d", nuclearBomp);
	pMemDC->SetTextColor(RGB(255, 255, 255));
	pMemDC->TextOut(37, m_CliRect.Height() - 102, nuclearBompTips);
	CString defenseNumTips;
	defenseNumTips.Format(L"%d", defenseNum);
	pMemDC->TextOut(37, m_CliRect.Height() - 67, defenseNumTips);
	CString weaponLevelTips;
	weaponLevelTips.Format(L"%d", weaponLevel);
	pMemDC->TextOut(37, m_CliRect.Height() - 30, weaponLevelTips);
}

void CPlaneGameView::gameInit()//重新开始游戏
{
	delete m_pMe;
	m_pMe = new CMyPlane;
	m_pMe->Draw(m_pMemDC, FALSE);
	m_ObjList[enBall].RemoveAll();
	m_ObjList[enBomb].RemoveAll();
	m_ObjList[enEnemy].RemoveAll();
	m_ObjList[enExplosion].RemoveAll();
	switch(bossflag)
	{
		case 1:
			m_ObjList[enBoss1].RemoveAll();
			m_ObjList[enBossbomb1].RemoveAll();
			break;
		case 2:
			m_ObjList[enBoss2].RemoveAll();
			m_ObjList[enBossbomb2].RemoveAll();
			break;
		case 3:
			m_ObjList[enBoss3].RemoveAll();
			m_ObjList[enBossbomb3].RemoveAll();
			break;
		case 4:
			m_ObjList[enBoss4].RemoveAll();
			m_ObjList[enBossbomb4].RemoveAll();
			break;
		case 5:
			m_ObjList[enBoss5].RemoveAll();
			m_ObjList[enBossbomb5].RemoveAll();
			m_ObjList[enBossbomb6].RemoveAll();
			break;
	}
	bossflag = 0;
	HP = 100;
	scores = 0;
	old_scores = 0;
	heart = 3;
	status = 1;
	weaponLevel = 1;
	step = 1;
	nuclearBomp=3; //核弹
	defenseNum = 3;//防护罩
	start=1;
}

void CPlaneGameView::myPlaneGetGifts()
{
	if (m_pMe == NULL) return;
	POSITION ePosp1 = NULL, ePosp2 = NULL;
	CRect mRect = m_pMe->GetRect();
	for (ePosp1 = m_ObjList[gifts].GetHeadPosition(); (ePosp2 = ePosp1) != NULL;)
	{
		Gifts* myGift = (Gifts*)m_ObjList[gifts].GetNext(ePosp1);
		CRect eRectp = myGift->GetRect();
		CRect tmpRect;
		if (tmpRect.IntersectRect(&eRectp, mRect))
		{
			int Giftstype = myGift->getType();
			if (Giftstype == 1)
			{
				if( heart < 3) ++heart;
				else HP = 100;
			}
			else if (Giftstype == 2) nuclearBomp++;
			else if (Giftstype == 3) defenseNum++;
			else if (Giftstype == 4 && weaponLevel<4) weaponLevel++;

			//删除gifts
			m_ObjList[gifts].RemoveAt(ePosp2);
			delete myGift;
			break;

		}
	}
}

void CPlaneGameView::handleDefense(CDC* pMemDC) //处理防护罩相关
{
	if (shield.on)
	{
		shield.SetPos(m_pMe->GetPoint().x - 73, m_pMe->GetPoint().y - 70);
		shield.Draw(pMemDC, TRUE);
		shield.CloseShield(GetTickCount64());
	}
}

void CPlaneGameView::welcomeAnsNextLevel(CDC* pMemDC)
{
		pMemDC->SetBkMode(TRANSPARENT);
		if (start == 1) return;
		CDC m_MemDc;
		CDC m_cacheDC;
		CBitmap m_BKBmp, m_cacheCBitmap;
		BITMAP m_Bmplnfo;
		CDC *pDc = GetDC();
		if(step==1 )m_BKBmp.LoadBitmapW(179);
		else m_BKBmp.LoadBitmapW(196);
		m_BKBmp.GetBitmap(&m_Bmplnfo);
		m_MemDc.CreateCompatibleDC(pDc);
		m_MemDc.SelectObject(&m_BKBmp);
		CRect m_CliRect;
		GetClientRect(&m_CliRect);


		//创建缓冲窗口大小（解决刷新闪屏问题）
		m_cacheDC.CreateCompatibleDC(NULL);
		m_cacheCBitmap.CreateCompatibleBitmap(pDc, m_CliRect.Width(),m_CliRect.Height());
		m_cacheDC.SelectObject(&m_cacheCBitmap);

		pMemDC->BitBlt(0, 0, m_CliRect.Width(),m_CliRect.Height(), &m_MemDc, 0, 0, SRCCOPY);  

		//在绘制完图后，使得窗口有效
		ValidateRect(&m_CliRect);
		//释放缓冲DC
		m_cacheDC.DeleteDC();
		//释放对象
		m_cacheCBitmap.DeleteObject();
		//释放窗口DC
		ReleaseDC(pDc);

		m_pMe->sety(600);

		if (step != 1)
		{
			if(step==4)
			{
				CString levelTips;
			levelTips.Format(L"FINAL MISSION  COMPLETE !", step-1);
			pMemDC->SetTextColor(RGB(255, 255, 255));
			pMemDC->TextOut(190, 220, levelTips);
			CString sscoresTips;
			sscoresTips.Format(L"得分： %llu", scores);
			pMemDC->SetTextColor(RGB(255, 255, 255));
			pMemDC->TextOut(270, 260, sscoresTips);
			CString initTips;
			initTips.Format(L"按回车键重新开始游戏");
			pMemDC->SetTextColor(RGB(255, 255, 255));
			pMemDC->TextOut(210, 300, initTips);
			if (GetKey(VK_RETURN) == 1) gameInit();
			}
			else
			{
			CString levelTips;
			levelTips.Format(L"MISSION %d  COMPLETE !", step-1);
			pMemDC->SetTextColor(RGB(255, 255, 255));
			pMemDC->TextOut(230, 220, levelTips);
			CString sscoresTips;
			sscoresTips.Format(L"得分： %llu", scores);
			pMemDC->SetTextColor(RGB(255, 255, 255));
			pMemDC->TextOut(270, 260, sscoresTips);
			}
		}
		m_pDC->BitBlt(0, 0, GAME_WIDTH, GAME_HEIGHT, m_pMemDC, 0, 0, SRCCOPY);
}


// 创建boss
void CPlaneGameView::createBoss(void)
{
	if (m_pMe != NULL && scores-old_scores >= scores1s)
	{
		bossflag = 1;
		m_ObjList[enBoss1].AddTail(new Boss);
	}
}


// boss产生子弹
void CPlaneGameView::bossCreateBomb(void)
{
	//Boss1发射子弹
	for (POSITION ePos = m_ObjList[enBoss1].GetHeadPosition(); ePos != NULL;)
	{
		Boss* pBoss = (Boss*)m_ObjList[enBoss1].GetNext(ePos);
		if (!pBoss->Fired())
			continue;
		CPoint  ePt = pBoss->GetPoint();

		m_ObjList[enBossbomb1].AddTail(new Bossbomb(ePt.x + 10, ePt.y + 10, pBoss->GetMontion()));
		m_ObjList[enBossbomb1].AddTail(new Bossbomb(ePt.x + 53, ePt.y + 10, pBoss->GetMontion()));
		m_ObjList[enBossbomb1].AddTail(new Bossbomb(ePt.x + 97, ePt.y + 10, pBoss->GetMontion()));
	}
}

// boss子弹打中战机
void CPlaneGameView::bossBombHitMyPlane(void)
{
	//Boss1子弹和战机碰撞
	POSITION bb1Pos1 = NULL, bb1Pos2 = NULL;
	if (m_pMe != NULL)
	{
		CRect mb1Rect = m_pMe->GetRect();
		for (bb1Pos1 = m_ObjList[enBossbomb1].GetHeadPosition(); (bb1Pos2 = bb1Pos1) != NULL;)
		{
			Bossbomb* pBossbomb = (Bossbomb*)m_ObjList[enBossbomb1].GetNext(bb1Pos1);
			CRect bRect = pBossbomb->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mb1Rect))
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mb1Rect.left, mb1Rect.top)
					);
				//删除子弹
				m_ObjList[enBossbomb1].RemoveAt(bb1Pos2);
				delete pBossbomb;
				reduceHP();
			}
		}
	}
}

//战机子弹打中boss
void CPlaneGameView::bombHitBoss(void)
{
	POSITION nPos1 = NULL, nPos2 = NULL;
	if (m_pMe != NULL)
	{
		for (nPos1 = m_ObjList[enBomb].GetHeadPosition(); (nPos2 = nPos1) != NULL;)
		{
			CBomb* nBomb = (CBomb*)m_ObjList[enBomb].GetNext(nPos1);
			CRect bRect = nBomb->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enBoss1].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				Boss* pBoss = (Boss*)m_ObjList[enBoss1].GetNext(ePos1);
				CRect nRect = pBoss->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, nRect))
				{
					pBoss->setblood(10);
					//添加爆炸效果
					m_ObjList[enExplosion].AddTail(
						new CExplosion(bRect.left, bRect.top)
						);
					//删除导弹
					m_ObjList[enBomb].RemoveAt(nPos2);
					delete nBomb;

					//删除boss
					if (pBoss->blood <= 0)
					{
						scores += scores1;
						++status;
						old_scores = scores;
						m_ObjList[enBoss1].RemoveAt(ePos2);
						delete pBoss;
						bossflag = 0;
					}
					break;
				}
			}
		}
	}
}

// boss和战机相撞
void CPlaneGameView::bossHitMyPlane(void)
{
	POSITION bPosboss1 = NULL, bPosboss2 = NULL;
	if (m_pMe != NULL)
	{
		CRect aRect = m_pMe->GetRect();
		for (bPosboss1 = m_ObjList[enBoss1].GetHeadPosition(); (bPosboss2 = bPosboss1) != NULL;)
		{
			Boss* pBoss = (Boss*)m_ObjList[enBoss1].GetNext(bPosboss1);
			CRect bRect = pBoss->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, aRect))
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(aRect.left, aRect.top)
					);
				pBoss->setblood(10);
				reduceHP();
				//删除boss
				if (pBoss->blood <= 0)
				{
					scores += scores1;
					old_scores = scores;
					++status;
					m_ObjList[enBoss1].RemoveAt(bPosboss2);
					delete pBoss;
					bossflag = 0;
					break;
				}
			}
		}
	}
}

// 创建boss2
void CPlaneGameView::createBoss2(void)
{
	if (m_pMe != NULL && scores-old_scores > scores2s)
	{
		bossflag = 2;
		m_ObjList[enBoss2].AddTail(new Boss2);
	}
}


// boss2产生子弹
void CPlaneGameView::boss2CreateBomb(void)
{
	if (m_pMe == NULL) return;
	CPoint pt2 = m_pMe->GetPoint();
	for (POSITION ePos = m_ObjList[enBoss2].GetHeadPosition(); ePos != NULL;)
	{
		Boss2* pBoss = (Boss2*)m_ObjList[enBoss2].GetNext(ePos);
		if (!pBoss->Fired()) continue;
		CPoint  ePt = pBoss->GetPoint();

		m_ObjList[enBossbomb2].AddTail(new Bossbomb2(ePt.x + 10, ePt.y + 10, pt2.x - ePt.x, pt2.y - ePt.y, pBoss->GetMontion()));
		m_ObjList[enBossbomb2].AddTail(new Bossbomb2(ePt.x + 30, ePt.y + 10, pt2.x - ePt.x, pt2.y - ePt.y, pBoss->GetMontion()));
		m_ObjList[enBossbomb2].AddTail(new Bossbomb2(ePt.x + 50, ePt.y + 10, pt2.x - ePt.x, pt2.y - ePt.y, pBoss->GetMontion()));
		m_ObjList[enBossbomb2].AddTail(new Bossbomb2(ePt.x + 70, ePt.y + 10, pt2.x - ePt.x, pt2.y - ePt.y, pBoss->GetMontion()));
		m_ObjList[enBossbomb2].AddTail(new Bossbomb2(ePt.x +90, ePt.y + 10, pt2.x - ePt.x, pt2.y - ePt.y, pBoss->GetMontion()));
	}
}


// boss2子弹打中战机
void CPlaneGameView::boss2BombHitMyPlane(void)
{
	POSITION bb2Pos1 = NULL, bb2Pos2 = NULL;
	if (m_pMe != NULL)
	{
		CRect mb2Rect = m_pMe->GetRect();
		for (bb2Pos1 = m_ObjList[enBossbomb2].GetHeadPosition(); (bb2Pos2 = bb2Pos1) != NULL;)
		{
			Bossbomb2* pBossbomb = (Bossbomb2*)m_ObjList[enBossbomb2].GetNext(bb2Pos1);
			CRect bRect = pBossbomb->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mb2Rect))
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mb2Rect.left, mb2Rect.top)
					);

				//删除子弹
				m_ObjList[enBossbomb2].RemoveAt(bb2Pos2);
				delete pBossbomb;
				reduceHP();
			}
		}
	}
}


// 战机子弹打中boss2
void CPlaneGameView::bombHitBoss2(void)
{
	POSITION b2Pos1 = NULL, b2Pos2 = NULL;
	if (m_pMe != NULL)
	{
		for (b2Pos1 = m_ObjList[enBomb].GetHeadPosition(); (b2Pos2 = b2Pos1) != NULL;)
		{
			CBomb* nBomb = (CBomb*)m_ObjList[enBomb].GetNext(b2Pos1);
			CRect bRect = nBomb->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enBoss2].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				Boss2* pBoss = (Boss2*)m_ObjList[enBoss2].GetNext(ePos1);
				CRect nRect = pBoss->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, nRect))
				{
					pBoss->setblood(10);
					//添加爆炸效果
					m_ObjList[enExplosion].AddTail(
						new CExplosion(bRect.left, bRect.top)
						);
					//删除导弹
					m_ObjList[enBomb].RemoveAt(b2Pos2);
					delete nBomb;

					//删除boss2
					if (pBoss->b2_blood <= 0)
					{
						scores += scores2;
						old_scores = scores;
						++status;
						m_ObjList[enBoss2].RemoveAt(ePos2);
						delete pBoss;
						bossflag = 0;
					}
					break;
				}
			}
		}
	}
}


// boss2和战机相撞
void CPlaneGameView::boss2HitMyPlane(void)
{
	POSITION b2Posboss1 = NULL, b2Posboss2 = NULL;
	if (m_pMe != NULL)
	{
		CRect b2Rect = m_pMe->GetRect();
		for (b2Posboss1 = m_ObjList[enBoss2].GetHeadPosition(); (b2Posboss2 = b2Posboss1) != NULL;)
		{
			Boss2* pBoss = (Boss2*)m_ObjList[enBoss2].GetNext(b2Posboss1);
			CRect bRect = pBoss->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, b2Rect))
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(b2Rect.left, b2Rect.top)
					);
				pBoss->setblood(10);
				reduceHP();
				//删除boss2
				if (pBoss->b2_blood <= 0)
				{
					scores += scores2;
					old_scores = scores;
					++status;
					m_ObjList[enBoss2].RemoveAt(b2Posboss2);
					delete pBoss;
					bossflag = 0;
					break;
				}
			}
		}
	}
}


// 创建boss3
void CPlaneGameView::createBoss3(void)
{
	if (m_pMe != NULL && scores-old_scores >= scores3s)
	{
		bossflag = 3;
		m_ObjList[enBoss3].AddTail(new Boss3);
	}
}


// boss3产生子弹
void CPlaneGameView::boss3CreateBomb(void)
{
	for (POSITION ePos = m_ObjList[enBoss3].GetHeadPosition(); ePos != NULL;)
	{
		Boss3* pBoss = (Boss3*)m_ObjList[enBoss3].GetNext(ePos);
		if (!pBoss->Fired())	continue;
		CPoint  ePt = pBoss->GetPoint();
		for (int i = 0; i < 3; i++)
		{
			m_ObjList[enBossbomb3].AddTail(new Bossbomb3(ePt.x + 50, ePt.y + 50, pBoss->GetMontion(), -i));
			m_ObjList[enBossbomb3].AddTail(new Bossbomb3(ePt.x + 50, ePt.y + 50, pBoss->GetMontion(), 0));
			m_ObjList[enBossbomb3].AddTail(new Bossbomb3(ePt.x + 50, ePt.y + 50, pBoss->GetMontion(), i));
		}
	}
}


// boss3子弹打中战机
void CPlaneGameView::bossBomb3HitMyPlane(void)
{
	POSITION bb3Pos1 = NULL, bb3Pos2 = NULL;
	if (m_pMe != NULL)
	{
		CRect mb3Rect = m_pMe->GetRect();
		for (bb3Pos1 = m_ObjList[enBossbomb3].GetHeadPosition(); (bb3Pos2 = bb3Pos1) != NULL;)
		{
			Bossbomb3* pBossbomb = (Bossbomb3*)m_ObjList[enBossbomb3].GetNext(bb3Pos1);
			CRect bRect = pBossbomb->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mb3Rect))
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mb3Rect.left, mb3Rect.top)
					);

				//删除子弹
				m_ObjList[enBossbomb3].RemoveAt(bb3Pos2);
				delete pBossbomb;
				reduceHP();
			}
		}
	}
}


// 战机子弹打中boss3
void CPlaneGameView::bombHitBoss3(void)
{
	POSITION b3Pos1 = NULL, b3Pos2 = NULL;
	if (m_pMe != NULL)
	{
		for (b3Pos1 = m_ObjList[enBomb].GetHeadPosition(); (b3Pos2 = b3Pos1) != NULL;)
		{
			CBomb* nBomb = (CBomb*)m_ObjList[enBomb].GetNext(b3Pos1);
			CRect bRect = nBomb->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enBoss3].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				Boss3* pBoss = (Boss3*)m_ObjList[enBoss3].GetNext(ePos1);
				CRect nRect = pBoss->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, nRect))
				{
					pBoss->setblood(10);
					//添加爆炸效果
					m_ObjList[enExplosion].AddTail(
						new CExplosion(bRect.left, bRect.top)
						);
					//删除导弹
					m_ObjList[enBomb].RemoveAt(b3Pos2);
					delete nBomb;

					//删除boss
					if (pBoss->b3_blood <= 0)
					{
						scores += scores3;
						old_scores = scores;
						m_ObjList[enBoss3].RemoveAt(ePos2);
						delete pBoss;
						bossflag = 0;
						step = 2;
						++status;
						passCartoon();
						return;
					}
					break;
				}
			}
		}
	}
}


// boss3和战机相撞
void CPlaneGameView::boss3HitMyPlane(void)
{
	POSITION b3Posboss1 = NULL, b3Posboss2 = NULL;
	if (m_pMe != NULL)
	{
		CRect b3Rect = m_pMe->GetRect();
		for (b3Posboss1 = m_ObjList[enBoss3].GetHeadPosition(); (b3Posboss2 = b3Posboss1) != NULL;)
		{
			Boss3* pBoss = (Boss3*)m_ObjList[enBoss3].GetNext(b3Posboss1);
			CRect bRect = pBoss->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, b3Rect))
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(b3Rect.left, b3Rect.top)
					);
				pBoss->setblood(10);
				reduceHP();
				//删除boss
				if (pBoss->b3_blood <= 0)
				{
					scores += scores3;
					old_scores = scores;
					m_ObjList[enBoss3].RemoveAt(b3Posboss2);
					delete pBoss;
					bossflag = 0;
					step = 2;
					++status;
					passCartoon();
					return;
				}
			}
		}
	}
}

// 创建boss4
void CPlaneGameView::createBoss4(void)
{
	if (m_pMe != NULL&&scores-old_scores >= scores4s)
	{
		bossflag = 4;
		m_ObjList[enBoss4].AddTail(new Boss4);
	}
}

// boss4产生子弹
void CPlaneGameView::boss4CreateBomb(void)
{
	for (POSITION ePos = m_ObjList[enBoss4].GetHeadPosition(); ePos != NULL;)
	{
		Boss4* pBoss = (Boss4*)m_ObjList[enBoss4].GetNext(ePos);
		if (!pBoss->Fired())	continue;
		CPoint  ePt = pBoss->GetPoint();
		m_ObjList[enBossbomb4].AddTail(new Bossbomb4(ePt.x + 10, ePt.y, pBoss->GetMontion(), 4));
		m_ObjList[enBossbomb4].AddTail(new Bossbomb4(ePt.x + 140, ePt.y, pBoss->GetMontion(), 2));
		m_ObjList[enBossbomb4].AddTail(new Bossbomb4(ePt.x + 30, ePt.y + 30, pBoss->GetMontion(), 1));
		m_ObjList[enBossbomb4].AddTail(new Bossbomb4(ePt.x + 60, ePt.y + 30, pBoss->GetMontion(), 1));
		m_ObjList[enBossbomb4].AddTail(new Bossbomb4(ePt.x + 90, ePt.y + 30, pBoss->GetMontion(), 1));
		m_ObjList[enBossbomb4].AddTail(new Bossbomb4(ePt.x + 30, ePt.y + 10, pBoss->GetMontion(), 3));
		m_ObjList[enBossbomb4].AddTail(new Bossbomb4(ePt.x + 60, ePt.y + 10, pBoss->GetMontion(), 3));
		m_ObjList[enBossbomb4].AddTail(new Bossbomb4(ePt.x + 90, ePt.y + 10, pBoss->GetMontion(), 3));
	}
}


// boss4子弹打中战机
void CPlaneGameView::bossBomb4HitMyPlane(void)
{
	POSITION bb4Pos1 = NULL, bb4Pos2 = NULL;
	if (m_pMe != NULL)
	{
		CRect mb4Rect = m_pMe->GetRect();
		for (bb4Pos1 = m_ObjList[enBossbomb4].GetHeadPosition(); (bb4Pos2 = bb4Pos1) != NULL;)
		{
			Bossbomb4* pBossbomb = (Bossbomb4*)m_ObjList[enBossbomb4].GetNext(bb4Pos1);
			CRect bRect = pBossbomb->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mb4Rect))
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mb4Rect.left, mb4Rect.top)
					);
				//删除子弹
				m_ObjList[enBossbomb4].RemoveAt(bb4Pos2);
				delete pBossbomb;
				reduceHP();
			}
		}
	}
}


// 战机子弹打中boss4
void CPlaneGameView::bombHitBoss4(void)
{
	POSITION b4Pos1 = NULL, b4Pos2 = NULL;
	if (m_pMe != NULL)
	{
		for (b4Pos1 = m_ObjList[enBomb].GetHeadPosition(); (b4Pos2 = b4Pos1) != NULL;)
		{
			CBomb* nBomb = (CBomb*)m_ObjList[enBomb].GetNext(b4Pos1);
			CRect bRect = nBomb->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enBoss4].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				Boss4* pBoss = (Boss4*)m_ObjList[enBoss4].GetNext(ePos1);
				CRect nRect = pBoss->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, nRect))
				{
					pBoss->setblood(10);
					//添加爆炸效果
					m_ObjList[enExplosion].AddTail(
						new CExplosion(bRect.left, bRect.top)
						);
					//删除导弹
					m_ObjList[enBomb].RemoveAt(b4Pos2);
					delete nBomb;

					//删除boss
					if (pBoss->b4_blood <= 0)
					{
						scores += scores4;
						old_scores = scores;
						m_ObjList[enBoss4].RemoveAt(ePos2);
						delete pBoss;
						bossflag = 0;
						step = 3;
						++status;
						passCartoon();
						return;
					}
					break;
				}
			}
		}
	}
}


// boss4和战机相撞
void CPlaneGameView::boss4HitMyPlane(void)
{
	POSITION b4Posboss1 = NULL, b4Posboss2 = NULL;
	if (m_pMe != NULL)
	{
		CRect b4Rect = m_pMe->GetRect();
		for (b4Posboss1 = m_ObjList[enBoss4].GetHeadPosition(); (b4Posboss2 = b4Posboss1) != NULL;)
		{
			Boss4* pBoss = (Boss4*)m_ObjList[enBoss4].GetNext(b4Posboss1);
			CRect bRect = pBoss->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, b4Rect))
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(b4Rect.left, b4Rect.top)
					);
				pBoss->setblood(10);
				reduceHP();
				//删除boss
				if (pBoss->b4_blood <= 0)
				{
					scores += scores4;
					old_scores = scores;
					m_ObjList[enBoss4].RemoveAt(b4Posboss2);
					delete pBoss;
					bossflag = 0;
					step = 3;
					++status;
					passCartoon();
					return;
				}
			}
		}
	}
}


// 创建boss5
void CPlaneGameView::createBoss5(void)
{
	if (m_pMe != NULL && scores-old_scores >= scores5s)
	{
		bossflag = 5;
		m_ObjList[enBoss5].AddTail(new Boss5);
	}
}


// boss5产生子弹
void CPlaneGameView::boss5CreateBomb(void)
{
	for (POSITION ePos = m_ObjList[enBoss5].GetHeadPosition(); ePos != NULL;)
	{
		Boss5* pBoss = (Boss5*)m_ObjList[enBoss5].GetNext(ePos);
		if (zidanok == 1)
		{
			if (!pBoss->Fired())
				continue;
			CPoint  ePt = pBoss->GetPoint();
			SetTimer(2, 1000, NULL);
			m_ObjList[enBossbomb5].AddTail(new Bossbomb5(ePt.x + 20, ePt.y + 30, pBoss->GetMontion()));
			m_ObjList[enBossbomb5].AddTail(new Bossbomb5(ePt.x + 85, ePt.y + 10, pBoss->GetMontion()));
			m_ObjList[enBossbomb5].AddTail(new Bossbomb5(ePt.x + 150, ePt.y + 30, pBoss->GetMontion()));
			zidanok = 0;
		}
	}
}


// boss5子弹打中战机
void CPlaneGameView::bossBomb5HitMyPlane(void)
{
	POSITION bb5Pos1 = NULL, bb5Pos2 = NULL;
	if (m_pMe != NULL)
	{
		CRect mb5Rect = m_pMe->GetRect();
		for (bb5Pos1 = m_ObjList[enBossbomb5].GetHeadPosition(); (bb5Pos2 = bb5Pos1) != NULL;)
		{
			Bossbomb5* pBossbomb = (Bossbomb5*)m_ObjList[enBossbomb5].GetNext(bb5Pos1);
			CRect bRect = pBossbomb->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mb5Rect))
			{
				for(int i=0; i<5; ++i) reduceHP();
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mb5Rect.left, mb5Rect.top)
					);
				//删除子弹
				m_ObjList[enBossbomb5].RemoveAt(bb5Pos2);
				delete pBossbomb;
				zidanok = 1;
			}
		}
	}
}


// 战机子弹打中boss5
void CPlaneGameView::bombHitBoss5(void)
{
	POSITION b5Pos1 = NULL, b5Pos2 = NULL;
	if (m_pMe != NULL)
	{
		for (b5Pos1 = m_ObjList[enBomb].GetHeadPosition(); (b5Pos2 = b5Pos1) != NULL;)
		{
			CBomb* nBomb = (CBomb*)m_ObjList[enBomb].GetNext(b5Pos1);
			CRect bRect = nBomb->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enBoss5].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				Boss5* pBoss = (Boss5*)m_ObjList[enBoss5].GetNext(ePos1);
				CRect nRect = pBoss->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, nRect))
				{
					pBoss->setblood(10);
					//添加爆炸效果
					m_ObjList[enExplosion].AddTail(
						new CExplosion(bRect.left, bRect.top)
						);
					//删除导弹
					m_ObjList[enBomb].RemoveAt(b5Pos2);
					delete nBomb;

					//删除boss
					if (pBoss->b5_blood <= 0)
					{
						scores += scores5;
						old_scores = scores;
						m_ObjList[enBoss5].RemoveAt(ePos2);
						delete pBoss;
						bossflag = 0;
						step = 4;
						++status;
						passCartoon();
						return;
					}
					break;
				}
			}
		}
	}
}


// boss5和战机相撞
void CPlaneGameView::boss5HitMyPlane(void)
{
	POSITION b5Posboss1 = NULL, b5Posboss2 = NULL;
	if (m_pMe != NULL)
	{
		CRect b5Rect = m_pMe->GetRect();
		for (b5Posboss1 = m_ObjList[enBoss5].GetHeadPosition(); (b5Posboss2 = b5Posboss1) != NULL;)
		{
			Boss5* pBoss = (Boss5*)m_ObjList[enBoss5].GetNext(b5Posboss1);
			CRect bRect = pBoss->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, b5Rect))
			{
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(b5Rect.left, b5Rect.top)
					);
				pBoss->setblood(10);
				reduceHP();
				//删除boss
				if (pBoss->b5_blood <= 0)
				{
					scores += scores5;
					old_scores = scores;
					m_ObjList[enBoss5].RemoveAt(b5Posboss2);
					delete pBoss;
					bossflag = 0;
					step = 4;
					++status;
					passCartoon();
					return;
				}
			}
		}
	}
}

// bomb6打中战机
void CPlaneGameView::bossbomb6HitMyPlane(void)
{
	POSITION bb5Pos1 = NULL, bb5Pos2 = NULL;
	if (m_pMe != NULL)
	{
		CRect mb5Rect = m_pMe->GetRect();
		for (bb5Pos1 = m_ObjList[enBossbomb6].GetHeadPosition(); (bb5Pos2 = bb5Pos1) != NULL;)
		{
			Bossbomb6* pBossbomb = (Bossbomb6*)m_ObjList[enBossbomb6].GetNext(bb5Pos1);
			CRect bRect = pBossbomb->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mb5Rect))
			{
				reduceHP();
				//添加爆炸效果
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mb5Rect.left, mb5Rect.top)
					);
				//删除子弹
				m_ObjList[enBossbomb6].RemoveAt(bb5Pos2);
				delete pBossbomb;
			}
		}
	}
}

// 激光消耗能量
void CPlaneGameView::LaserReduceEnergy(void)
{
	if (invincible == 0) --nuclearBomp;
}

// 发射激光
void CPlaneGameView::createLaser(void)
{
	if (m_pMe != NULL  && GetKey('K') && m_pMe->Fired())
	{
		if(invincible == 0 && !nuclearBomp) return;
		CPoint la = m_pMe->GetPoint();
		m_ObjList[enLaser].AddTail(new Laser(la.x - 30, la.y - 500, 0));
		LaserReduceEnergy();
	}
}

// 激光碰撞敌机
void CPlaneGameView::laserHitEnemy(void)
{
	POSITION lePos1 = NULL, lePos2 = NULL;
	if (m_pMe != NULL)
	{
		for (lePos1 = m_ObjList[enLaser].GetHeadPosition(); (lePos2 = lePos1) != NULL;)
		{
			Laser* plaser = (Laser*)m_ObjList[enLaser].GetNext(lePos1);
			CRect bRect = plaser->GetRect();
			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
				CRect nRect = pEnemy->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, nRect))
				{
					scores += 10;
					//添加爆炸效果
					m_ObjList[enExplosion].AddTail(
						new CExplosion(bRect.left, bRect.top)
					);
					//删除敌机
					m_ObjList[enEnemy].RemoveAt(ePos2);
					delete pEnemy;
					int giftType = rand() % 70;
					if (giftType <= 1)
						m_ObjList[gifts].AddTail(new  Gifts(bRect.left - 10, bRect.top - 10, 1)); //生命
					else if (giftType <= 3)
						m_ObjList[gifts].AddTail(new  Gifts(bRect.left - 10, bRect.top - 10, 2)); //核弹
					else if (giftType <= 5)
						m_ObjList[gifts].AddTail(new  Gifts(bRect.left - 10, bRect.top - 10, 3)); //保护罩
					else if(giftType <= (9-weaponLevel))
						m_ObjList[gifts].AddTail(new  Gifts(bRect.left - 10, bRect.top - 10, 4)); //武器升级
					break;
				}
			}
		}
	}
}

// 激光和boss1碰撞
void CPlaneGameView::laserHitBoss1(void)
{
	POSITION le1Pos1 = NULL, le1Pos2 = NULL;
	if (m_pMe != NULL)
	{
		for (le1Pos1 = m_ObjList[enLaser].GetHeadPosition(); (le1Pos2 = le1Pos1) != NULL;)
		{
			Laser* plaser = (Laser*)m_ObjList[enLaser].GetNext(le1Pos1);
			CRect bRect = plaser->GetRect();
			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enBoss1].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				Boss* pBoss = (Boss*)m_ObjList[enBoss1].GetNext(ePos1);
				CRect nRect = pBoss->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, nRect))
				{
					pBoss->setblood(10);
					//添加爆炸效果
					m_ObjList[enExplosion].AddTail(
						new CExplosion(nRect.left, nRect.top)
						);
					//删除boss
					if (pBoss->blood <= 0)
					{
						scores += scores1;
						old_scores = scores;
						++status;
						m_ObjList[enBoss1].RemoveAt(ePos2);
						delete pBoss;
						bossflag = 0;
						break;
					}
				}
			}
		}
	}
}

// 激光和boss2相撞
void CPlaneGameView::laserHitBoss2(void)
{
	POSITION le2Pos1 = NULL, le2Pos2 = NULL;
	if (m_pMe != NULL)
	{
		for (le2Pos1 = m_ObjList[enLaser].GetHeadPosition(); (le2Pos2 = le2Pos1) != NULL;)
		{
			Laser* plaser = (Laser*)m_ObjList[enLaser].GetNext(le2Pos1);
			CRect bRect = plaser->GetRect();
			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enBoss2].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				Boss* pBoss = (Boss*)m_ObjList[enBoss2].GetNext(ePos1);
				CRect nRect = pBoss->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, nRect))
				{
					pBoss->setblood(10);
					//添加爆炸效果
					m_ObjList[enExplosion].AddTail(
						new CExplosion(nRect.left, nRect.top)
						);
					//删除boss
					if (pBoss->blood <= 0)
					{
						scores += scores2;
						old_scores = scores;
						++status;
						m_ObjList[enBoss2].RemoveAt(ePos2);
						delete pBoss;
						bossflag = 0;
						break;
					}
				}
			}
		}
	}
}

//激光和boss3相撞
void CPlaneGameView::laserHitBoss3(void)
{
	POSITION le3Pos1 = NULL, le3Pos2 = NULL;
	if (m_pMe != NULL)
	{
		for (le3Pos1 = m_ObjList[enLaser].GetHeadPosition(); (le3Pos2 = le3Pos1) != NULL;)
		{
			Laser* plaser = (Laser*)m_ObjList[enLaser].GetNext(le3Pos1);
			CRect bRect = plaser->GetRect();
			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enBoss3].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				Boss* pBoss = (Boss*)m_ObjList[enBoss3].GetNext(ePos1);
				CRect nRect = pBoss->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, nRect))
				{
					pBoss->setblood(10);
					//添加爆炸效果
					m_ObjList[enExplosion].AddTail(
						new CExplosion(nRect.left, nRect.top)
						);
					//删除boss
					if (pBoss->blood <= 0)
					{
						scores += scores3;
						old_scores = scores;
						m_ObjList[enBoss3].RemoveAt(ePos2);
						delete pBoss;
						bossflag = 0;
						++status;
						++step;
						passCartoon();
						return;
					}
				}
			}
		}
	}
}


// 激光和boss4相撞
void CPlaneGameView::laserHitBoss4(void)
{
	POSITION le4Pos1 = NULL, le4Pos2 = NULL;
	if (m_pMe != NULL)
	{
		for (le4Pos1 = m_ObjList[enLaser].GetHeadPosition(); (le4Pos2 = le4Pos1) != NULL;)
		{
			Laser* plaser = (Laser*)m_ObjList[enLaser].GetNext(le4Pos1);
			CRect bRect = plaser->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enBoss4].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				Boss* pBoss = (Boss*)m_ObjList[enBoss4].GetNext(ePos1);
				CRect nRect = pBoss->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, nRect))
				{
					pBoss->setblood(10);
					//添加爆炸效果
					m_ObjList[enExplosion].AddTail(
						new CExplosion(nRect.left, nRect.top)
						);
					//删除boss
					if (pBoss->blood <= 0)
					{
						scores += scores4;
						old_scores = scores;
						m_ObjList[enBoss4].RemoveAt(ePos2);
						delete pBoss;
						bossflag = 0;
						++step;
						++status;
						passCartoon();
						return;
					}
				}
			}
		}
	}
}


// 激光碰撞boss5
void CPlaneGameView::laserHitboss5(void)
{
	POSITION le5Pos1 = NULL, le5Pos2 = NULL;
	if (m_pMe != NULL)
	{
		for (le5Pos1 = m_ObjList[enLaser].GetHeadPosition(); (le5Pos2 = le5Pos1) != NULL;)
		{
			Laser* plaser = (Laser*)m_ObjList[enLaser].GetNext(le5Pos1);
			CRect bRect = plaser->GetRect();
			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enBoss5].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				Boss* pBoss = (Boss*)m_ObjList[enBoss5].GetNext(ePos1);
				CRect nRect = pBoss->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, nRect))
				{
					pBoss->setblood(10);
					//添加爆炸效果
					m_ObjList[enExplosion].AddTail(
						new CExplosion(nRect.left, nRect.top)
						);
					//删除boss
					if (pBoss->blood <= 0)
					{
						scores += scores5;
						old_scores = scores;
						m_ObjList[enBoss5].RemoveAt(ePos2);
						delete pBoss;
						bossflag = 0;
						++step;
						++status;
						passCartoon();
						return;
					}
				}
			}
		}
	}
}


// boss驱动程序
void CPlaneGameView::bossDriver(void)
{
	if(start == 0) return;
	switch(bossflag)
	{
	case 0:
		switch(status)
		{
		case 1:
		case 4:
		case 7:
			createBoss(); //创建boss 909
			break;
		case 2:
		case 5:
		case 8:
			createBoss2(); //创建boss2 1057
			break;
		case 3:
			createBoss3(); //创建boss3 1190
			break;
		case 6:
			createBoss4(); //创建boss4 1335
			break;
		case 9:
			createBoss5(); //创建boss5 1481
			break;
		}
	break;
	case 1:
		bossCreateBomb();// boss产生子弹 920
		bossBombHitMyPlane();// boss子弹打中战机 937
		bombHitBoss();//战机子弹打中boss 965
		bossHitMyPlane();// boss和战机相撞 1010
		laserHitBoss1();//激光和boss1相撞  1716
		break;
	case 2:
		boss2CreateBomb();// boss2产生子弹 1057
		boss2BombHitMyPlane();// boss2子弹打中战机 1077
		bombHitBoss2();//战机子弹打中boss2 1106
		boss2HitMyPlane();// boss2和战机相撞 1152
		laserHitBoss2();//激光和boss2相撞 1756
		break;
	case 3:
		boss3CreateBomb();//boss3产生子弹 1201
		bossBomb3HitMyPlane();// boss3子弹打中战机 1219
		bombHitBoss3();//战机子弹打中boss3 1248
		boss3HitMyPlane();// boss3和战机相撞 1297
		laserHitBoss3();//激光和boss3相撞 1796
		break;
	case 4:
		boss4CreateBomb();// boss4产生子弹 1345
		bossBomb4HitMyPlane();// boss4子弹打中战机 1365
		bombHitBoss4();//战机子弹打中boss4 1393
		boss4HitMyPlane();// boss4和战机相撞 1442
		laserHitBoss4();//激光和boss4相撞  1839
		break;
	case 5:
		boss5CreateBomb();// boss5产生子弹 1492
		bossBomb5HitMyPlane();// boss5子弹打中战机 1513
		bombHitBoss5();//战机子弹打中boss5 1542
		boss5HitMyPlane();// boss5和战机相撞 1591
		bossbomb6HitMyPlane();//bomb6碰撞战机 1629
		laserHitboss5();//激光和boss5相撞 1883
		break;
	}		
}

void CPlaneGameView::passCartoon()//过关动画
{
	start = 0;
	shield.on = 0;
	for(int i=0; i<17; ++i)
	{
		m_ObjList[i].RemoveAll();
	}
	HP = 100;
}
