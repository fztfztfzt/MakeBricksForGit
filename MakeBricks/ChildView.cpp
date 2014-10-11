
// ChildView.cpp : CChildView ���ʵ��
//

#include "stdafx.h"
#include "MakeBricks.h"
#include "ChildView.h"
#include "SetDialog.h"
#include "SetSoundDiagle.h"
#include "CtipsDlg.h"
#include "MainFrm.h"

#include <time.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

COLORREF ColorArray[]={
	FZT_PINK	,
	FZT_LIGHTPURPLE,
	FZT_GOLD	,
	FZT_LIGHTGREEN,	
	FZT_LIGHTBLUE,

	FZT_RED	,
	FZT_YELLOW	,
	FZT_GREEN,	
	FZT_BLUE	,	
	FZT_PURPLE	,		

	FZT_CRIMSON	,
	FZT_ORANGER	,
};
// CChildView

CChildView::CChildView()
	: m_chooseNum(0)
	, m_score(0)
	, m_isClassMode(true)
	,m_stage(1)
{
	rect_width = RECT_WIDTH;
	rect_height = RECT_HEIGHT;
	m_rectNumX = FZT_NUMX;
	m_rectNumY = FZT_NUMY;
	m_species = FZT_SPECIES;
	m_isClassMode=false;
	m_score=0;
	m_targeSorce=1000;
	num_rest=0;
	for(int i=0;i<MAX_COLORNUM;i++)
	m_Rectcolor[i] = ColorArray[i];
	sound = new CSound;
	timer_num=0;
	m_time=0;
	m_gameIsOver=false;
	s_effectName = SOUND_EFFECTNAME;
	s_musicName = SOUND_MUSICNAME;
	s_effectPath = SOUND_EFFECTPATH;
	s_musicPath = SOUND_MUSICPATH;
	pent = NULL;
	p=NULL;
	pre=NULL;
	nowx=0;
	nowy=0;
	m_isIntoStage=false;
	//AfxGetApp()->WriteProfileInt("save","MAX",0);
	//p_num=-1;
	
	Init();
}

CChildView::~CChildView()
{
	if(m_gameIsOver)
	{
		OFSTRUCT ofn;
		if(OpenFile("save_exit.fzt",&ofn,OF_EXIST) != HFILE_ERROR) //�浵����Ӧɾ��
		{
			DeleteFile("save_exit.fzt");
		}
	}else WriteFile("save_exit.fzt");
	StopAnimation();
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_32771, &CChildView::OnNewGame)
	ON_COMMAND(ID_QUICKSAVE, &CChildView::OnSaveGame)
	ON_COMMAND(ID_32774, &CChildView::OnSetGame)
	ON_COMMAND(ID_32776, &CChildView::OnSetSound)
	ON_COMMAND(ID_QUICKREAD, &CChildView::OnReadGame)
	ON_COMMAND(ID_32778, &CChildView::OnSaveAs)
	ON_COMMAND(ID_32779, &CChildView::OnReadAs)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(ID_32774, &CChildView::OnUpdateSetGame)
	ON_UPDATE_COMMAND_UI(ID_32776, &CChildView::OnUpdateSetSound)
	ON_COMMAND(ID_CLASSICMODE, &CChildView::OnClassicmode)
	ON_COMMAND(ID_32789, &CChildView::OnTip)
	ON_UPDATE_COMMAND_UI(ID_CLASSICMODE, &CChildView::OnUpdateClassicmode)
END_MESSAGE_MAP()



// CChildView ��Ϣ�������

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������
	CDC *cdc = GetDC();
	CPen *oldPen;
	CDC dcMemory;//����DC
	dcMemory.CreateCompatibleDC(&dc);
	//CBitmap MemBitmap;
	//MemBitmap.CreateCompatibleBitmap(cdc,m_rectNumX*RECT_WIDTH,(m_rectNumY+FZT_GAP)*RECT_HEIGHT);
	bitmap.m_hObject = (HBITMAP)LoadImage(NULL,"res\\QingHua.bmp",
		IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION|LR_DEFAULTSIZE|LR_LOADFROMFILE);
	dcMemory.SelectObject(bitmap);
	if(m_isIntoStage) DrawIntoStage(dcMemory);
	else
	{
		//	cdc->SelectObject(bitmap);
//	dcMemory.BitBlt(0,0,m_rectNumX*RECT_WIDTH,(m_rectNumY+FZT_GAP)*RECT_HEIGHT,cdc,0,0,SRCCOPY);
	
	
		DrawInfo(dcMemory);//���ƼƷ���Ϣ
		CPen pen_unchoose(PS_SOLID,1,FZT_BGCOLOR);
		dcMemory.SelectObject(pen_unchoose);
		DrawAllRect(dcMemory);//�������б�������
		CPen pen_choosed(PS_SOLID,2,FZT_CRIMSON);
		oldPen=dcMemory.SelectObject(&pen_choosed);
		DrawChooseRect(dcMemory);//���Ʊ�ѡ��ľ���
		CPen pen_animation(PS_SOLID,1,FZT_BLACK);
		dcMemory.SelectObject(pen_animation);
		DrawAnimation(dcMemory);
		dcMemory.SelectObject(oldPen);
		DrawExtraInfo(dcMemory);
		DrawGoodInfo(dcMemory);
	}
	
	dc.BitBlt(0,0,m_rectNumX*RECT_WIDTH,(m_rectNumY+FZT_GAP)*RECT_HEIGHT,&dcMemory,0,0,SRCCOPY);
