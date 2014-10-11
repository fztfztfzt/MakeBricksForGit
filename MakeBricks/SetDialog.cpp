// SetDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MakeBricks.h"
#include "SetDialog.h"
#include "afxdialogex.h"
#include "defhead.h"

// CSetDialog �Ի���

IMPLEMENT_DYNAMIC(CSetDialog, CDialogEx)
COLORREF CSetDialog::defColorArray[12]={
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
CSetDialog::CSetDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetDialog::IDD, pParent)
	, m_rectSpecies(0)
{

	//  m_DialogRectNum = _T("");
	m_DialogRectNum = 0;


	//  m_DialogRectSep = 0;
	m_DialogRectNumX = 0;
	m_DialogRectNumY = 0;
}

CSetDialog::~CSetDialog()
{
}

void CSetDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_RECTNUM, m_DialogRectNum);
	//	DDX_Text(pDX, IDC_RECTNUM, m_DialogRectNum);
	//	DDV_MinMaxInt(pDX, m_DialogRectNum, 5, 40);
	//  DDX_CBIndex(pDX, IDC_RECTSEPECIES, m_DialogRectSep);
	//  DDV_MinMaxInt(pDX, m_DialogRectSep, 2, 12);
	DDX_Control(pDX, IDC_RECTSEPECIES, m_RectSpe);
	DDX_Text(pDX, IDC_RECTNUMX, m_DialogRectNumX);
	DDV_MinMaxInt(pDX, m_DialogRectNumX, 5, 30);
	DDX_Text(pDX, IDC_RECTNUMY, m_DialogRectNumY);
	DDV_MinMaxInt(pDX, m_DialogRectNumY, 5, 30);
	for(int i=1;i<=12;i++)//�����ؼ����飬ע�������Դid
	{
		DDX_Control(pDX, i+1000, m_colorbtu[i-1]);
	}
}


BEGIN_MESSAGE_MAP(CSetDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSetDialog::OnBnClickedOk)
ON_CBN_SELCHANGE(IDC_RECTSEPECIES, &CSetDialog::OnSelchangeRectsepecies)
ON_CBN_EDITCHANGE(IDC_RECTSEPECIES, &CSetDialog::OnEditchangeRectsepecies)
ON_BN_CLICKED(IDC_DEF, &CSetDialog::OnBnClickedDef)
END_MESSAGE_MAP()



BOOL CSetDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	int index=0;
	CString str;
	for (int i=3;i<=12;i++)//��ʼ��combox;��ɫ����3��12
	{	
		str.Format("%d",i);
		m_RectSpe.AddString(str);
	}
	CString s;//�򿪶Ի���ʱ�Ѿ�ѡ�õ���ɫ��
	s.Format("%d",m_rectSpecies);
	index=m_RectSpe.FindString(index,s);
	m_RectSpe.SetCurSel(index);
	SetColorBtu();
	//���ض������ɫ��ť
	ShowColorBtu();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CSetDialog::OnBnClickedOk()
{

	CString s;
	m_RectSpe.GetWindowTextA(s);
	sscanf(s,"%d",&m_rectSpecies);//����int�;�������
	GetColorBtu();
	CDialogEx::OnOK();
}

