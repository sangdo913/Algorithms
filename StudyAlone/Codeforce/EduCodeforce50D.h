#pragma once
#include<iostream>

using namespace std;

int que[2][300000];
int f[2], r[2];

long long res[300000];
int rlen;

int EduCodeforce50D() {
	int n, m;
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	for (int i = 0; i < n; i++) {
		int in;
		cin >> in;
		que[0][r[0]++] = in;
	}
	cin >> m;
	for (int i = 0; i < m; i++) {
		int in;
		cin >> in;
		que[1][r[1]++] = in;
	}

	while (f[0] != r[0] && f[1] != r[1]) {
		long long num[2] = { que[0][f[0]++], que[1][f[1]++] };
		if (num[0] == num[1]) {
			rlen++;
			continue;
		}

		while (num[0] != num[1])
		{
			if (f[0] == r[0] && num[0] < num[1]) break;
			if (f[1] == r[1] && num[0] > num[1]) break;
			while (f[0] != r[0] && num[0] < num[1]) {
				num[0] += que[0][f[0]++];
			}
			while (f[1] != r[1] && num[0] > num[1]) {
				num[1] += que[1][f[1]++];
			}
		}
		if (num[0] != num[1]) {
			cout << -1 << '\n';
			return 0;
		}
		rlen++;
	}
	if (r[0] != f[0] || r[1] != f[1]) {
		cout << -1 << '\n';
		return 0;
	}
	cout << rlen << '\n';
	return 0;
}