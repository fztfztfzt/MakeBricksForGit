#pragma once

// CSetDialog �Ի���

class CSetDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSetDialog)

public:
	CSetDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetDialog();

// �Ի�������
	enum { IDD = IDD_SETGAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	CString m_DialogRectNum;
	int m_DialogRectNum;
//	int m_DialogRectSep;
	CComboBox m_RectSpe;
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();//��ʼ���Ի���
	afx_msg void OnBnClickedOk();
	int m_rectSpecies;
	int m_DialogRectNumX;
	int m_DialogRectNumY;
	CMFCColorButton colorbut[12];
	afx_msg void OnSelchangeRectsepecies();
	afx_msg void OnEditchangeRectsepecies();
	void ShowColorBtu();//��ɫ��ť����ʾ������
	CMFCColorButton m_colorbtu[12];
	COLORREF colorArray[12];
	static COLORREF defColorArray[12];
	afx_msg void OnBnClickedDef();
	void GetColorBtu();//�õ���ɫ��ť����ɫ
	void SetColorBtu();//������ɫ��ť����ɫ
};