//	MemBitmap.DeleteObject();//�ͷ�dc
	bitmap.DeleteObject();
	dcMemory.DeleteDC();
	ReleaseDC(&dc);
	ReleaseDC(cdc);
			// ��ҪΪ������Ϣ������ CWnd::OnPaint()
}
void CChildView::DrawIntoStage(CDC &dcMemory)
{
	CFont font;
	font.CreatePointFont(300,_T("����Ȥ���"));
	CFont font2;
	font2.CreatePointFont(200,_T("����Ȥ���"));
	dcMemory.SelectObject(&font);
	dcMemory.SetTextColor(FZT_BLACK);
	dcMemory.SetBkMode(TRANSPARENT);
	CString s;
	if(m_gameIsOver)
	{
		CFont font3;
		font3.CreatePointFont(m_rectNumX*23,_T("����Ȥ���"));
		dcMemory.SelectObject(&font3);
		int sore;
		if(num_rest<10) sore = 2000-20*num_rest*num_rest;
		else sore=0;
		m_score+=sore;
		s.Format("ʣ��%d��,��%d��",num_rest,sore);
		CSize size = dcMemory.GetTextExtent(s);
		dcMemory.TextOutA(((m_rectNumX*RECT_WIDTH+DEFAULT_FRAME_X)-size.cx)/2,
			(m_rectNumY*RECT_HEIGHT+DEFAULT_FRAME_Y+FZT_GAP*RECT_HEIGHT)*1/5,s);
		s.Format("�ܷ�%d ��Ϸ����",m_score);
		size = dcMemory.GetTextExtent(s);
		dcMemory.TextOutA(((m_rectNumX*RECT_WIDTH+DEFAULT_FRAME_X)-size.cx)/2,
			(m_rectNumY*RECT_HEIGHT+DEFAULT_FRAME_Y+FZT_GAP*RECT_HEIGHT)*2/4,s);
		if(m_isClassMode && max_sorce<m_score) 
		{
			max_sorce = m_score;
			AfxGetApp()->WriteProfileInt("save","MAX",m_score);
		}
	}
	else
	{
		s.Format("�ؿ�%d",m_stage);
		CSize size = dcMemory.GetTextExtent(s);
		dcMemory.TextOutA(((m_rectNumX*RECT_WIDTH+DEFAULT_FRAME_X)-size.cx)/2,
			(m_rectNumY*RECT_HEIGHT+DEFAULT_FRAME_Y+FZT_GAP*RECT_HEIGHT)*1/5,s);
		s.Format("Ŀ����� %d",m_targeSorce);
		dcMemory.SelectObject(&font2);
		size = dcMemory.GetTextExtent(s);
		dcMemory.TextOutA(((m_rectNumX*RECT_WIDTH+DEFAULT_FRAME_X)-size.cx)/2,
			(m_rectNumY*RECT_HEIGHT+DEFAULT_FRAME_Y+FZT_GAP*RECT_HEIGHT)*2/4,s);
	}
	
}
void CChildView::DrawInfo(CDC &dcMemory)
{	
	CBrush brush(FZT_BLUE);
	CFont font;
	font.CreatePointFont(120,_T("����Ȥ���"));
	dcMemory.SelectObject(&font);
	dcMemory.SelectObject(&brush);
	//dcMemory.Rectangle(0,0,rect_width*m_rectNumX,rect_height*FZT_GAP);
	CBrush *brushNull=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	dcMemory.SetTextColor(FZT_BLUE);
	dcMemory.SetBkMode(TRANSPARENT);
	CString s_score;
	if(m_chooseNum>1) s_score.Format("�÷�:%d %d����%d��",m_score,m_chooseNum,CalScore(m_chooseNum));
	else s_score.Format("�÷�:%d",m_score);
	dcMemory.TextOutA(2,4,s_score);
	s_score.Format("�ؿ�:%d Ŀ��:%d ��߷�:%d",m_stage,m_targeSorce,max_sorce);
	if(m_score>=m_targeSorce) 
	{
		CString s=s_score;
		s_score.Format("%s Ŀ����!",s);
	}
	if(m_isClassMode) dcMemory.TextOutA(2,4+RECT_HEIGHT,s_score);
}
void CChildView::DrawAllRect(CDC &dcMemory)
{
	for(int i=0;i<m_rectNumX;i++)
		for(int j=0;j<m_rectNumY;j++)
		{
			CBrush brush;
			if(rect_fzt[i][j].GetColor() != FZT_BGCOLOR)brush.CreateSolidBrush(rect_fzt[i][j].GetColor());
			else {continue;}//brush.CreateStockObject(NULL_BRUSH);}
			dcMemory.SelectObject(&brush);
			dcMemory.Rectangle(rect_fzt[i][j].x,rect_fzt[i][j].y,rect_fzt[i][j].x+rect_width,rect_fzt[i][j].y+rect_height);

		}
}
void CChildView::DrawChooseRect(CDC &dcMemory)
{
	if(m_chooseNum>0)//m_chooseNum > 1)//ֻ��1�鱻ѡ��ʱ�ܷ����ѡ�п�
	{	
		for(int i=0;i<m_rectNumX;i++)
			for(int j=0;j<m_rectNumY;j++)
			{
				if(rect_fzt[i][j].IsChoose()&&rect_fzt[i][j].IsAlive())
				{
					CBrush brush(rect_fzt[i][j].GetColor());
					dcMemory.SelectObject(&brush);
					dcMemory.Rectangle(rect_fzt[i][j].x,rect_fzt[i][j].y,rect_fzt[i][j].x+rect_width,rect_fzt[i][j].y+rect_height);
				}
			}
	}
}
void CChildView::DrawAnimation(CDC &dcMemory)
{
	
	p=pent;
	pre=new CPentagram;
	for(int i=0;p!=NULL;i++)
	{
		CBrush brush(p->GetColor());
		dcMemory.SelectObject(brush);
		dcMemory.Polygon(p->pts,10);
		if(p->pts[0].x<0 || p->pts[0].x>(m_rectNumX+1)*rect_width || p->pts[0].y > (m_rectNumY+1)*rect_height)//�ڵ㳬����Ļ��ɾ��
		{	
			if(pent==p) {pent=pent->next;delete p;p=pent;}//��ͷ�ڵ�Ϊ�ա�����
			else 
			{
				pre->next = p->next;
				delete p;
				p=pre->next;
			}

		}
		else
		{
			pre=p;
			p=p->next;
		}
	}
}
void CChildView::DrawExtraInfo(CDC &dcMemory)
{
	if (m_gameIsOver)//��ʾ���⽱����Ϣ
	{
		CFont font;
		font.CreatePointFont(m_rectNumX*23,_T("����Ȥ���"));
		dcMemory.SelectObject(&font);
		CString s;
		int sore;
		sore = 2000-20*num_rest*num_rest;
		if (sore<0)
		{
			sore=0;
		}
		s.Format("���⽱�� %d",sore);
		CSize size = dcMemory.GetTextExtent(s);
		dcMemory.TextOutA(((m_rectNumX*RECT_WIDTH+DEFAULT_FRAME_X)-size.cx)/2,
			(m_rectNumY*RECT_HEIGHT+DEFAULT_FRAME_Y+FZT_GAP*RECT_HEIGHT)*1/5,s);
	}
}
void CChildView::DrawGoodInfo(CDC &dcMemory)
{
	if (m_isShowGoodInfo)
	{
		CString s;
		if(m_goodnun<5) return;
		switch(m_goodnun)
		{
		case 5:
			s="����";break;
		case 6:
			s="��";break;
		case 7:
			s="Ư��";break;
		case 8:
			s="������";break;
		default:
			s="˧����";break;
		}
		CFont font;
		font.CreatePointFont(m_rectNumX*20,_T("����Ȥ���"));
		dcMemory.SelectObject(&font);
		dcMemory.SetTextColor(FZT_RED);
		CSize size = dcMemory.GetTextExtent(s);
		dcMemory.TextOutA(((m_rectNumX*RECT_WIDTH+DEFAULT_FRAME_X)-size.cx)/2,
			(m_rectNumY*RECT_HEIGHT+DEFAULT_FRAME_Y+FZT_GAP*RECT_HEIGHT)*1/5,s);
	}
}

