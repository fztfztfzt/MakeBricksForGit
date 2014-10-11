/************************************************************************/
/* 游戏中常量和宏定义的申明统一定义处                                                                     */
/************************************************************************/
#pragma once
const int FZT_WIDTH = 640;//默认窗口宽度
const int FZT_HIGHT = 480;//默认窗口高度
const int FZT_NUMX	= 20;//默认矩形X数目
const int FZT_NUMY	= 20;//默认矩形Y数目
const int FZT_SPECIES =	5;//默认矩形颜色种类
const int MAX_NUM	  =	30;//最大矩形数目
const int MAX_COLORNUM=	12;//最大矩形种类数
const int RECT_WIDTH  =	32;//矩形宽度
const int RECT_HEIGHT=	24;//矩形高度

const int FZT_GAP	= 2;//用以显示信息的行数

const int DEFAULT_FRAME_X = 6;	//窗口X方向宽
const int DEFAULT_FRAME_Y  = 52;

//颜色设定
#define FZT_BGCOLOR	RGB(255,255,255)//白色
#define FZT_BLACK   RGB(0,0,0)
#define FZT_RED		RGB(255,0,0)
#define FZT_GREEN	RGB(0,255,0)
#define FZT_BLUE	RGB(0,0,255)
#define FZT_YELLOW	RGB(255,255,0)
#define FZT_PINK	RGB(255,192,203)
#define FZT_SKYBLUE RGB(135,206,235)
#define FZT_CRIMSON	RGB(220,20,60)
#define	FZT_ORANGER	RGB(255,69,0)//橙红
#define	FZT_PURPLE	RGB(192,14,235)//紫色
#define FZT_GOLD	RGB(255,215,0)//金色
#define	FZT_LIGHTGREEN	RGB(127,255,0)//淡绿
#define FZT_LIGHTBLUE	RGB(0,250,154)//淡蓝	
#define	FZT_NAVYBLUE	RGB(0,0,128)//海军蓝
#define FZT_LIGHTPURPLE	RGB(85,107,47)//淡紫

//播放声音种类
const int STATE_MOUSEMOVE = 0;
const int STATE_BTUDOWN	= 1;
//初始化时声音名和路径
#define SOUND_EFFECTNAME	"Cursor.wav"
#define SOUND_EFFECTPATH	"res\\effect\\Cursor.wav"
#define SOUND_MUSICNAME		"glassbreak.wav"
#define SOUND_MUSICPATH		"res\\music\\glassbreak.wav";
//
const double  PI = 3.1415927;

//定时器ID
const int TIMER_REFRESH	= 1;
const int TIMER_INFOINTOTRAGE = 10;
const int TIMER_SHOWGOODINFO = 11;