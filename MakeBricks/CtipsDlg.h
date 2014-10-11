#pragma once


// CCtipsDlg 对话框

class CCtipsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCtipsDlg)

public:
	CCtipsDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCtipsDlg();

// 对话框数据
	enum { IDD = IDD_INTRODUCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