void CChildView::StopAnimation()
{
	while(pent!=NULL)
	{
		p=pent;
		pent=pent->next;
		delete p;
		m_time=0;
		KillTimer(2);
		oldc=FZT_BGCOLOR;
	}
	
}

void CChildView::InitLevel()//��ʼ���ؿ�
{
	m_isIntoStage=true;
	m_stage=1;
	m_targeSorce=1000;

}
void CChildView::Init(void)//��ʼ�����ο�
{
	time_t t;
	time(&t);
	srand(t);
	m_score=0;
	m_gameIsOver = false;
	num_rest=0;
	m_isShowGoodInfo=false;
	for (int i=0;i<m_rectNumX;i++)
	{
		for(int j =0;j<m_rectNumY;j++)  
		{
			rect_fzt[i][j].SetPoint((i)*rect_width,(j+FZT_GAP)*rect_height);
			rect_fzt[i][j].oldx=rect_fzt[i][j].x;
			rect_fzt[i][j].oldy=rect_fzt[i][j].y;
			rect_fzt[i][j].SetAlive(true);
			rect_fzt[i][j].SetColor(ChooseColor());
		}
	}
	m_isIntoStage=false;
	max_sorce =AfxGetApp()->GetProfileIntA("save","MAX",0);
}


COLORREF CChildView::ChooseColor(void)
{
	int r;
	r=rand()%m_species;
	return m_Rectcolor[r];
}

