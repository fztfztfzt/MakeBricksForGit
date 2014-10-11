/*动画效果   五角星的属性以及方法
五角星以链表形式存储，next用以指向下一个节点

*/
#pragma once
class CPentagram
{
public:
	CPentagram(void);
	~CPentagram(void);
	CPoint pts[10];//五角星的10个顶点
	CPoint oldPts[10];
	CPoint center_point;//中心点
	
	void Init();
	void SetCenterPoint(int,int);//设置中心点
	void SetCenterPoint(CPoint p);
	void SetSpeed(int,int);
	void Run();
	void SetColor(COLORREF);
	COLORREF GetColor();
	CPentagram *next;//指针链表，指向下一个五角星
private:
	int radius;//五角星半径
	int vx;//x轴初速度
	int vy;//y轴初速度
	int a;//y轴加速度
	int t;//运行时间
	COLORREF color;//五角星颜色
};

