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
	//设有n个正整数，将他们连接成一排，组成一个最大的多位整数。
	//如:n = 3时，3个整数13, 312, 343, 连成的最大整数为34331213。
	//如 : n = 4时, 4个整数7, 13, 4, 246连接成的最大整数为7424613。
	void maxnum();
	//输入的第一行表示节点的个数n（1 ≤ n ≤ 1000，节点的编号为0到n - 1）组成，
	//下面是n - 1行，每行有两个整数，第一个数表示父节点的编号，第二个数表示子节点的编号
	void treeheight();

private:
	///////数塔问题:
	int maxtwo(const uint32_t *data, int y, int x);
	
	int Catalan(int n);
};