void CChildView::KillMouseAnimation()
{
	for (int i=0;i<m_rectNumX;i++)
	{
		for(int j =0;j<m_rectNumY;j++)
		{
			rect_fzt[i][j].x=rect_fzt[i][j].oldx;
			rect_fzt[i][j].y=rect_fzt[i][j].oldy;
			KillTimer(3);
			//SetTimer(3,16,NULL);//ʱ�������������ƶ������ٶȣ�ԽСԽ��,��Ҫ

		}
	}
	
}
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// �õ������ָ�ľ���
	if(m_isIntoStage) return ;
	int x=point.x/rect_width;
	int y=point.y/rect_height-FZT_GAP;
	
	if(oldc==rect_fzt[x][y].GetColor() || !rect_fzt[x][y].IsAlive()) 
	{
		if( !rect_fzt[x][y].IsAlive()) 
		{
			oldc = rect_fzt[x][y].GetColor();
			m_chooseNum=0;
			nowx = x;
			nowy = y;
		}
		
		return;//�趨Ϊ����굽��ľ���ʱ������Ч
	}
	nowx = x;
	nowy = y;
	//if(!rect_fzt[x][y].IsAlive()) return;
	if(x!=oldx ||  y!=oldy ) //��ֹ�Խ�����ͬ��ɫ��������������bug
	{

		sound->PlaySound(STATE_MOUSEMOVE);

	}
	for (int i=0;i<m_rectNumX;i++)
	{
		for(int j =0;j<m_rectNumY;j++)
		{
			rect_fzt[i][j].SetSameColor(false);
			//rect_fzt[i][j].x=rect_fzt[i][j].oldx;
			//rect_fzt[i][j].y=rect_fzt[i][j].oldy;
			
			//KillTimer(3);
			//
			

		}
	}
	
	if(x>=m_rectNumX || y>=m_rectNumY || y<0 )
	{
		m_chooseNum=0;
		return ;
	}
	
	COLORREF c=rect_fzt[x][y].GetColor();
	m_chooseNum=1;
	rect_fzt[x][y].SetSameColor(true);
	if(rect_fzt[x][y].IsAlive())	ChooseRect(x,y,c);
	else m_chooseNum=0;
	if(oldc!=rect_fzt[x][y].GetColor())
	{
		KillMouseAnimation();
	}
	
	if(m_chooseNum>1)
	{
		
		timer_num=0;//����kill��Ϻ�
		SetTimer(3,16,NULL);
	//ʱ�������������ƶ������ٶȣ�ԽСԽ��,��Ҫ
	
	}
	oldx=x;
	oldy=y;
	
	oldc = rect_fzt[x][y].GetColor();
	CWnd::OnMouseMove(nFlags, point);
}
void CChildView::ChooseRect(int x,int y,COLORREF c)//ѡ�������ľ��ο�
{
	if(x+1<m_rectNumX &&rect_fzt[x+1][y].IsSameColor(c)&& !rect_fzt[x+1][y].IsChoose()){m_chooseNum++;rect_fzt[x+1][y].SetSameColor(true); ChooseRect(x+1,y,c);}
	if(x-1>=0 && rect_fzt[x-1][y].IsSameColor(c)&&!rect_fzt[x-1][y].IsChoose()){m_chooseNum++;rect_fzt[x-1][y].SetSameColor(true); ChooseRect(x-1,y,c);}
	if(y+1<m_rectNumY && rect_fzt[x][y+1].IsSameColor(c)&& !rect_fzt[x][y+1].IsChoose()){m_chooseNum++;rect_fzt[x][y+1].SetSameColor(true); ChooseRect(x,y+1,c);}
	if(y-1>=0 && rect_fzt[x][y-1].IsSameColor(c)&&!rect_fzt[x][y-1].IsChoose()){m_chooseNum++;rect_fzt[x][y-1].SetSameColor(true); ChooseRect(x,y-1,c);}
}
bool CChildView::IsOver()//ֻ�������ڿ���ɫ�Ƕ���ͬ����
{
	for(int i=0;i<m_rectNumX;i++)
	{
		for(int j=0;j<m_rectNumY;j++)
		{
			if (rect_fzt[i][j].IsAlive())
			{
				if(i+1<m_rectNumX &&rect_fzt[i+1][j].IsAlive() && rect_fzt[i+1][j].IsSameColor(rect_fzt[i][j].GetColor()) ) return true;
				if(i-1>=0 &&rect_fzt[i-1][j].IsAlive()&& rect_fzt[i-1][j].IsSameColor(rect_fzt[i][j].GetColor()))	return true;
				if(j+1<m_rectNumY &&rect_fzt[i][j+1].IsAlive()&& rect_fzt[i][j+1].IsSameColor(rect_fzt[i][j].GetColor()))return true;
				if(j-1>=0 &&rect_fzt[i][j-1].IsAlive()&& rect_fzt[i][j-1].IsSameColor(rect_fzt[i][j].GetColor()))return true;
			}

		}
	}
	return false;

}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_isIntoStage) return ;
	// �õ������ָ�ľ���
	int x=point.x/rect_width;
	int y=point.y/rect_height-FZT_GAP;
	if(x>=m_rectNumX || y>=m_rectNumY || y<0 || !rect_fzt[x][y].IsAlive()) return ;
	color_btndown=rect_fzt[x][y].GetColor();
	m_chooseNum=0;
	for (int i=0;i<m_rectNumX;i++)
	{
		for(int j =0;j<m_rectNumY;j++)
		{
			rect_fzt[i][j].SetSameColor(false);
		}
	}
	ChooseRect(x,y,color_btndown);
	if(m_chooseNum >1)
	{
		KillMouseAnimation();
		StopAnimation();//ֹ֮ͣǰ���Ƕ���
		GetUpdateRect();
		m_isShowGoodInfo=true;
		m_goodnun=m_chooseNum;
		pent = new CPentagram;
		pent->SetCenterPoint(point.x,point.y);
		pent->SetSpeed(10,10);
		pent->SetColor(color_btndown);
		p=pent;
		//oldc = color_btndown;
		EraseRect(x,y,color_btndown);
		rect_fzt[x][y].EraseRect();
		SetTimer(4,100,NULL);//������������ʱ��
		SetTimer(2,500,NULL);//����λ�ø���ʱ��
		m_score+=CalScore(m_chooseNum);
		if (m_isClassMode && m_score>max_sorce)
		{
			max_sorce = m_score;
			AfxGetApp()->WriteProfileInt("save","MAX",m_score);
		}
		sound->PlaySound(STATE_BTUDOWN);
		m_chooseNum=0;
		
		SetTimer(TIMER_SHOWGOODINFO,1000,NULL);
		//if(pent==NULL)GetUpdateRect();
	//	OnMouseMove(nFlags,point);
		
	}


	
	CWnd::OnLButtonDown(nFlags, point);
}
void CChildView::EraseRect(int x,int y,COLORREF c)//�ݹ����
{
	if(x+1<m_rectNumX &&rect_fzt[x+1][y].IsSameColor(c)&& rect_fzt[x+1][y].IsAlive())
	{
		CPoint point((x+1)*rect_width,(y+FZT_GAP)*rect_height);
		NewPent(point,c);
		rect_fzt[x+1][y].EraseRect(); 
		EraseRect(x+1,y,c);
	}
	if(x-1>=0 && rect_fzt[x-1][y].IsSameColor(c)&&rect_fzt[x-1][y].IsAlive())
	{
		
		CPoint point((x-1)*rect_width,(y+FZT_GAP)*rect_height);
		NewPent(point,c);
		rect_fzt[x-1][y].EraseRect();
		EraseRect(x-1,y,c);
	}
	if(y+1<m_rectNumY && rect_fzt[x][y+1].IsSameColor(c)&& rect_fzt[x][y+1].IsAlive())
	{
		CPoint point((x)*rect_width,(y+1+FZT_GAP)*rect_height);
		NewPent(point,c);
		rect_fzt[x][y+1].EraseRect();
		EraseRect(x,y+1,c);
	}
	if(y-1>=0 && rect_fzt[x][y-1].IsSameColor(c)&&rect_fzt[x][y-1].IsAlive())
	{
		CPoint point((x+1)*rect_width,(y-1+FZT_GAP)*rect_height);
		NewPent(point,c);
		rect_fzt[x][y-1].EraseRect();
		EraseRect(x,y-1,c);
	}
}
void CChildView::NewPent(CPoint point,COLORREF c)
{
	int vx;
	int vy;
	vx=rand()%3+3;
	vy=rand()%20+20;
	p->next = new CPentagram;
	p=p->next;
	p->SetSpeed(vx,vy);
	p->SetCenterPoint(point);
	p->SetColor(c);
	p->next = new CPentagram;
	p=p->next;
	p->SetSpeed(-vx,vy);
	p->SetCenterPoint(point);
	p->SetColor(c);
}
void CChildView::GetUpdateRect()
{//���������жϾ����Ƿ��false�������ƶ�����
	
	for(int k=0;k<m_rectNumY;k++)
	{	
		for(int i=m_rectNumX-1;i>=0;i--)
		{
			for(int j=m_rectNumY-1;j>0;j--)
			{
				if (!rect_fzt[i][j].IsAlive())
				{
					SwapRect(rect_fzt[i][j],rect_fzt[i][j-1]);
				}
			//	rect_fzt[i][j].SetSameColor(false);
			}
			
		}
	}
	//ɨ�������һ�У��п���������ƶ�����
	int emptynum = 0;
	for(int i=0;i<m_rectNumX-emptynum;i++)
	{
		if (!rect_fzt[i][m_rectNumY-1].IsAlive())//���β����
		{
			for(int j=i+1;j<m_rectNumX-emptynum;j++)
				for(int k=0;k<m_rectNumY;k++)
				{
					SwapRect(rect_fzt[j][k],rect_fzt[j-1][k]); 
				}
				i=-1;//���¼��,��ֹһ�ζ������,��Ϊ������i++,����i��Ϊ-1
				++emptynum;//������
		}

	}
	//m_chooseNum=0;
	KillMouseAnimation();

	
}
void CChildView::SwapRect(ClassRect_fzt &a,ClassRect_fzt &b)
{
	//�������ε���ɫ�����״̬����
	COLORREF r = a.GetColor();
	bool l = a.IsAlive();
	a.SetColor(b.GetColor());
	a.SetAlive(b.IsAlive());
	b.SetColor(r);
	b.SetAlive(l);
}


