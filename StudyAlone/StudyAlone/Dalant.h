#pragma once
#include<iostream>

using namespace std;
inline long long Dalant_MAX(long long x1, long long x2)
{
	return x1 > x2 ? x1 : x2;
}
long long memoi[101][101];
long long MaxDalant(long long remain, long long length)
{
	long long &result = memoi[remain][length];
	if (remain == 0) return 1;
	else if (length == 1)return (remain+1);
	else if (result > 0) return result;
	length--;
	for (int i = 0; i <= (remain+1)/2; i++)
	{
		result = Dalant_MAX(result, (i+1)*MaxDalant(remain - i, length));
	}

	return result;
}

void Dalant()
{
	int T,N,M;
	long long result;
	cin >> T;
	for (int i = 0; i < 101; i++)
		for (int j = 0; j < 101; j++)
			memoi[i][j] = 0;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N >> M;
		result = MaxDalant(N - M,M);
		cout << '#' << tc << ' ' << result << endl;
	}
}