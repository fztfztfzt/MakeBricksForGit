#pragma once
class ClassRect_fzt
{
public:
	ClassRect_fzt();
	~ClassRect_fzt(void);
	void SetColor(COLORREF c);//���þ�����ɫ
	void SetPoint(int x,int y);//���þ���λ��
	bool IsAlive();//�жϾ����Ƿ����
	void SetAlive(bool b);//���þ��δ������
	bool IsColor(COLORREF c);//�ж���ɫ
	COLORREF GetColor();//�õ�����������ɫ
	bool IsSameColor(COLORREF c);//�Ƿ���ѡ����ɫ��ͬ
	void SetSameColor(bool b);//������ѡ�����ͬʱ��Ϊtrue
	bool IsChoose();//�Ƿ�ѡ��
	void EraseRect();//��ȥ�þ���
	int x;//��������
	int y;
	int oldx;//��������ʱ������Ŀ���Ǳ��涯��֮ǰ��������
	int oldy;
private:
	bool alive;//���δ��״̬
	COLORREF color;//������ɫ
	bool SameColor;//�жϸþ��ο��Ƿ���ѡ�еľ�����ɫ��ͬ
	
};

