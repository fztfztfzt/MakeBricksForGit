#include "StdAfx.h"
#include "Sound.h"
CString CSound::effectPath=0;
CSound::CSound(void)
{
	
	Init();
	
}


CSound::~CSound(void)
{
}
void CSound::Init()
{
	effectPath = SOUND_EFFECTPATH;
	CString s;
	s.Format("open %s alias sound",effectPath);
	MCIERROR   mciError;
	mciError   =	mciSendString(s,NULL,0,NULL);
	effectPath = SOUND_MUSICPATH;
	s.Format("open %s alias music",effectPath);

	mciError   =	mciSendString(s,NULL,0,NULL);
	char buf[120];
	if(mciError)   
	{   
		mciGetErrorString(mciError,buf,128);   
		::AfxMessageBox("send MCI_PLAY command failed");    
		return;   
	}  
}
void CSound::PlaySound(int playstate)
{

	MCIERROR   mciError;
	if(playstate==STATE_MOUSEMOVE) mciError   =	mciSendString("play sound from 0",NULL,0,NULL);
	else if(playstate =STATE_BTUDOWN) mciError   =	mciSendString("play music from 0",NULL,0,NULL);
	char buf[120];
	if(mciError)   
	{   
		mciGetErrorString(mciError,buf,128);   
		::AfxMessageBox(buf);    
		return;   
	}   
}
void CSound::StopSound()
{
	mciSendString("close music",NULL,0,NULL);
	mciSendString("close sound",NULL,0,NULL);
}
void CSound::OpenMusic(CString s_name)
{
	CString s;
	s.Format("open %s alias music",s_name);
	mciSendString(s,NULL,0,NULL);

}
void CSound::OpenEffect(CString s_name)
{
	CString s;
	s.Format("open %s alias sound",s_name);
	mciSendString(s,NULL,0,NULL);

}