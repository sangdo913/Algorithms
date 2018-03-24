#pragma once
#include<iostream>
#include<vector>

using namespace std;
bool AllTravel(vector<bool> check)
{
	int size = check.size();
	bool result = true;
	for (int i = 0; i < size; i++)
	{
		result &= check[i];
	}

	return result;
}

int SetNow(int size, int i)
{
	i = i > 0 ? i : 0;
	i = i < size ? i : size - 1;
	return i;
}

int DFS(const vector<int> &ai, vector<bool> check,int now)
{
	check[now] = true;
	if (AllTravel(check)) return 1;
	int ret = 0;
	int size = check.size();
	for (int i = SetNow(size, now - ai[now]); i <= SetNow(size,now+ai[now]); i++)
	{
		if (check[i] == false)
		{
			ret += DFS(ai, check, i);
		}
	}
	return ret;
}

void BC()
{
	vector<int> ai;
	vector<bool> check;
	int N;
	cin >> N;
	ai.resize(N);
	check.resize(N,false);
	for (int i = 0; i < N; i++)
	{
		cin >> ai[i];
	}
	int result = 0;
	for (int i = 0; i < N; i++)
	{
		result += DFS(ai, check, i);
	}

	cout << result << endl;

}