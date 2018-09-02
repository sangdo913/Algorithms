#pragma once
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

int Aabs(int i) {
	return i > 0 ? i : -i;
}
int min(int i1, int i2) {
	return i1 < i2 ? i1 : i2;
}

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
	if (n == 1) {
		printf("%d\n", Aabs(s - vec[0]));
		return 0;
	}
	auto it = lower_bound(vec.begin(), vec.end(), s);
	int r = it - vec.begin();
	if (r == vec.size() / 2) {
		printf("%d\n", Aabs(vec[r] - s));
	}
	else if (r < vec.size() / 2) {
		long long res = 0;
		for (; r <= vec.size() / 2; r++) {
			res += vec[r] - s;
		}
		printf("%lld\n", res);

	}
	else {
		long long res = 0;
		if (r == vec.size()) r--;
		for (; r >= vec.size() / 2; r--) {
			res += s - vec[r];
		}
		printf("%lld\n", res);
	}

	return 0;
}
