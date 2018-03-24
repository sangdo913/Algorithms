#pragma once
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;



void PushOperator()
{
	long long nums[11];
	int operators[10];
	const int PLUS = 0;
	const int MINUS = 1;
	const int FLOP = 2;
	const int DIVIDE = 3;
	memset(nums, 0, sizeof(nums));

	int N;
	long long max = INT64_MIN;
	long long min = INT64_MAX;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> nums[i];
	}
	int cnt = 0;
	for (int i = 0; i < 4; i++)
	{
		int temp;
		cin >> temp;
		for (int j = 0; j < temp; j++)
			operators[cnt++] = i;
	}
	long long result = nums[0];
	do
	{
		for (int i = 0; i < N-1; i++)
		{
			switch (operators[i])
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
		min = min > result ? result : min;
		max = max < result ? result : max;
		result = nums[0];
	} while (next_permutation(operators, operators + N-1));
	cout << max << endl << min << endl;
}