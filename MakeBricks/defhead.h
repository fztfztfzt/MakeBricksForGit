/************************************************************************/
/* ��Ϸ�г����ͺ궨�������ͳһ���崦                                                                     */
/************************************************************************/
#pragma once
const int FZT_WIDTH = 640;//Ĭ�ϴ��ڿ��
const int FZT_HIGHT = 480;//Ĭ�ϴ��ڸ߶�
const int FZT_NUMX	= 20;//Ĭ�Ͼ���X��Ŀ
const int FZT_NUMY	= 20;//Ĭ�Ͼ���Y��Ŀ
const int FZT_SPECIES =	5;//Ĭ�Ͼ�����ɫ����
const int MAX_NUM	  =	30;//��������Ŀ
const int MAX_COLORNUM=	12;//������������
const int RECT_WIDTH  =	32;//���ο��
const int RECT_HEIGHT=	24;//���θ߶�

const int FZT_GAP	= 2;//������ʾ��Ϣ������

const int DEFAULT_FRAME_X = 6;	//����X�����
const int DEFAULT_FRAME_Y  = 52;

//��ɫ�趨
#define FZT_BGCOLOR	RGB(255,255,255)//��ɫ
#define FZT_BLACK   RGB(0,0,0)
#define FZT_RED		RGB(255,0,0)
#define FZT_GREEN	RGB(0,255,0)
#define FZT_BLUE	RGB(0,0,255)
#define FZT_YELLOW	RGB(255,255,0)
#define FZT_PINK	RGB(255,192,203)
#define FZT_SKYBLUE RGB(135,206,235)
#define FZT_CRIMSON	RGB(220,20,60)
#define	FZT_ORANGER	RGB(255,69,0)//�Ⱥ�
#define	FZT_PURPLE	RGB(192,14,235)//��ɫ
#define FZT_GOLD	RGB(255,215,0)//��ɫ
#define	FZT_LIGHTGREEN	RGB(127,255,0)//����
#define FZT_LIGHTBLUE	RGB(0,250,154)//����	
#define	FZT_NAVYBLUE	RGB(0,0,128)//������
#define FZT_LIGHTPURPLE	RGB(85,107,47)//����

//������������
const int STATE_MOUSEMOVE = 0;
const int STATE_BTUDOWN	= 1;
//��ʼ��ʱ��������·��
#define SOUND_EFFECTNAME	"Cursor.wav"
#define SOUND_EFFECTPATH	"res\\effect\\Cursor.wav"
#define SOUND_MUSICNAME		"glassbreak.wav"
#define SOUND_MUSICPATH		"res\\music\\glassbreak.wav";
//
const double  PI = 3.1415927;

//��ʱ��ID
const int TIMER_REFRESH	= 1;
const int TIMER_INFOINTOTRAGE = 10;
const int TIMER_SHOWGOODINFO = 11;