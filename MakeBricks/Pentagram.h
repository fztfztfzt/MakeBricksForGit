/*����Ч��   ����ǵ������Լ�����
�������������ʽ�洢��next����ָ����һ���ڵ�

*/
#pragma once
class CPentagram
{
public:
	CPentagram(void);
	~CPentagram(void);
	CPoint pts[10];//����ǵ�10������
	CPoint oldPts[10];
	CPoint center_point;//���ĵ�
	
	void Init();
	void SetCenterPoint(int,int);//�������ĵ�
	void SetCenterPoint(CPoint p);
	void SetSpeed(int,int);
	void Run();
	void SetColor(COLORREF);
	COLORREF GetColor();
	CPentagram *next;//ָ������ָ����һ�������
private:
	int radius;//����ǰ뾶
	int vx;//x����ٶ�
	int vy;//y����ٶ�
	int a;//y����ٶ�
	int t;//����ʱ��
	COLORREF color;//�������ɫ
};