void CChildView::OnNewGame()/*����������Ϸ*/
{
	Init();/*��ʼ�����������ɾ��ο�*/
	m_isIntoStage=false;
	if(m_isClassMode) 
	{
		InitLevel();
		SetTimer(TIMER_INFOINTOTRAGE,2000,NULL);
	}
	StopAnimation();
	for (int i=3;i<6;i++)
	{
		KillTimer(i);
	}
	//Invalidate(TRUE);
}
int CChildView::ReadFile(CString s_name)
{
	OFSTRUCT ofn;
	if(OpenFile(s_name,&ofn,OF_EXIST) == HFILE_ERROR) 
	{
		return 0;//�ж��ļ��Ƿ����
	}
	CFile file(s_name, CFile::modeRead | CFile::typeBinary );


	file.Read(&m_rectNumX,sizeof(int));
	file.Read(&m_rectNumY,sizeof(int));


	file.Read(&m_isClassMode,sizeof(bool));
//	file.Read(&m_isIntoStage,sizeof(bool));
	file.Read(&m_stage,sizeof(int));
	file.Read(&m_targeSorce,sizeof(int));


	file.Read(&m_score,sizeof(int));
	
	file.Read(&m_species,sizeof(int));
	file.Read(m_Rectcolor,sizeof(m_Rectcolor));
	file.Read(rect_fzt,sizeof(rect_fzt));

	int ln;
	file.Read(&ln,sizeof(int));
	file.Read(s_effectName.GetBuffer(ln+1),ln+1);
	s_effectName.ReleaseBuffer(ln+1);//�ͷ�������ڴ�
	file.Read(&ln,sizeof(int));
	file.Read(s_effectPath.GetBuffer(ln+1),ln+1);
	s_effectPath.ReleaseBuffer(ln+1);
	file.Read(&ln,sizeof(int));
	file.Read(s_musicName.GetBuffer(ln+1),ln+1);
	s_musicName.ReleaseBuffer(ln+1);
	file.Read(&ln,sizeof(int));
	file.Read(s_musicPath.GetBuffer(ln+1),ln+1);
	s_musicPath.ReleaseBuffer(ln+1);
	file.Close();
	for(int i=0;i<m_rectNumX;i++)//��ֹ�Ӯ��^���б��������bug
		for(int j=0;j<m_rectNumY;j++)
		{
			rect_fzt[i][j].x=rect_fzt[i][j].oldx;
			rect_fzt[i][j].y=rect_fzt[i][j].oldy;
			rect_fzt[i][j].SetSameColor(false);
		}
	StopAnimation();
	for(int i=3;i<6;i++)
		KillTimer(i);
	m_gameIsOver = false;
	num_rest=0;
	m_isIntoStage=false;
//	GetUpdateRect();
	return 1;
}
void CChildView::WriteFile(CString s_name)
{
	int ln=0;
	CFile file(s_name,CFile::modeCreate | CFile::modeWrite | CFile::typeBinary );

	file.Write(&m_rectNumX,sizeof(int));
	file.Write(&m_rectNumY,sizeof(int));


	file.Write(&m_isClassMode,sizeof(bool));
//	file.Write(&m_isIntoStage,sizeof(bool));
	file.Write(&m_stage,sizeof(int));
	file.Write(&m_targeSorce,sizeof(int));


	file.Write(&m_score,sizeof(int));
	
	file.Write(&m_species,sizeof(int));
	file.Write(m_Rectcolor,sizeof(m_Rectcolor));

	file.Write(rect_fzt,sizeof(rect_fzt));

	ln=s_effectName.GetLength();
	file.Write(&ln,sizeof(int));
	file.Write(s_effectName,ln+1);
	ln=s_effectPath.GetLength();
	file.Write(&ln,sizeof(int));
	file.Write(s_effectPath,ln+1);
	ln=s_musicName.GetLength();
	file.Write(&ln,sizeof(int));
	file.Write(s_musicName,ln+1);
	ln=s_musicPath.GetLength();
	file.Write(&ln,sizeof(int));
	file.Write(s_musicPath,ln+1);
	file.Close();
}
void CChildView::OnSaveGame()
{
	WriteFile("save.fzt");
}
void CChildView::OnReadGame()
{
	ReadFile("save.fzt");
	ChangeWindow();
	sound->StopSound();
	sound->OpenEffect(s_effectPath);
	sound->OpenMusic(s_musicPath);
}
void CChildView::OnSaveAs()
{
	CFileDialog fileDlg(false,NULL,"save.fzt",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"fzt(*.fzt)|*.fzt"); //���ļ��Ի���
	fileDlg.m_ofn.lpstrTitle="������Ϸ";
	if (IDOK==fileDlg.DoModal())
	{
		CString s=fileDlg.GetPathName();
		WriteFile(s);
	}
}
void CChildView::OnReadAs()
{
	CFileDialog fileDlg(true,NULL,"",OFN_ALLOWMULTISELECT,"fzt(*.fzt)|*.fzt"); //���ļ��Ի���
	fileDlg.m_ofn.lpstrTitle="��ȡ��Ϸ";
	if (IDOK==fileDlg.DoModal())
	{
		CString s=fileDlg.GetPathName();
		ReadFile(s);
		ChangeWindow();
		sound->StopSound();
		sound->OpenEffect(s_effectPath);
		sound->OpenMusic(s_musicPath);
	}
}
void CChildView::OnSetGame()//��Ϸ����
{
	CSetDialog setDialog;
	setDialog.m_DialogRectNumX = m_rectNumX;
	setDialog.m_DialogRectNumY = m_rectNumY;
	setDialog.m_rectSpecies = m_species;
	for(int i=0;i<12;i++)
		setDialog.colorArray[i]=m_Rectcolor[i];
	if(IDOK == setDialog.DoModal())
	{
		m_rectNumX = setDialog.m_DialogRectNumX;
		m_rectNumY = setDialog.m_DialogRectNumY;
		m_species = setDialog.m_rectSpecies;
		for(int i=0;i<MAX_COLORNUM;i++)
			m_Rectcolor[i]=setDialog.colorArray[i];
		ChangeWindow();
		Init();
	}
}

