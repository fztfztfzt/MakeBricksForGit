
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "MakeBricks.h"

#include "MainFrm.h"

#include "defhead.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 创建一个视图以占用框架的工作区
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("未能创建视图窗口\n");
		return -1;
	}
	SendMessage(WM_SETICON, (WPARAM)FALSE, (LPARAM)LoadIcon(GetModuleHandle(NULL), (LPCTSTR)IDR_MAINFRAME));
//	SetClassLong(m_hWnd,GCL_HBRBACKGROUND,(long)GetStockObject(NULL_BRUSH));
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	
	int x,y;
	OFSTRUCT ofn;
	if(OpenFile("save_exit.fzt",&ofn,OF_EXIST) != HFILE_ERROR) 
	{
		CFile file("save_exit.fzt", CFile::modeRead | CFile::typeBinary );

		file.Read(&x,sizeof(int));
		file.Read(&y,sizeof(int));
		file.Close();
	}else
	{
		x=FZT_NUMX;
		y=FZT_NUMY;
	}
	
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	cs.cx = RECT_WIDTH*x+DEFAULT_FRAME_X;//设置窗口宽度
	cs.cy = y*RECT_HEIGHT+DEFAULT_FRAME_Y+FZT_GAP*RECT_HEIGHT;//设置窗口高度
	cs.style &= ~WS_THICKFRAME ;//去除可改变大小的边框
	cs.style&=~WS_MAXIMIZEBOX;
	
	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// 将焦点前移到视图窗口
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// 让视图第一次尝试该命令
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// 否则，执行默认处理
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


BOOL CMainFrame::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
	//return CFrameWnd::OnEraseBkgnd(pDC);
}
