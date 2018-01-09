#pragma once
#include<iostream>
#include<cmath>
#include<cstring>

using namespace std;

long long int SUPERVISOR_A[1000000];

void SuperVisor()
{
	long long int N, A, B,C;
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		cin >> SUPERVISOR_A[i];
	}

	cin >> B >> C;
	long long int result = N;
	for (int i = 0; i < N; i++) SUPERVISOR_A[i] -= B;
	for (int i = 0; i < N; i++)
	{
		if (SUPERVISOR_A[i] <= 0) continue;
		else {
			result += SUPERVISOR_A[i] / C;
			if (SUPERVISOR_A[i] % C != 0) result++;
		}

	}
	cout << result << endl;
}