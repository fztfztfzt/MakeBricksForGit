#pragma once


// CSetSoundDiagle �Ի���

class CSetSoundDiagle : public CDialogEx
{
	DECLARE_DYNAMIC(CSetSoundDiagle)

public:
	CSetSoundDiagle(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetSoundDiagle();

// �Ի�������
	enum { IDD = IDD_SETSOUND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combo2;
	CComboBox m_combo3;
	virtual BOOL OnInitDialog();

	afx_msg void OnSelchangeCombo2();
	afx_msg void OnSelchangeCombo3();
	afx_msg void OnBnClickedOk();
	CString	s_musicBuf;//�ݴ�
	CString s_effectBuf;
	afx_msg void OnBnClickedButton1();
	CString s_effectPath;//��Ŵ��ļ������ֺ�·��
	CString s_effectName;
	CString s_musicPath;
	CString s_musicName;
	int othereffect;//�ж��Ƿ����û��򿪵��ļ�
	int othermusic;
	afx_msg void OnBnClickedButton2();
	CString m_edit1;
	CString m_edit2;
};
