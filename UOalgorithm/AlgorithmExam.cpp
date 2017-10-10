#include "AlgorithmExam.h"
#include <vector>
#include <algorithm>
#include <set>
#include <string>
#include <memory>

AlgorithmExam::AlgorithmExam()
{
}


AlgorithmExam::~AlgorithmExam()
{
}

int AlgorithmExam::maxtwo(const uint32_t *data,int y, int x)
{
	if (y < 0)
		return 0;
	else if (x == -1)
		return data[y * 5 + x + 1];
	else
		return data[y * 5 + x] > data[y * 5 + x + 1] ? data[y * 5 + x] : data[y * 5 + x + 1];
}

void AlgorithmExam::Numberoftower()
{
	uint32_t data[5][5] = { 9,0,0,0,0,
							12,15,0,0,0,
							10,6,8,0,0,
							2,18,9,5,0,
							19,7,10,4,16};
	uint32_t data2[5][5] = {0};
	
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x <= y; x++)
			data2[y][x] = maxtwo(data2[0],y-1,x-1) + data[y][x];
	}
	uint32_t max = 0;
	for (int x = 0; x < 5; x++)
		max = max > data2[4][x] ? max : data2[4][x];

}

void AlgorithmExam::COF()
{
	std::vector<std::pair<std::string, std::string> > p;
	p.push_back(std::make_pair("a", "b"));
	p.push_back(std::make_pair("b", "c"));
	p.push_back(std::make_pair("d", "e"));
	p.push_back(std::make_pair("e", "f"));
	p.push_back(std::make_pair("g", "h"));

	bool find = false;
	
	std::vector<std::set<std::string> > root;
	for (uint32_t n = 0;n < p.size();n++)
	{
		find = false;
		for (size_t i = 0; i < root.size(); i++)
		{
			if (root[i].find(p[n].first) != root[i].end() || root[i].find(p[n].second) != root[i].end())
			{
				root[i].insert(p[n].first);
				root[i].insert(p[n].second);
				find = true;
				break;
			}
		}
		if (!find)
		{
			std::set<std::string> Cir;
			Cir.insert(p[n].first);
			Cir.insert(p[n].second);
			root.push_back(Cir);
		}
	}
	std::cout << "朋友圈个数：" << root.size() << std::endl;
}

void AlgorithmExam::EQsum()
{
	std::vector<int> vec;
	int tmp;
	std::cout << "输入 任意非数字 结束" << std::endl;
	while (std::cin >> tmp)
		vec.push_back(tmp);
	std::sort(vec.rbegin(), vec.rend());
	
	std::vector<int> vec1(1,0);
	std::vector<int> vec2(1,0);
	std::vector<int> vec3(1,0);

	for (size_t i = 0; i < vec.size(); i++)
	{
		tmp = 0;
		if (vec1[0] < vec2[0])
		{
			if (vec1[0] < vec3[0])
				tmp = 1;
			else
				tmp = 3;
		}
		else
		{
			if (vec2[0] < vec3[0])
				tmp = 2;
			else
				tmp = 3;
		}

		switch (tmp)
		{
		case 1:
			vec1[0] += vec[i];
			vec1.push_back(vec[i]);
			break;
		case 2:
			vec2[0] += vec[i];
			vec2.push_back(vec[i]);
			break;
		case 3:
			vec3[0] += vec[i];
			vec3.push_back(vec[i]);
			break;
		default:
			break;
		}
	}

	std::cout << vec1[0] << '\t';
	for (size_t i = 1; i < vec1.size(); i++)
		std::cout << vec1[i] << " ";
	std::cout << std::endl;

	std::cout << vec2[0] << '\t';
	for (size_t i = 1; i < vec2.size(); i++)
		std::cout << vec2[i] << " ";
	std::cout << std::endl;

	std::cout << vec3[0] << '\t';
	for (size_t i = 1; i < vec3.size(); i++)
		std::cout << vec3[i] << " ";
	std::cout << std::endl;
}

void AlgorithmExam::paidui()
{
	std::cout << Catalan(6);
}

int AlgorithmExam::Catalan(int n)
{
	//if (Catalan(0) = 1 && Catalan(1) == 1)
	//	Catalan(n) = c(2n,n)/(n+1)
	//另类递推式：
	//	h(n) = h(n - 1)*(4 * n - 2) / (n + 1)
	if (n == 0)
		return 1;
	if (n == 1)
		return 1;
	else
	{
		int tmp = 0;
		for (int i = 0; i < n; i++)
			tmp += Catalan(i) * Catalan(n-i-1);
		return tmp;
	}
}

void AlgorithmExam::taskscheduling(const int &ntask, const int &nsvr, const int *time)
{
	int *now = new int[nsvr];
	memset(now, 0,sizeof(int) * nsvr);
	int *next = new int[nsvr];
	memset(next, 0, sizeof(int) * nsvr);
	
	for (int i = 0; i < ntask; i++)
	{
		int svrnum = 0;
		int min = now[0] + time[0];
		for (int j = 0; j < nsvr; j++)
		{
			memcpy(next, now, sizeof(int) * nsvr);
			next[j] += time[j];
			if (min > next[j])
			{
				svrnum = j;
				min = next[j];
			}
		}
		now[svrnum] += time[svrnum];
	}
	for (int i = 0; i < nsvr; i++)
		std::cout << now[i] << '\t';
	std::cout << std::endl;
}

bool cmp(const std::string &a, const std::string &b)
{
	return (a + b) > (b + a);
}

void AlgorithmExam::maxnum()
{
	int a = 0;
	std::cin >> a;

	std::vector<std::string> v;
	for (int i = 0; i < a; i++)
	{
		std::string s;
		std::cin >> s;
		v.push_back(s);
	}
	std::sort(v.begin(), v.end(), cmp);
	for (int i = 0; i < a; i++)
		std::cout << v[i];
}

struct NODE
{
	NODE *LC;
	NODE *RC;
	int ID;
	NODE()
	{
		ID = 0;
		LC = nullptr;
		RC = nullptr;
	}
	//~NODE()
	//{
	//	if (LC)
	//		delete LC;
	//	if (RC)
	//		delete RC;
	//}
};

int high(NODE* p)
{
	if (!p)
		return 0;
	else
	{
		int lh = high(p->LC);
		int rh = high(p->RC);
		return 1 + (lh > rh ? lh : rh);
	}
}

void AlgorithmExam::treeheight()
{
	int num = 0;
	std::cin >> num;
	NODE *p = new NODE[num];
	
	for (int i = 1; i < num; i++)
	{
		int a = 0;
		int b = 0;
		std::cin >> a >> b;
		p[b].ID = b;
		if (p[a].LC == nullptr)
			p[a].LC = &p[b];
		else if(p[a].RC == nullptr)
			p[a].RC = &p[b];
	}

	std::cout << high(p);
	delete p;
}