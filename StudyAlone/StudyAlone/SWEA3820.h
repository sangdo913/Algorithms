//swea3820
//롤러코스터
#pragma once
#include<iostream>
#include<algorithm>

using namespace std;

int arr[200000][2];
int parr[200000], MOD = 1000000007;

struct cmp {
	bool operator()(int i1, int i2) {
		return 1LL * (arr[i1][0] + arr[i1][1])*arr[i2][0] + arr[i2][1] < 1LL*(arr[i2][0] + arr[i2][1])*arr[i1][0] + arr[i1][1] ;
	}
};

int SWEA3820() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int  t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		int n;
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> arr[i][0] >> arr[i][1];
			parr[i] = i;
		}

		sort(parr, parr + n, cmp());

		long long v = 1;

		for (int i = 0; i < n; i++) {
			int idx = parr[i];
			v =( arr[idx][0] * v + arr[idx][1])%MOD;
 		}

		cout << '#' << tc << ' ' <<  v << endl;
	}
	
	return 0;
}
