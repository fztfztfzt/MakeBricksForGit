#pragma once
#include "Mmsystem.h"
#include "defhead.h"
#pragma comment(lib,"winmm.lib")
class CSound
{
public:
	CSound(void);
	~CSound(void);
	void Init();//�����ĳ�ʼ��
	void OpenMusic(CString s_name);//���ļ�
	void OpenEffect(CString s_name);//���ļ�
	void PlaySound(int gamestate);//���ű�������
	void StopSound();//ֹͣ��������
private:
static	CString musicPath;
static	CString effectPath;
};