void CChildView::ChangeWindow()
{
	CRect rect;
	CString s;
	GetParent()->GetWindowRect(&rect);//��GetParent()�õ����ǳ����λ�ã�����õ�����client��λ��
	//GetDesktopWindow()->GetWindowRect(&rect);
	int x = (rect.Width()-m_rectNumX*RECT_WIDTH+DEFAULT_FRAME_X)/2;
	int y = (rect.Height()-m_rectNumY*RECT_HEIGHT+DEFAULT_FRAME_Y)/2;
	CPoint p(0,0);
	//ClientToScreen(&rect);
	GetParent()->MoveWindow(rect.left,rect.top,m_rectNumX*RECT_WIDTH+DEFAULT_FRAME_X,m_rectNumY*RECT_HEIGHT+DEFAULT_FRAME_Y+FZT_GAP*RECT_HEIGHT);	
	GetWindowRect(&rect);
}
int CChildView::CalScore(int num)
{
	int base=5;
	int pro =1;
	return base*pro* m_chooseNum*num;
}
int CChildView::SubGameOver()
{
	//StopAnimation();
	int flag = 1;
	for(int i=0;i<m_rectNumX;i++)
		for(int j=0;j<m_rectNumY;j++)
		{
			if(rect_fzt[i][j].IsAlive() )//&& 1==flag)
			{
				
				if(pent==NULL)//num_rest==0)
				{
					pent = new CPentagram;
					p=pent;
					pent->SetCenterPoint(rect_fzt[i][j].x+rect_width/2,rect_fzt[i][j].y+rect_height/2);
					pent->SetSpeed(rand()%3+3,rand()%10+20);
					pent->SetColor(rect_fzt[i][j].GetColor());
					p->next = new CPentagram;
					p=p->next;
					p->SetCenterPoint(rect_fzt[i][j].x,rect_fzt[i][j].y);
					p->SetSpeed(-(rand()%3+3),rand()%20+10);
					p->SetColor(rect_fzt[i][j].GetColor());
					pre = pent;
				}
				else
				{
					if(p==NULL)
					{
						pre=pent;
						while(pre->next!=NULL)
						{
							pre=pre->next;
						}
						p=pre;
					}
					p->next = new CPentagram;
					p=p->next;
					p->SetCenterPoint(rect_fzt[i][j].x+rect_width/2,rect_fzt[i][j].y+rect_height/2);
					p->SetSpeed(rand()%3+3,rand()%10+20);
					p->SetColor(rect_fzt[i][j].GetColor());
					pre=p;
					p->next = new CPentagram;
					p=p->next;
					p->SetCenterPoint(rect_fzt[i][j].x,rect_fzt[i][j].y);
					p->SetSpeed(-(rand()%3+3),rand()%20+10);
					p->SetColor(rect_fzt[i][j].GetColor());
				}
				
				rect_fzt[i][j].EraseRect();
				//SetTimer(4,100,NULL);
			//	if(num_rest==15)KillTimer(5);
				flag=0;
				num_rest++;
				return -1;
			}
		/*	else if(rect_fzt[i][j].IsAlive() && 0==flag)
			{
				num_rest++;
				CPoint point(rect_fzt[i][j].x,rect_fzt[i][j].y);
				NewPent(point);
				rect_fzt[i][j].EraseRect();
			}*/
		}
		KillTimer(5);//����������Ϲرն�ʱ��
		if(m_score<m_targeSorce || !m_isClassMode) 
		{
			//s.Format("ʣ��%d��,��%d��,�ܷ���%d",num_rest,sore,m_score);
			m_isIntoStage=true;
			Invalidate(TRUE);
			//SetTimer(TIMER_INFOINTOTRAGE,10,NULL);
			//MessageBox(s);
			//Init();
			//if(m_isClassMode)InitLevel();
		}
		else 
		{
			int n1=m_score;
			int n2=m_stage;
			int n3=m_targeSorce;
			Init();
			m_score=n1;
			m_stage=n2+1;
			if(m_stage<5)m_targeSorce=n3+m_stage*1000;
			else m_targeSorce=n3+4000;
			m_isIntoStage=true;
			SetTimer(TIMER_INFOINTOTRAGE,2000,NULL);
			Invalidate(TRUE);
			
		}

		
		return flag;
}
int CChildView::GameOver(void)
{
	GetUpdateRect();
	m_gameIsOver = true;
	
	
	StopAnimation();
	p=NULL;
	pent=NULL;
//	SubGameOver();
	SetTimer(5,100,NULL);
	SetTimer(4,100,NULL);
	return 0;
}


