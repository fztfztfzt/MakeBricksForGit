#pragma once
#include "Mmsystem.h"
#include "defhead.h"
#pragma comment(lib,"winmm.lib")
class CSound
{
public:
	CSound(void);
	~CSound(void);
	void Init();//声音的初始化
	void OpenMusic(CString s_name);//打开文件
	void OpenEffect(CString s_name);//打开文件
	void PlaySound(int gamestate);//播放背景音乐
	void StopSound();//停止背景音乐
private:
static	CString musicPath;
static	CString effectPath;
};

