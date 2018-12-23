#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

vector<int> info[2];
vector<bool> check;
vector<int> sorted[2];

struct xcmp {
	bool operator()(int i1, int i2) {
		if (info[0][i1] == info[0][i2]) {
			return info[1][i1] < info[1][i2];
		}

		return info[0][i1] < info[0][i2];
	}
};

struct ycmp {
	bool operator()(int i1, int i2) {
		if (info[1][i1] == info[1][i2]) {
			return info[0][i1] < info[0][i2];
		}

		return info[1][i1] > info[1][i2];
	}
};

int main() {
	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		int n;
		cin >> n;
		info[0].clear(); info[1].clear();
		sorted[0].clear(); sorted[1].clear();
		check.clear();
		check.resize(n+1);


		info[0].push_back(0); info[1].push_back(0);

		for (int i = 0; i < n; i++) {
			int x, y;
			cin >> x >> y;
			info[0].push_back(x);
			info[1].push_back(y);
		}

		for (int i = 1; i <= n; i++) {
			sorted[0].push_back(i);
			sorted[1].push_back(i);
		}

		sort(sorted[0].begin(), sorted[0].end(), xcmp());
		sort(sorted[1].begin(), sorted[1].end(), ycmp());

		int yvalue = 0x7fffffff;
		int xvalue = -1;
		cout << '#' << tc;

		for (int i = 0; i < sorted[0].size(); i++) {
			int y = info[1][sorted[0][i]];
			int x = info[0][sorted[0][i]];

			if (y >= yvalue || xvalue == x) continue;
			
			yvalue = y;
			xvalue = x;
			cout << ' ' << sorted[0][i];
		}
		cout << '\n';
	}
	return 0;
}
