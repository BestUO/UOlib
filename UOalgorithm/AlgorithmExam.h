#pragma once
#include <iostream>

class AlgorithmExam
{
public:
	AlgorithmExam();
	~AlgorithmExam();
	///////数塔问题:
	///////从顶部出发在每一个节点可以选择向左或者向右走，
	///////一直走到底层，要求找出一条路径，使得路径上的数字之和最大.
	void Numberoftower();
	///////朋友圈数量人和人之间的朋友关系，
	//求出这些朋友关系中有多少个朋友圈（a-b、b-c、d-e、e-f，这里就有2个朋友圈）
	//给出时间复杂度
	///给出10w条
	void COF();
	//任意数分三组，使每组的和尽量相等
	void EQsum();
	//12个高矮不同的人排两排，每排必须从矮到高排列，第二排比对应的第一排的人高，有几种排列方式
	void paidui();
	//任务调度算法,time[m]:第m台机器处理一个任务的时间，所有任务都相同
	void taskscheduling(const int &ntask,const int &nsvr,const int *time);

private:
	///////数塔问题:
	int maxtwo(const uint32_t *data, int y, int x);
	
	int Catalan(int n);
};

