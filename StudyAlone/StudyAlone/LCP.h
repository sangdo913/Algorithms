#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

int AtoI(char a)
{
	if (a >= 'a' && a <= 'z') return a - 'a';
	else if (a >= 'A' && a <= 'Z') return a - 'A' + 'z'-'a' +1;

	return -1;
}

struct Cmp
{
	vector<int> *g;
	int *t;
	bool operator ()(int x1, int x2);
	Cmp(vector<int> *g, int *t):g(g), t(t) 
	{
	};
};

//when result is false, swap happens.
bool Cmp::operator() (int x1, int x2)
{
	if ((*g)[x1] == (*g)[x2])
	{
		return ((*g)[x1 + *t] ) < (*g)[x2 + *t];
	}

	return (*g)[x1] < (*g)[x2];
}



void LCP()
{
	vector<int> g, tg, SA, rank,lcp;
	string str;

	int c_num,t = 1;
	cin >> c_num;
	g.resize(600000, -1);
	tg.resize(c_num, 0);
	SA.resize(c_num + c_num, -1);
	rank.resize(c_num, 0);
	lcp.resize(c_num, 0);

	
	cin >> str;
	
	for (int i = 0; i < c_num+c_num; i++)
	{
		str += "@";
	}

	int size = c_num;
	for (int i = 0; i < size; i++)
	{
		g[i] = AtoI(str[i]);
		SA[i] = i;
	}


	Cmp cmp(&g,&t);

	while (t <= size)
	{
		sort(SA.begin(), SA.begin()+size, cmp);

		tg[SA[0]] = 0;
		for (int i = 1; i < size; i++)
		{
			if (cmp(SA[i-1], SA[i]))
			{
				tg[SA[i]] = tg[SA[i - 1]]+1;
			}

			else tg[SA[i]] = tg[SA[i - 1]];
		}

		for (int i = 0; i < size; i++)
		{
			g[i] = tg[i];
		}

		t <<= 1;
	}

	for (int i = 0; i < size; i++)
	{
		rank[SA[i]] = i;
	}

	////print
	//for (int i = 0; i < size; i++)
	//{
	//	cout << &str[SA[i]] << endl;
	//}
	//cout << endl;

	int len = 0;
	int k;

	for (int i = 0; i < size; i++)
	{
		k = rank[i];
		if (k > 0)
		{
			while (str[i + len] == str[SA[k-1]+len] && str[i+len] != '@') len++;
			lcp[rank[i]] = len;
			//cout << len << endl;
			if (len > 0)len--;
		}
	}
/*
	for (int i = 0; i < size; i++)
	{
		cout << lcp[i] << " ";
	}
	cout << endl;
	*/

	//cout << endl;
	int max = 0;
	for (int i = 0; i < size; i++)
		max = max > lcp[i] ? max : lcp[i];

	cout << max << endl;
}