#pragma once
#include<cstdio>
#include<algorithm>
#include<vector>

using namespace std;

typedef pair<int, int> PII;
int n;
int x[300001], y[300001];
vector<PII> vec;

int Codeforce506C() {

	scanf("%d\n", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d %d\n", &x[i], &y[i]);
		vec.push_back({ x[i], y[i] });
	}

	sort(x, x + n);
	sort(y, y + n);
	sort(vec.begin(), vec.end());

	int ans = 0;
	for (int i = 0; i < n; i++) {
		int xx = i == n - 1 ? x[n - 2] : x[n - 1];
		int yy = vec[i].second == y[0] ? y[1] : y[0];

		int d = yy - xx;
		ans = ans < d ? d : ans;
	}
	printf("%d\n", ans);
	return 0;
}
