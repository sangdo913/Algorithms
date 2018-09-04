#pragma once
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

int Codeforce0902B() {
	vector<int> vec;

	int n, s;
	scanf("%d %d\n", &n, &s);
	for (int i = 0; i < n; i++)
	{
		int in;
		scanf("%d\n", &in);
		vec.push_back(in);
	}

	sort(vec.begin(), vec.end());

	long long res = 0;
	int i = vec.size() / 2;
	if ( vec[i] < s) 
	{
		while (i < vec.size() && vec[i] < s)
		{
			res += s - vec[i];
			i++;
		}
	}

	else {
		while (i >= 0 && vec[i] > s) {
			res += vec[i] - s;
			i--;
		}
	}
	printf("%lld\n", res);
	return 0;
}
