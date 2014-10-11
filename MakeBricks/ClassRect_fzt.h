#pragma once
class ClassRect_fzt
{
public:
	ClassRect_fzt();
	~ClassRect_fzt(void);
	void SetColor(COLORREF c);//设置矩形颜色
	void SetPoint(int x,int y);//设置矩形位置
	bool IsAlive();//判断矩形是否存在
	void SetAlive(bool b);//设置矩形存在与否
	bool IsColor(COLORREF c);//判断颜色
	COLORREF GetColor();//得到矩形现在颜色
	bool IsSameColor(COLORREF c);//是否与选中颜色相同
	void SetSameColor(bool b);//矩形与选择块相同时设为true
	bool IsChoose();//是否被选中
	void EraseRect();//消去该矩形
	int x;//矩形坐标
	int y;
	int oldx;//制作动画时新增，目的是保存动画之前矩形坐标
	int oldy;
private:
	bool alive;//矩形存活状态
	COLORREF color;//矩形颜色
	bool SameColor;//判断该矩形块是否与选中的矩形颜色相同
	
};

