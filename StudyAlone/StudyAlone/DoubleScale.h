#pragma once
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>

// 준환이의 양팔저울 : https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWAe7XSKfUUDFAUw

using namespace std;

int SCALE_sinker[9];
int KNAP_memoi[9][1 << 18];

int GoDoubleScale(int left, int right, int count, int size,int visit,int index)
{
	int &result= KNAP_memoi[index][visit];

	//conditions to return
	if (result != -1) return result;		// 1. if there is memoi, then return
	if (right > left)						// 2. right is bigger than left
	{
		result = 0;
		return 0;
	}
	if (count == size)						// 3. seek all path
	{
		result = 1;
		return 1;
	}

	for (int i = 0; i < size; i++)
	{
		int next; // next check

		if (((visit >> (i + size)) & 1) || ((visit >> (i)) & 1)) continue;						//visit check ( left 9 bits are left, right 9 bits are right

		next = (visit |= (1 << (i + size)));													//visit	 left
		result += GoDoubleScale(left + SCALE_sinker[i], right, count + 1, size, next, i);
		visit &= ~(1 << (i + size));															//off visit

		next = (visit |= (1 << (i)));															// visit right
		result += GoDoubleScale(left, right + SCALE_sinker[i], count + 1, size, next, i);
		(visit &= ~(1 << (i)));																	// off visit
	}
	return ++result;																			// because initial result is zero.
}

void DoubleScale()
{
	int T, N;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N;

		memset(KNAP_memoi, -1, sizeof(KNAP_memoi));

		for (int i = 0; i < N; i++)
		{
			cin >> SCALE_sinker[i];
		}
		int result = GoDoubleScale(0,0,0,N,0,0);
		cout << '#' << tc << ' ' << result << endl;
	}
}