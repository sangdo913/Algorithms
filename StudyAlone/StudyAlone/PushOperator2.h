#pragma once
#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

int PUSH_ARR[4];
long long nums[11];
long long mins = INT64_MAX, maxs = INT64_MIN;
int path[1000];

const int PLUS = 0;
const int MINUS = 1;
const int FLOP = 2;
const int DIVIDE = 3;


void PermPlusS(int n, int depth, int PUSH_ARR[4])
{
	if (n == depth)
	{
		long long result = nums[0];
		for (int i = 0; i < n; i++)
		{
			switch (path[i])
			{
			case PLUS:
				result += nums[i + 1];
				break;
			case MINUS:
				result -= nums[i + 1];
				break;
			case FLOP:
				result *= nums[i + 1];
				break;
			case DIVIDE:
				result /= nums[i + 1];
				break;
			}

		}

		mins = mins> result ? result : mins;
		maxs = maxs < result ? result : maxs;
		return;
	}

	for (int i = 0; i < 4; i++)
	{

		if (PUSH_ARR[i] == 0) continue;
		PUSH_ARR[i]--;
		int temp[4];
		path[depth] = i;
		PermPlusS(n, depth + 1, (int*)memcpy(temp, PUSH_ARR, sizeof(temp)));
		PUSH_ARR[i]++;
	}
}

void PushOperator2()
{
	int N;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> nums[i];
	}

	for (int i = 0; i < 4; i++)
	{
		cin >> PUSH_ARR[i];
	}

	PermPlusS(N - 1, 0, PUSH_ARR);
	cout << maxs << '\n' << mins << '\n';
}