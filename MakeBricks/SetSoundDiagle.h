#pragma once


// CSetSoundDiagle 对话框

class CSetSoundDiagle : public CDialogEx
{
	DECLARE_DYNAMIC(CSetSoundDiagle)

public:
	CSetSoundDiagle(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetSoundDiagle();

// 对话框数据
	enum { IDD = IDD_SETSOUND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combo2;
	CComboBox m_combo3;
	virtual BOOL OnInitDialog();

	afx_msg void OnSelchangeCombo2();
	afx_msg void OnSelchangeCombo3();
	afx_msg void OnBnClickedOk();
	CString	s_musicBuf;//暂存
	CString s_effectBuf;
	afx_msg void OnBnClickedButton1();
	CString s_effectPath;//存放打开文件的名字和路径
	CString s_effectName;
	CString s_musicPath;
	CString s_musicName;
	int othereffect;//判断是否是用户打开的文件
	int othermusic;
	afx_msg void OnBnClickedButton2();
	CString m_edit1;
	CString m_edit2;
};
