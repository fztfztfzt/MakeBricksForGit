// SetSoundDiagle.cpp : 实现文件
//

#include "stdafx.h"
#include "MakeBricks.h"
#include "SetSoundDiagle.h"
#include "afxdialogex.h"
#include "Mmsystem.h"
#pragma comment(lib,"winmm.lib")

// CSetSoundDiagle 对话框

CString musicname[]=
{
	"act.wav",
	"bomb1.wav",
	"bomb2.wav",
	"breakplate.wav",
	"Cautom.wav",
	"charge1.wav",
	"charge2.wav",
	"diescream.wav",
	"fire.wav",
	"Glass.wav",
	"glassbreak.wav",
	"hit.wav",
	"item.wav",
};
CString effectname[]=
{
	"act1.wav",
	"act2.wav",
	"act3.wav",
	"act4.wav",
	"act5.wav",
	"Cautom.wav",
	"charge.wav",
	"Cursor.wav",
	"Decision.wav",
	"drip.wav",
	"gold.wav",
};
IMPLEMENT_DYNAMIC(CSetSoundDiagle, CDialogEx)

CSetSoundDiagle::CSetSoundDiagle(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetSoundDiagle::IDD, pParent)
{
	othereffect=0;
	othermusic=0;
	m_edit1 = _T("");
	m_edit2 = _T("");
}

CSetSoundDiagle::~CSetSoundDiagle()
{
}

void CSetSoundDiagle::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_combo2);
	DDX_Control(pDX, IDC_COMBO3, m_combo3);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
}


BEGIN_MESSAGE_MAP(CSetSoundDiagle, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CSetSoundDiagle::OnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CSetSoundDiagle::OnSelchangeCombo3)
	ON_BN_CLICKED(IDOK, &CSetSoundDiagle::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CSetSoundDiagle::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSetSoundDiagle::OnBnClickedButton2)
END_MESSAGE_MAP()


// CSetSoundDiagle 消息处理程序


BOOL CSetSoundDiagle::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	int index;
	for(int i=0;i<11;i++)
		m_combo2.AddString(effectname[i]);
	if((index=m_combo2.FindString(0,s_effectName))==CB_ERR)
	{
		m_edit1 = s_effectName;
		othereffect=1;
	}else m_combo2.SetCurSel(index);
	for(int i=0;i<12;i++)
		m_combo3.AddString(musicname[i]);
	if((index=m_combo3.FindString(0,s_musicName))==CB_ERR)
	{
		m_edit2 = s_musicName;
		othermusic=1;
	}else m_combo3.SetCurSel(index);
	// TODO:  在此添加额外的初始化
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSetSoundDiagle::OnSelchangeCombo2()
{
	int index = m_combo2.GetCurSel();
	 m_combo2.SetCurSel(index);
	UpdateData(TRUE);//更新索引
	CString s;
	m_combo2.GetLBText(index,s_effectBuf);
	s.Format("open res\\effect\\%s alias effectTemp",s_effectBuf);
	mciSendString(s,NULL,0,NULL);
	mciSendString("play effectTemp from 0",NULL,0,NULL);
	Sleep(500);//给音效时间
	mciSendString("close effectTemp",NULL,0,NULL);
	othereffect=0;
}


void CSetSoundDiagle::OnSelchangeCombo3()
{
	int index = m_combo3.GetCurSel();
	m_combo3.SetCurSel(index);
	UpdateData(TRUE);//更新索引
	CString s;
	m_combo3.GetLBText(index,s_musicBuf);

	s.Format("open res\\music\\%s alias musicTemp",s_musicBuf);
	mciSendString(s,NULL,0,NULL);
	mciSendString("play musicTemp from 0",NULL,0,NULL);
	Sleep(500);//给音效时间
	mciSendString("close musicTemp",NULL,0,NULL);
	othermusic=0;
	
}


void CSetSoundDiagle::OnBnClickedOk()
{
	CString s;
	int index;
	if (othereffect==0)
	{
		index = m_combo2.GetCurSel();
		m_combo2.GetLBText(index,s);
		s_effectBuf.Format("res\\effect\\%s",s);
		s_effectName = s;
		s_effectPath = s_effectBuf;
	}
	else 
	{
		s_effectBuf = s_effectPath;
	}
	if(othermusic==0)
	{
		index = m_combo3.GetCurSel();
		m_combo3.GetLBText(index,s);
		s_musicBuf.Format("res\\music\\%s",s);
		s_musicName=s;
		s_musicPath=s_musicBuf;
	}
	else
	{
		s_musicBuf=s_musicPath;
	}
	CDialogEx::OnOK();
}


void CSetSoundDiagle::OnBnClickedButton1()
{
	CFileDialog file(true,NULL,NULL,OFN_ALLOWMULTISELECT,"wav(*.wav)|*.wav");
	file.m_ofn.lpstrTitle="选择移动时音效";
	if(file.DoModal() == IDOK)
	{
		s_effectName = file.GetFileName();
		s_effectPath = file.GetPathName();
		if(s_effectPath!="")
		{
			othereffect=1;
		}
		m_edit1 = s_effectName;
		UpdateData(FALSE);
	}
}


void CSetSoundDiagle::OnBnClickedButton2()
{
	CFileDialog file(true,NULL,NULL,OFN_ALLOWMULTISELECT,"wav(*.wav)|*.wav");
	file.m_ofn.lpstrTitle="选择消除时音效";
	if(file.DoModal() == IDOK)
	{
		s_musicName = file.GetFileName();
		s_musicPath = file.GetPathName();
		if(s_effectPath!="")
		{
			othermusic=1;
		}
		m_edit2 = s_musicName;
		UpdateData(FALSE);
	}
}
