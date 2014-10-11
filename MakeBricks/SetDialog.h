#pragma once

// CSetDialog 对话框

class CSetDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSetDialog)

public:
	CSetDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetDialog();

// 对话框数据
	enum { IDD = IDD_SETGAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	CString m_DialogRectNum;
	int m_DialogRectNum;
//	int m_DialogRectSep;
	CComboBox m_RectSpe;
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();//初始化对话框
	afx_msg void OnBnClickedOk();
	int m_rectSpecies;
	int m_DialogRectNumX;
	int m_DialogRectNumY;
	CMFCColorButton colorbut[12];
	afx_msg void OnSelchangeRectsepecies();
	afx_msg void OnEditchangeRectsepecies();
	void ShowColorBtu();//颜色按钮的显示与隐藏
	CMFCColorButton m_colorbtu[12];
	COLORREF colorArray[12];
	static COLORREF defColorArray[12];
	afx_msg void OnBnClickedDef();
	void GetColorBtu();//得到颜色按钮的颜色
	void SetColorBtu();//设置颜色按钮的颜色
};