void CChildView::OnSetSound()
{
	CSetSoundDiagle soundDiagle;
	soundDiagle.s_effectName = s_effectName;
	soundDiagle.s_musicName = s_musicName;
	soundDiagle.s_effectPath = s_effectPath;
	soundDiagle.s_musicPath = s_musicPath;
	if(IDOK == soundDiagle.DoModal())
	{
		s_effectName = soundDiagle.s_effectName;
		s_musicName = soundDiagle.s_musicName;
		s_effectPath = soundDiagle.s_effectPath;
		s_musicPath = soundDiagle.s_musicPath;
		sound->StopSound();
		sound->OpenEffect(soundDiagle.s_effectBuf);
		sound->OpenMusic(soundDiagle.s_musicBuf);
	}
}
int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetTimer(0,1,NULL);//��ʼ�����ڣ�ֻ����һ��
	SetTimer(1,16,NULL);//ˢ�¼�ʱ��������֡��
	if(m_isClassMode)SetTimer(TIMER_INFOINTOTRAGE,2000,NULL);
	return 0;
}
void CChildView::MoveAnimation()
{
	if (1)//m_chooseNum>1)//����ȥ���ж���
	{


		for (int i=0;i<m_rectNumX;i++)
		{
			for(int j=0;j<m_rectNumY;j++)
			{
				if(rect_fzt[i][j].IsChoose() && timer_num<rect_height/2)
				{
					rect_fzt[i][j].y--;

				}else if(rect_fzt[i][j].IsChoose() && timer_num>=rect_height/2 && timer_num<rect_height)
				{
					rect_fzt[i][j].y++;
				}
				if(rect_fzt[i][j].IsChoose() && timer_num>=rect_height && timer_num<(rect_height*5/4))
				{
					rect_fzt[i][j].y--;

				}else if(rect_fzt[i][j].IsChoose() && timer_num>=rect_height*5/4)
				{
					rect_fzt[i][j].y++;
				}
			}
		}
		if(timer_num<rect_height*6/4-1) timer_num++;
		else 
		{
			timer_num=0;
			for (int i=0;i<m_rectNumX;i++)
			{
				for(int j=0;j<m_rectNumY;j++)
				{
					rect_fzt[i][j].x=rect_fzt[i][j].oldx;
					rect_fzt[i][j].y=rect_fzt[i][j].oldy;
				}
			}
			KillTimer(3);
		}
	}
	//Invalidate(FALSE);
}

