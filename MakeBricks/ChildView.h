
// ChildView.h : CChildView ��Ľӿ�
//


#pragma once
#include "ClassRect_fzt.h"
#include "Sound.h"
#include "defhead.h"
#include "Pentagram.h"
// CChildView ����

class CChildView : public CWnd
{
// ����
public:
	CChildView();

// ����
public:

// ����
public:

// ��д
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CChildView();

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	int rect_width;
	int rect_height;
	void Init(void);//��Ϸ������ʼ��
	ClassRect_fzt rect_fzt[MAX_NUM][MAX_NUM];//���þ��������Ŀ������ֻ���ó�������
	COLORREF ChooseColor(void);//�������һ����ɫ
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void ChooseRect(int x,int y,COLORREF c);//ѡ�о���
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void EraseRect(int x,int y,COLORREF c);//��������
	void GetUpdateRect();//���¾���״̬
	void SwapRect(ClassRect_fzt &a,ClassRect_fzt &b);//����2����������
	bool IsOver();//��Ϸ�Ƿ��������������true
	int m_chooseNum;//������ھ�������������Ŀ
	int m_rectNumX;//���ɾ�����ĿX
	int m_rectNumY;
	int m_species;//������ɫ��
	afx_msg void OnNewGame();
	afx_msg void OnSaveGame();
	afx_msg void OnSetGame();
	void ChangeWindow();//�ı䴰�ڴ�С��λ��
	void DrawInfo(CDC &dcMemory);//������Ϸ��Ϣ,����Ϊ����dc
	int CalScore(int num);//������Ϸ�÷�
	int m_score;
	int GameOver(void);	// ��Ϸ����
	CSound *sound;
	COLORREF m_Rectcolor[MAX_COLORNUM];
private:
	COLORREF oldc;//�����ж�����Ƿ��Ƶ���ľ�����
	COLORREF color_btndown;
	int oldx;
	int oldy;
	CString s_effectName;//����ѡ����ļ����ƺ�·��
	CString s_musicName;
	CString s_effectPath;
	CString s_musicPath;
	int max_sorce;//��Ϸ��߷֣�������ע�����
	int num_rest;
	bool m_gameIsOver;
public:
	afx_msg void OnSetSound();
	afx_msg void OnReadGame();
	afx_msg void OnSaveAs();
	afx_msg void OnReadAs();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
	bool m_isClassMode;// �Ƿ��Ǿ���ģʽ
	bool m_isIntoStage;//����ؿ�����
	bool m_isShowGoodInfo;//������Ŀ��ʾ��Ϣ
	int m_goodnun;

	int m_stage;//����ģʽ�µĹ���
	int m_targeSorce;//ÿ��Ŀ�����
	afx_msg void OnUpdateSetGame(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSetSound(CCmdUI *pCmdUI);
	afx_msg void OnClassicmode();
	afx_msg void OnTip();
	afx_msg void OnUpdateClassicmode(CCmdUI *pCmdUI);
	int ReadFile(CString s_name);//��ȡ�ļ���ʧ�ܷ���0
	void WriteFile(CString s_name);
	void MoveAnimation();
	void DrawAllRect(CDC &dcMemory);//�������б�������
	void DrawChooseRect(CDC &dcMemory);//���Ʊ�ѡ��ľ���
	void NewPent(CPoint point,COLORREF c);
	void DrawAnimation(CDC &dcMemory);
	void StopAnimation();//����갴�ºͶ�ȡ�浵ʱ���ã���ֹһЩbug
	int SubGameOver();
	void KillMouseAnimation();
	void DrawIntoStage(CDC &dcMemory);
	void InitLevel();
	void DrawExtraInfo(CDC &dcMemory);
	void DrawGoodInfo(CDC &dcMemory);
	int timer_num;//����������������ʾ�������ж����ƶ�����
	//CPentagram p[10];
	CPentagram *pent;
	CPentagram *p;
	CPentagram *pre;
	//int p_num;//
	int m_time;//�൱�����������Ѿ����е�ʱ��
	int nowx;
	int nowy;
	CBitmap bitmap;
	
};

