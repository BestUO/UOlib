#pragma once
#include <iostream>

class AlgorithmExam
{
public:
	AlgorithmExam();
	~AlgorithmExam();
	///////��������:
	///////�Ӷ���������ÿһ���ڵ����ѡ��������������ߣ�
	///////һֱ�ߵ��ײ㣬Ҫ���ҳ�һ��·����ʹ��·���ϵ�����֮�����.
	void Numberoftower();
	///////����Ȧ�����˺���֮������ѹ�ϵ��
	//�����Щ���ѹ�ϵ���ж��ٸ�����Ȧ��a-b��b-c��d-e��e-f���������2������Ȧ��
	//����ʱ�临�Ӷ�
	///����10w��
	void COF();
	//�����������飬ʹÿ��ĺ;������
	void EQsum();
	//12���߰���ͬ���������ţ�ÿ�ű���Ӱ��������У��ڶ��űȶ�Ӧ�ĵ�һ�ŵ��˸ߣ��м������з�ʽ
	void paidui();
	//��������㷨,time[m]:��m̨��������һ�������ʱ�䣬����������ͬ
	void taskscheduling(const int &ntask,const int &nsvr,const int *time);

private:
	///////��������:
	int maxtwo(const uint32_t *data, int y, int x);
	
	int Catalan(int n);
};

