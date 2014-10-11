#include "StdAfx.h"
#include "Pentagram.h"
#include "defhead.h"
#include <math.h>

CPentagram::CPentagram(void)
{
	radius = 10;
	vx=0;
	vy=0;
	a=5;
	t=0;
	next=NULL;
	Init();
}


CPentagram::~CPentagram(void)
{
}
void CPentagram::Init()
{
	float theta1=18;
	float theta2=54;
	for (int i=0;i<5;i++)//对外圆的五个点初始化
	{
		pts[2*i].x=radius*cos((theta1+72*i)*PI/180)+center_point.x;
		oldPts[2*i].x=pts[2*i].x;
		pts[2*i].y=-radius*sin((theta1+72*i)*PI/180)+center_point.y;
		oldPts[2*i].y=pts[2*i].y;
	}
	for(int i=0;i<5;i++) //求靠里面边的五个顶点的坐标
	{
		float r=radius*sin(18*PI/180)/sin(54*PI/180);

		pts[2*i+1].x=r*cos((theta2+i*72)*PI/180)+center_point.x;
		pts[2*i+1].y=-r*sin((theta2+i*72)*PI/180)+center_point.y;
		oldPts[2*i+1].x=pts[2*i+1].x;
		oldPts[2*i+1].y=pts[2*i+1].y;
	}
}
void CPentagram::SetCenterPoint(int x,int y)
{
	center_point.x = x;
	center_point.y=y;
	Init();
}
void CPentagram::SetCenterPoint(CPoint p)
{
	center_point = p;
	Init();
}
void CPentagram::SetSpeed(int x,int y)
{
	vx=x;
	vy=y;
}
void CPentagram::Run()
{
	for(int i=0;i<10;i++)
	{
	//	pts[i].x=oldPts[i].x+center_point.x+vx*t;
		//if(t<=vy/a) pts[i].y=oldPts[i].y+center_point.y-(vy*t-a*t*t/2);
		//else pts[i].y=oldPts[i].y+center_point.y-(vy*t-a*t*t/2)+a*(t-vy/a)*(t-vy/a)/2;
		pts[i].x += vx;
		if(t<=vy/a) pts[i].y=oldPts[i].y-(vy*t-a*t*t/2);
		else pts[i].y=oldPts[i].y-(vy*vy/2/a)+a*(t-vy/a)*(t-vy/a)/2;
	}
	++t;
//	TRACE("x=%d,y=%d,t=%d\n",pts[0].x,pts[0].y,t);
	
	//Sleep(100);
}
void CPentagram::SetColor(COLORREF c)
{
	color = c;
}
COLORREF CPentagram::GetColor()
{
	return color;
}