
// ChildView.h : CChildView 类的接口
//


#pragma once
#include "ClassRect_fzt.h"
#include "Sound.h"
#include "defhead.h"
#include "Pentagram.h"
// CChildView 窗口

class CChildView : public CWnd
{
// 构造
public:
	CChildView();

// 特性
public:

// 操作
public:

// 重写
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildView();

	// 生成的消息映射函数
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	int rect_width;
	int rect_height;
	void Init(void);//游戏参数初始化
	ClassRect_fzt rect_fzt[MAX_NUM][MAX_NUM];//设置矩形最大数目，数组只能用常量定义
	COLORREF ChooseColor(void);//随机生成一种颜色
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void ChooseRect(int x,int y,COLORREF c);//选中矩形
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void EraseRect(int x,int y,COLORREF c);//擦除矩形
	void GetUpdateRect();//更新矩形状态
	void SwapRect(ClassRect_fzt &a,ClassRect_fzt &b);//交换2个矩形属性
	bool IsOver();//游戏是否结束，结束返回true
	int m_chooseNum;//鼠标所在矩形连起来的数目
	int m_rectNumX;//生成矩形数目X
	int m_rectNumY;
	int m_species;//矩形颜色数
	afx_msg void OnNewGame();
	afx_msg void OnSaveGame();
	afx_msg void OnSetGame();
	void ChangeWindow();//改变窗口大小和位置
	void DrawInfo(CDC &dcMemory);//绘制游戏信息,参数为缓存dc
	int CalScore(int num);//计算游戏得分
	int m_score;
	int GameOver(void);	// 游戏结束
	CSound *sound;
	COLORREF m_Rectcolor[MAX_COLORNUM];
private:
	COLORREF oldc;//用来判断鼠标是否移到别的矩形上
	COLORREF color_btndown;
	int oldx;
	int oldy;
	CString s_effectName;//保存选择的文件名称和路径
	CString s_musicName;
	CString s_effectPath;
	CString s_musicPath;
	int max_sorce;//游戏最高分，保存在注册表中
	int num_rest;
	bool m_gameIsOver;
public:
	afx_msg void OnSetSound();
	afx_msg void OnReadGame();
	afx_msg void OnSaveAs();
	afx_msg void OnReadAs();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
	bool m_isClassMode;// 是否是经典模式
	bool m_isIntoStage;//进入关卡画面
	bool m_isShowGoodInfo;//连消数目提示信息
	int m_goodnun;

	int m_stage;//经典模式下的关数
	int m_targeSorce;//每关目标分数
	afx_msg void OnUpdateSetGame(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSetSound(CCmdUI *pCmdUI);
	afx_msg void OnClassicmode();
	afx_msg void OnTip();
	afx_msg void OnUpdateClassicmode(CCmdUI *pCmdUI);
	int ReadFile(CString s_name);//读取文件，失败返回0
	void WriteFile(CString s_name);
	void MoveAnimation();
	void DrawAllRect(CDC &dcMemory);//绘制所有背景矩形
	void DrawChooseRect(CDC &dcMemory);//绘制被选择的矩形
	void NewPent(CPoint point,COLORREF c);
	void DrawAnimation(CDC &dcMemory);
	void StopAnimation();//当鼠标按下和读取存档时调用，防止一些bug
	int SubGameOver();
	void KillMouseAnimation();
	void DrawIntoStage(CDC &dcMemory);
	void InitLevel();
	void DrawExtraInfo(CDC &dcMemory);
	void DrawGoodInfo(CDC &dcMemory);
	int timer_num;//动画新增，用来表示计数器中动画移动次数
	//CPentagram p[10];
	CPentagram *pent;
	CPentagram *p;
	CPentagram *pre;
	//int p_num;//
	int m_time;//相当与消除动画已经运行的时间
	int nowx;
	int nowy;
	CBitmap bitmap;
	
};

