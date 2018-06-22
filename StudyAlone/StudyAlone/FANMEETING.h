#pragma once
#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>

using namespace std;

char groups[200001];
char fans[200001];

int len[2];

typedef vector<int> VEC;

vector<int> g, f;

int min(int i1, int i2)
{
	return i1 < i2 ? i1 : i2;
}

int max(int i1, int i2)
{
	return i1 > i2 ? i1 : i2;
}

VEC multi(VEC& A, VEC& B)
{
	int s1 = A.size();
	int s2 = B.size();

	VEC res;  
	res.resize(s1 + s2 - 1, 0);

	for (int i = 0; i < s1; i++)
	{
		for (int j = 0; j < s2; j++)
		{
			res[i + j] += A[i] * B[j];
		}
	}
	return res;
}

void add(vector<int>& vec1, vector<int>& vec2, int k)
{	
	int s = max(vec2.size() + k, vec1.size());

	vec1.resize(s, 0);
	vec2.resize(s, 0);

	for (int i = 0; i < s - k; i++)
	{
		vec1[i + k] += vec2[i];
	}
	
}

void sub(vector<int>& vec1, vector<int>& vec2)
{
	int s = max(vec1.size(),vec2.size());

	vec1.resize(s, 0);
	vec2.resize(s, 0);

	for (int i = 0; i < s; i++) vec1[i] -= vec2[i];
}

VEC Karatsuba(VEC& A, VEC& B)
{
	if (A.size() < 50)
	{
		VEC res;
		res = multi(A,B);
		return res;
	}

	int half = A.size() / 2;
	
	if (A.empty() || B.empty()) return VEC();

	VEC a1 = VEC(A.begin(), A.begin() + half);
	VEC a0 = VEC(A.begin() + half, A.end());
	VEC b1 = VEC(B.begin(), B.begin() + min(half, B.size()));
	VEC b0 = VEC(B.begin() + min(half, B.size()), B.end());

	VEC z0, z1, z2;
	
	z0 = Karatsuba(a0, b0);
	z2 = Karatsuba(a1, b1);
	
	add(a0, a1, 0);
	add(b0, b1, 0);

	z1 = Karatsuba(a0, b0);
	sub(z1, z0);
	sub(z1, z2);

	VEC res;
	add(res, z2, 0);
	add(res, z1, half);
	add(res, z0, half + half);

	return res;
}

int FANMEETING()
{
	int t;
	scanf("%d\n", &t);

	while (t--)
	{
		scanf("%s\n", groups);
		scanf("%s\n", fans);

		len[0] = strlen(groups);
		len[1] = strlen(fans);

		f.resize(len[1], 0);
		g.resize(len[0], 0);
		for (int i = 0; i < len[0]; i++) g[i] = groups[len[0] - i - 1] == 'M';
		for (int i = 0; i < len[1]; i++) f[i] = fans[i] == 'M';

		VEC res = Karatsuba(f, g);

		int cnt = 0;
		for (int i = len[0] - 1; i < len[1]; i++)
		{
			cnt += res[i] == 0;
		}
		printf("%d\n", cnt);
	}

	return 0;
}