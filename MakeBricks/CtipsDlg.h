#pragma once


// CCtipsDlg �Ի���

class CCtipsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCtipsDlg)

public:
	CCtipsDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCtipsDlg();

// �Ի�������
	enum { IDD = IDD_INTRODUCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
