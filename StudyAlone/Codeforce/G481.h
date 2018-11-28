//codeforces 481 G
//Petya's Exams

#pragma once
#include<iostream>
#include<queue>
#include<vector>

using namespace std;

struct INFO {
	int num;
	int d;
	int c;
};

bool operator<(const INFO& i1, const INFO& i2) {
	return i1.d > i2.d;
}

bool isend[101];

priority_queue<INFO> pq;
vector<INFO> exams[101];

int m, n;
int res[101];

int G481() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int s, d, c;
		cin >> s >> d >> c;
		exams[s].push_back({i + 1,d,c });
		res[d] = i + 1;
	}

	for (int i = 1; i <= n; i++) {
		for (int ii = 0; ii < exams[i].size(); ii++) {
			pq.push(exams[i][ii]);
		}
		if (res[i] != 0) {
			isend[res[i]] = true;
			res[i] = m + 1;
			continue;
		}

		if (pq.empty()) continue;

		INFO info = pq.top(); pq.pop();
		if (isend[info.num]) {
			pq.push({ 0,0,10000 });
			break;
		}
		info.c--;

		res[i] = info.num;
		if(info.c) pq.push(info);
	}

	if (pq.size()) { cout << -1 << '\n'; return 0; }

	for (int i = 1; i <= n; i++) cout << res[i] << ' ';
	cout << '\n';
	
	return 0;
}
