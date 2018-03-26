#pragma once
#include<iostream>
#include<vector>
#include<map>

using namespace std;

struct Counsler_Vector
{
	long long x;
	long long y;

	long long getLength()
	{
		return x*x + y*y;
	}
};

long long max_value;

void GetMinVector(vector<Counsler_Vector> list, bool flag[300],int n, int r)
{
	if (r == 0)
	{
		Counsler_Vector res = { 0,0 };
		for (int i = 0; i < list.size(); i++)
		{
			res.x = flag[i] ? res.x + list[i].x : res.x - list[i].x;
			res.y = flag[i] ? res.y + list[i].y : res.y - list[i].y;
		}

		if (res.getLength() < max_value) max_value = res.getLength();
		return;
	}

	if (n == r)
	{
		Counsler_Vector res = { 0,0 };
		for (int i = 0; i < n; i++) {
			res.x = res.x + list[i].x;
			res.y = res.y + list[i].y;
		}

		for (int i = n; i < list.size(); i++)
		{
			res.x = flag[i] ? res.x + list[i].x : res.x - list[i].x;
			res.y = flag[i] ? res.y + list[i].y : res.y - list[i].y;
		}
		if (res.getLength() < max_value) max_value = res.getLength();
		return;
	}

	flag[n - 1] = true;
	GetMinVector(list, flag, n - 1, r - 1);
	flag[n - 1] = false;
	GetMinVector(list, flag, n-1, r);
}

void Counsler()
{
	//Counsler_Vector vecs[20];
	vector<Counsler_Vector> vecs;
	int K, N;
	cin >> K;
	for (int t = 1; t <= K; t++)
	{
		long long result = 0;
		cin >> N;

		vecs = vector<Counsler_Vector>(N);
		max_value = INT64_MAX;
		for (int i = 0; i < N; i++)
		{
			cin >> vecs[i].x >> vecs[i].y;
		}

		bool flag[300];
		memset(flag, false, sizeof(flag));
		GetMinVector(vecs,flag,N,N/2);
		cout << "#" << t << " " <<max_value << endl;
	}
}