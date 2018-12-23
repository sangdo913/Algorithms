#include<queue>
#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;

struct INFO {
	int value, first, second;
};

vector<int> info[2];
vector<int> indexes;
int n, m, b;

bool operator<(const INFO& i1, const INFO& i2) {
	return i1.value > i2.value;
}

int DO() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int tc;
	cin >> tc;

	for (int t = 1; t <= tc; t++) {
		cin >> n >> m >> b;
		info[0].clear(); info[1].clear();
		indexes.clear();

		for (int i = 0; i < m; i++) {
			indexes.push_back(i);
		}

		for (int i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b;

			info[0].push_back(a);
			info[1].push_back(b);
		}

		priority_queue<INFO> pq;

		for (int i = 0; i < m; i++) {
			if (info[0][i] >= b) pq.push({ info[0][i],i,-1 });

			for (int j = i; j < m; j++) {
				if (info[0][i] + info[0][j] >= b) pq.push({ info[0][i] + info[0][j], i, j});
			}
		}

		int res = 0;
		int cnt = 0;

		while (cnt != n) {
			if (pq.size() == 0) { res = -1; break; }

			INFO i = pq.top();

			if (i.second == -1) {
				if (info[1][i.first] == 0) { pq.pop(); continue; }

				info[1][i.first]--;
				res += i.value;
				cnt++;
			}

			else if (i.first == i.second) {
				if (info[1][i.first] < 2) {
					pq.pop(); continue;
				}

				info[1][i.first] -= 2;
				res += i.value;
				cnt++;
			}

			else {
				if (info[1][i.first] == 0 || info[1][i.second] == 0) {
					pq.pop(); continue;
				}

				info[1][i.first]--, info[1][i.second]--;
				res += i.value;
				cnt++;
			}
		}
		cout << '#' << t << ' ' << res << '\n';
	}

	return 0;
}
