#include "StdAfx.h"
#include "ClassRect_fzt.h"
#include "defhead.h"

ClassRect_fzt::ClassRect_fzt()
{
	alive=0;
	SameColor=false;
	color = FZT_BLACK;
}


ClassRect_fzt::~ClassRect_fzt(void)
{
}
void ClassRect_fzt::SetPoint(int a,int b)
{
	x=a;
	y=b;
}
bool ClassRect_fzt::IsAlive()
{
	return alive;
}
bool ClassRect_fzt::IsColor(COLORREF c)
{
	if(color == c) return true;
	else return false;
}
void ClassRect_fzt::SetColor(COLORREF c)
{
	color = c;
}
void ClassRect_fzt::SetAlive(bool b)
{
	alive = b;
}
COLORREF ClassRect_fzt::GetColor()
{
	return color;
}
bool ClassRect_fzt::IsSameColor(COLORREF c)
{
	if(color == c)
		return true;
	else
		return false;
}
void ClassRect_fzt::SetSameColor(bool b)
{
	SameColor = b;
}
bool ClassRect_fzt::IsChoose()
{
	return SameColor;
}
void ClassRect_fzt::EraseRect()
{
	alive = false;
	color = FZT_BGCOLOR;
	SameColor = false;
}