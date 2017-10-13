// UOalgorithm.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "AlgorithmExam.h"
#include<iostream>
#include<algorithm>
//using namespace std;

int main()
{

	AlgorithmExam aa;
	//aa.Numberoftower();
	//aa.COF();
	//aa.EQsum();
	//aa.paidui();
	
	//std::cout << "输入为m台服务器" << std::endl;
	//int nsvr;
	//std::cin >> nsvr;
	//std::cout << "输入每台机器处理一个任务的时间为t[i]" << std::endl;
	//int* time = new int[nsvr];
	//for (int i = 0; i < nsvr; i++)
	//	std::cin >> time[i];
	//std::cout << "输入任务数n" << std::endl;
	//int ntask;
	//std::cin >> ntask;
	//aa.taskscheduling(ntask, nsvr, time);
	//aa.maxnum();
	//aa.treeheight();
	//aa.reverseword();
	//aa.phone();
	//aa.flowernum();
	//aa.arraysum();
	//aa.CrossRiver();
		using namespace std;

		int n, a[10000], i;
		cin >> n;
		for (i = 0; i < n; i++)
		{
			cin >> a[i];
		}
		int count = 0;
		for (i = 0; i < n; i++)
		{
			if (a[i] >= n - i)
			{
				count++;
				n = i; i = -1;
			}
		}
		if (n != 0)
		{
			cout << -1;
		}
		else cout << count;
		return 0;

}

