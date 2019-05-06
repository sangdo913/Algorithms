#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
#include<cstring>
#include<map>

using namespace std;

int arr[100][100];
int n,m,k;
vector<int> vec[100];

void R() {
	map<int, int> mp;
	int mc = 0;

	for (int i = 0; i < n; ++i) {
		priority_queue<pair<int, int> > pq;
		mp.clear();
		for (int j = 0; j < m; ++j) {
			mp[arr[i][j]]++;
		}
		for (auto i : mp) {
			if (i.first) {
				pq.push({ -i.second, i.first });
			}
		}

		int prev = 1;
		priority_queue<pair<int, int> > pq2;
		int idx = 0;
		pq.push({-1000000, 0 });
		vec[i].clear();

		while (pq.size()) {
			auto ii = pq.top();
			if (ii.first != prev) {
				while (pq2.size()) {
					pair<int, int> j = pq2.top(); pq2.pop();
					vec[i].push_back(-j.first);
					vec[i].push_back(j.second);
				}
				prev = ii.first;
				continue;
			}
			pq2.push({ -ii.second, -ii.first });
			pq.pop();
		}

		mc = vec[i].size() > mc ? vec[i].size() : mc;
	}

	mc = mc < 100 ? mc : 100;
	for (int i = 0; i < n; ++i) {
		vec[i].resize(mc);
		for (int j = 0; j < mc; ++j) {
			arr[i][j] = vec[i][j];
		}
	}
	m = mc;
}

void C() {
	map<int, int> mp;
	int mr = 0;

	for (int j = 0; j < m; ++j) {
		priority_queue<pair<int, int> > pq;
		mp.clear();
		for (int i = 0; i < n; ++i) {
			mp[arr[i][j]]++;
		}
		for (auto i : mp) {
			if (i.first) {
				pq.push({ -i.second, i.first });
			}
		}

		int prev = 1;
		priority_queue<pair<int, int> > pq2;
		int idx = 0;
		pq.push({-1000000, 0 });
		vec[j].clear();

		while (pq.size()) {
			auto ii = pq.top();
			if (ii.first != prev) {
				while (pq2.size()) {
					pair<int, int> jj = pq2.top(); pq2.pop();
					vec[j].push_back(-jj.first);
					vec[j].push_back(jj.second);
				}
				prev = ii.first;
				continue;
			}
			pq2.push({ -ii.second, -ii.first });
			pq.pop();
		}

		mr = mr < vec[j].size() ? vec[j].size() : mr;
	}

	mr = mr > 100 ? 100 : mr;
	for (int j = 0; j < m; ++j) {
		vec[j].resize(mr);
		for (int i = 0; i < mr; ++i) {
			arr[i][j] = vec[j][i];
		}
	}
	n = mr;
}

int ain() {
	int r, c;
	cin >> r >> c >> k;
	n = m = 3;
	--r, --c;

	for (int i = 0; i < 3; ++i)for (int j = 0; j < 3; ++j) {
		cin >> arr[i][j];
	}

	int cnt = 0;
	while (arr[r][c] != k && cnt <= 100) {
		if (n < m) C();
		else R();
		cnt++;
	}
	cout << (cnt > 100 ? -1 : cnt);
	return 0;
}