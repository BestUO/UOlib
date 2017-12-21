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

void AlgorithmExam::reverseword()
{
	std::string str;
	std::getline(std::cin, str);
	std::vector<std::string> v;
	size_t lastpos = 0;
	while (true)
	{
		size_t pos = str.find(' ', lastpos);
		v.push_back(str.substr(lastpos,pos - lastpos));
		if (pos == str.npos)
			break;
		lastpos = pos + 1;
	}
	for (size_t i = v.size(); i > 1; i--)
		std::cout << v[i - 1] << ' ';
	std::cout << v[0];
}

void AlgorithmExam::phone()
{
	std::vector<std::string> v;

	std::string snum;
	std::getline(std::cin, snum);
	for (int i = 0; i < std::stoi(snum); i++)
	{
		std::string str;
		std::getline(std::cin, str);
		v.push_back(str);
	//}
	//for (int i = 0; i < std::stoi(snum); i++)
	//{
		char l[26] = { 0 };
		char n[10] = { 0 };
		for (uint32_t j = 0; j < v[i].size(); j++)
			l[v[i][j] - 'A']++;

		n[0] = l['Z' - 'A'];
		n[2] = l['W' - 'A'];
		n[4] = l['U' - 'A'];
		n[6] = l['X' - 'A'];
		n[8] = l['G' - 'A'];

		n[1] = l['O' - 'A'] - n[0] - n[2] - n[4];
		n[3] = l['R' - 'A'] - n[0] - n[4];
		n[5] = l['F' - 'A'] - n[4];
		n[7] = l['S' - 'A'] - n[6];
		n[9] = (l['N' - 'A'] - n[1] - n[7])/2;

		std::vector<int> m;
		for (int j = 0; j < 10; j++)
		{
			for (int k = 0; k < n[j]; k++)
				m.push_back((j + 2) % 10);
		}
		std::sort(m.begin(), m.end());
		for (auto t : m)
			std::cout << t;
		std::cout << std::endl;
	}
}

bool sum(const int& n)
{
	int bai = n / 100;
	int shi = (n / 10) % 10;
	int ge = n % 10;
	if (n == (pow(bai, 3) + pow(shi, 3) + pow(ge, 3)))
		return true;
	else return false;
}

void AlgorithmExam::flowernum()
{
	int min = 0;
	int max = 0;
	while (std::cin >> min >> max)
	{
		if (min > max)
			break;
		std::vector<int> v;
		for (int i = min; i <= max; i++)
		{
			if (sum(i))
				v.push_back(i);
		}
		if (v.size() != 0)
		{
			for (uint32_t j = 0; j < v.size() - 1; j++)
				std::cout << v[j] << ' ';
			std::cout << v[v.size() - 1];
		}
		else
			std::cout << "no" << std::endl;
	}
}
#include<iomanip>
void AlgorithmExam::arraysum()
{
	float fir = 0;
	int num = 0;
	while (std::cin >> fir >> num)
	{
		float sum = fir;
		for (int i = 1; i < num; i++)
		{
			fir = sqrtf(fir);
			sum += fir;
		}
		std::cout << std::fixed << std::setprecision(2) << sum << std::endl;
	}
}

void AlgorithmExam::CrossRiver()
{
	int len = 0;
	std::cin >> len;
	int t[10001] = { 0 };
	for (int i = 0; i < len; i++)
		std::cin >> t[i];

	int sum = t[0];
	int num = 1;
	int ID = 0;
	bool fail = false;
	while (sum < len)
	{
		int maxsum = 0;
		int maxID = 0;
		for (int i = 0; i < t[ID]; i++)
		{
			if (maxsum <= ID + (i + 1) + t[ID + i + 1])
			{
				maxsum = ID + (i + 1) + t[ID + i + 1];
				maxID = ID + (i + 1);
			}
		}
		ID = maxID;
		if (!t[ID])
		{
			fail = true;
			break;
		}
		sum = ID + t[ID];
		num++;
	}
	if (fail)
		std::cout << "-1" << std::endl;
	else
		std::cout << num << std::endl;
}

int finds1(const char* a,int arraylen,std::string s,int findlen)
{
	for (int j = 0; j < arraylen; j++)
	{
		const char*b = a + j;
		bool tmp;
		for (size_t i = 0; i < s.size(); i++)
		{
			tmp = false;
			for (int k = 0; k < findlen; k++)
			{
				if (s[i] == b[k])
				{
					tmp = true;
					break;
				}
			}
			if (!tmp)
				break;
		}
		if (tmp)
			return j;
	}
	return 0;
}