void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	
	switch(nIDEvent)
	{
	case 0:
		KillTimer(0);
		if(0!=ReadFile("save_exit.fzt"))
			ChangeWindow();		
		break;
	case TIMER_REFRESH:
	//	if(pent==NULL)GetUpdateRect();
	
		Invalidate(FALSE);//ר��ˢ�½���
		break;
	case 2://���¾���λ��
		if(!m_gameIsOver) 
		{
			GetUpdateRect();//���������������
			m_chooseNum=1;
			for (int i=0;i<m_rectNumX;i++)
			{
				for(int j =0;j<m_rectNumY;j++)
				{
					rect_fzt[i][j].SetSameColor(false);
				}
			}
			rect_fzt[nowx][nowy].SetSameColor(true);
			ChooseRect(nowx,nowy,rect_fzt[nowx][nowy].GetColor());
			if (!IsOver())//�ж��Ƿ����������ӣ������������else����ֻ�ж�һ�Σ����������ÿ�ε�����ж�
			{

				GameOver();
			}
			KillTimer(2);
		}
		break;
	case 3://����ƶ������Ŀ���
		MoveAnimation();
		break;
	case 4://������������
		p=pent;
		for (int i=0;p!=NULL;i++)
		{
			p->Run();
			p=p->next;
		}
		if(pent==NULL && !m_gameIsOver)
		{
			KillTimer(4);
			oldc=FZT_BGCOLOR;
		}
		break;
	
	case 5:
		SubGameOver();
		break;
	case TIMER_INFOINTOTRAGE:
		m_isIntoStage=false;
		Invalidate(TRUE);
		KillTimer(TIMER_INFOINTOTRAGE);
		break;
	case TIMER_SHOWGOODINFO:
		m_isShowGoodInfo=false;
		KillTimer(TIMER_SHOWGOODINFO);
		break;

	}
	
	CWnd::OnTimer(nIDEvent);
}


void CChildView::OnUpdateSetGame(CCmdUI *pCmdUI)
{
	if(m_isClassMode)
	{
		pCmdUI->Enable(false);
	}
	else pCmdUI->Enable(true);
	// TODO: �ڴ������������û����洦��������
}


void CChildView::OnUpdateSetSound(CCmdUI *pCmdUI)
{
	/*if(m_isClassMode)
	{
		pCmdUI->Enable(false);
	}
	else pCmdUI->Enable(true);*/
}


void CChildView::OnClassicmode()
{
	if(m_isClassMode)
	{
		m_isClassMode=false;
	//	((CMainFrame *)GetParent())->GetMenu()->CheckMenuItem(ID_CLASSICMODE,MF_UNCHECKED);
	}
	else 
	{
		m_isClassMode=true;
	//	((CMainFrame *)GetParent())->GetMenu()->CheckMenuItem(ID_CLASSICMODE,MF_CHECKED);
		m_rectNumX = 10;
		m_rectNumY = 10;
		m_species = FZT_SPECIES;
		for(int i=0;i<MAX_COLORNUM;i++)
			m_Rectcolor[i] = ColorArray[i];
		ChangeWindow();
		Init();
		InitLevel();
		SetTimer(TIMER_INFOINTOTRAGE,2000,NULL);
	}
}


void CChildView::OnTip()
{
	CCtipsDlg tipDlg;
	tipDlg.DoModal();
}


void CChildView::OnUpdateClassicmode(CCmdUI *pCmdUI)
{
	if(m_isClassMode)
	{
		((CMainFrame *)GetParent())->GetMenu()->CheckMenuItem(ID_CLASSICMODE,MF_CHECKED);
	}
	else 
	{
		((CMainFrame *)GetParent())->GetMenu()->CheckMenuItem(ID_CLASSICMODE,MF_UNCHECKED);
	}
}
