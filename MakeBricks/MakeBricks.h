
// MakeBricks.h : MakeBricks Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMakeBricksApp:
// �йش����ʵ�֣������ MakeBricks.cpp
//

class CMakeBricksApp : public CWinApp
{
public:
	CMakeBricksApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMakeBricksApp theApp;
