#pragma once
#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

struct COD
{
	long long x;
	long long y;
};

long long check[300][300];

int DFS(int n, int k)
{
	int ret = 0;

	if (k == n || k== 0)
	{
		return 1;
	}
	else
	{
		if (check[n-1][k] > 0)
		{
			ret += check[n-1][k];
		}
		else
		{
			check[n - 1][k] = DFS(n - 1, k);
			ret += check[n-1][k];
		}
		if (check[n - 1][k - 1] > 0) ret += check[n - 1][k - 1];
		else
		{
			check[n-1][k-1] =  DFS(n - 1, k - 1);
			ret += check[n - 1][k - 1];
		}
	}

	return ret;
}


void B1()
{
	memset(check, 0, sizeof(check));
	vector<COD> cods;
	int num_of_cods;
	long long share =  1000000007;
	cin >> num_of_cods;

	cods.resize(num_of_cods);
	for (int i = 0; i < num_of_cods; i++)
	{
		cin >> cods[i].x >> cods[i].y;
	}
	long long result = 0;
	for (int i = 3; i <= num_of_cods; i++)
	{
		result += (long long)DFS(num_of_cods, i);
	}

	cout << (result)% share << endl;
}