void CSetDialog::OnSelchangeRectsepecies()
{
	int index = ((CComboBox*)GetDlgItem(IDC_RECTSEPECIES))->GetCurSel();
	((CComboBox*)GetDlgItem(IDC_RECTSEPECIES))->SetCurSel(index); 
	UpdateData(TRUE);
	GetColorBtu();
	ShowColorBtu();
	//ԭ�ȷ���������������ɫ��ť������
	/*CRect rect;
	CRect rect2;
	GetDlgItem(IDC_MFCCOLORBUTTON2)->GetWindowRect(&rect);
	ScreenToClient(rect);
	//	GetDlgItem(IDC_MFCCOLORBUTTON2)->GetClientRect(&rect);
	rect2 = rect;
	rect2.left=rect.right+10;
	int width=rect.right-rect.left;
	int height=rect.bottom-rect.top;
	rect2.right=rect2.left+width;


	CString str;
	m_RectSpe.GetWindowTextA(str);
	for(int i=0;i<m_rectSpecies-3;i++)
	{
		colorbut[i].DestroyWindow();

	}
	sscanf(str,"%d",&m_rectSpecies);
	DWORD style = m_colorbtu1.GetStyle();
	for(int i=0;i<m_rectSpecies-3;i++)
	{
		CString s;
		s.Format("%d",i);
		colorbut[i].Create(s,style,rect2,this,i);
		colorbut[i].ShowWindow(SW_SHOW);
		if(i==2)
		{
			GetDlgItem(IDC_MFCCOLORBUTTON1)->GetWindowRect(&rect);
			ScreenToClient(rect);
			rect2=rect;
			rect2.top +=height+10;
			rect2.bottom += height+10;

		}else
		{rect2.left+=width+10;
		rect2.right+=10+width;}
	}*/
}


void CSetDialog::OnEditchangeRectsepecies()
{
	//ԭ�ȷ���������������ɫ��ť������
	/*CRect rect;
	CRect rect2;
	GetDlgItem(IDC_MFCCOLORBUTTON2)->GetWindowRect(&rect);
	ScreenToClient(rect);
	//	GetDlgItem(IDC_MFCCOLORBUTTON2)->GetClientRect(&rect);
	rect2 = rect;
	rect2.left=rect.right+10;
	int width=rect.right-rect.left;
	int height=rect.bottom-rect.top;
	rect2.right=rect2.left+width;


	CString str;
	m_RectSpe.GetWindowTextA(str);
	for(int i=0;i<m_rectSpecies-3;i++)
	{
		colorbut[i].DestroyWindow();

	}
	sscanf(str,"%d",&m_rectSpecies);
	DWORD style = m_colorbtu1.GetStyle();
	for(int i=0;i<m_rectSpecies-3;i++)
	{
		colorbut[i].Create("1",style,rect2,this,i);
		colorbut[i].ShowWindow(SW_SHOW);
		if(i==2)
		{
			GetDlgItem(IDC_MFCCOLORBUTTON1)->GetWindowRect(&rect);
			ScreenToClient(rect);
			rect2=rect;
			rect2.top +=height+10;
			rect2.bottom += height+10;

		}else
		{rect2.left+=width+10;
		rect2.right+=10+width;}
	}*/
	//���ض������ɫ��ť
	GetColorBtu();
	ShowColorBtu();
	
}
void CSetDialog::ShowColorBtu()
{
	CString str;
	m_RectSpe.GetWindowTextA(str);
	sscanf(str,"%d",&m_rectSpecies);//�õ���������
	if(m_rectSpecies<3)//�����С����
	{
		m_rectSpecies=3;
	}
	else if(m_rectSpecies>12)
	{
		m_rectSpecies=12;
		m_RectSpe.SetCurSel(9);
	}
	for(int i=0;i<12;i++)//���ð�ť
	{
		m_colorbtu[i].ShowWindow(SW_SHOW);
	}

	for(int i=m_rectSpecies;i<12;i++)
	{
		
		m_colorbtu[i].ShowWindow(SW_HIDE);
		
	}
}

void CSetDialog::OnBnClickedDef()
{
	for(int i=0;i<12;i++)
	{
		colorArray[i]=defColorArray[i];
		m_colorbtu[i].SetColor(colorArray[i]);
	}
}
void CSetDialog::GetColorBtu()
{
	for(int i=0;i<12;i++)
	{
		colorArray[i]=m_colorbtu[i].GetColor();
	}
}
void CSetDialog::SetColorBtu()
{
	for(int i=0;i<12;i++)
	{
		m_colorbtu[i].SetColor(colorArray[i]);
	}
}