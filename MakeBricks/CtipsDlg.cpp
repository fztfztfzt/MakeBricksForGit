// CtipsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MakeBricks.h"
#include "CtipsDlg.h"
#include "afxdialogex.h"


// CCtipsDlg 对话框

IMPLEMENT_DYNAMIC(CCtipsDlg, CDialogEx)

CCtipsDlg::CCtipsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCtipsDlg::IDD, pParent)
{

}

CCtipsDlg::~CCtipsDlg()
{
}

void CCtipsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCtipsDlg, CDialogEx)
END_MESSAGE_MAP()


// CCtipsDlg 消息处理程序