void AlgorithmExam::gemstone()
{
	std::string str;
	std::string s = "ABCED";
	while (std::cin >> str)
	{
		int len = str.size() + str.size() - 1;
		char* tmp = new char[len];
		memcpy(tmp, str.data(), str.size());
		memcpy(tmp + str.size(), tmp, str.size() - 1);
		
		int n = 0;
		for (size_t i = s.size();i <= str.size();i++)
		{
			n = finds1(tmp, len, s, i);
			if (n)
			{
				n = i;
				break;
			}
		}

		delete tmp;
		tmp = nullptr;
		if (n)
			std::cout << str.size() - n << std::endl;
		else
			std::cout << 0 << std::endl;
	}
}

void AlgorithmExam::maxnum2()
{
	std::string str;
	int cnt = 0;
	while (std::cin >> str >> cnt)
	{
		std::string out;
		while (cnt)
		{
			int ind = 0;
			for (size_t i = 0; i < str.size() - 1; i++)
			{
				if (str[i] < str[i + 1])
				{
					str.erase(str.begin() + i);
					cnt--;
					break;
				}
				else if (i + 1 == str.size() - 1)
				{
					str.erase(str.begin() + i + 1);
					cnt--;
				}
			}
		}
		std::cout << str << std::endl;
	}
}

void AlgorithmExam::firstthree()
{
	std::string s;
	while (std::getline(std::cin, s))
	{
		int a[26] = { 0 };
		int b[26] = { 0 };
		for (size_t i = 0; i < s.size(); i++)
		{
			if (s[i] >= 'a' && s[i] <= 'z')
			{
				a[s[i] - 'a']++;
				if (a[s[i] - 'a'] == 3)
				{
					std::cout << s[i] << std::endl;
					break;
				}
			}
			else if(s[i] >= 'A' && s[i] <= 'Z')
			{
				b[s[i] - 'A']++;
				if (b[s[i] - 'A'] == 3)
				{
					std::cout << s[i] << std::endl;
					break;
				}
			}
		}
	}
}

void AlgorithmExam::IDdivide()
{
	std::string str;
	while (std::getline(std::cin,str))
	{
		int len = str.size();
		int pos = 0;
		for (int i = 0; i < len; i++)
		{
			if (str[i] == ' ')
				continue;
			else
			{
				std::cout << str[i];
				++pos;
				if (pos == 6 || pos == 14)
					std::cout << ' ';
			}

		}
		std::cout << std::endl;
	}
}

void AlgorithmExam::hotelprice()
{
	int prices[10000] = { 0 };
	int first, last, price;
	std::cin >> first >> last >> price;

	int min = first;
	int max = last;
	for (int i = first; i <= last; i++)
		prices[i] = price;
	while (std::cin >> first >> last >> price)
	{
		min = min < first?min:first;
		max = max > last?max:last;
		for (int i = first; i <= last; i++)
			prices[i] = price;
	}
	bool newone = true;
	for (int i = min; i < max+1; i++)
	{
		if (!prices[i])
			continue;
		if (newone)
		{
			newone = false;
			std::cout << '[' << i << ',';
			if (prices[i] != prices[i + 1])
			{
				newone = true;
				std::cout << i << ',' << prices[i] << ']';
				if (i != max)
					std::cout << ',';
			}
		}
		else
		{
			if (prices[i] != prices[i+1])
			{
				newone = true;
				std::cout << i << ',' << prices[i] << ']';
				if (i != max)
					std::cout << ',';
			}
		}
	}
}

void AlgorithmExam::fileextension()
{
	std::string str;
	while (std::getline(std::cin,str))
	{
		int pos = str.find('.');
		if (pos != -1)
			std::cout << str.substr(pos + 1);
		else
			std::cout << "null";
	}
}

void AlgorithmExam::intplus()
{
	std::string str;
	while (std::getline(std::cin, str))
	{
		bool iserror = false;
		for (size_t i = 0; i < str.size(); i++)
		{
			if (str[i] != ' ')
			{
				if (!isdigit(str[i]))
				{
					std::cout << "error" << std::endl;
					iserror = true;
					break;
				}
			}
		}
		if (!iserror)
		{
			int pos = str.find(' ');
			int first = std::stoi(str.substr(0, pos));
			int second = std::stoi(str.substr(pos + 1));
			std::cout << first + second << std::endl;
		}
	}
}