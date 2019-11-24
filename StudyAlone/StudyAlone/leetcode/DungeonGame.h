#include<iostream>
#include<vector>
#include<queue>

using namespace std;

#define MAX(x,y) ((x) > (y) ? (x) : (y))

class Solution {
public:
	int calculateMinimumHP(vector<vector<int>>& dungeon) {
		int n = dungeon.size();
		 int m = dungeon[0].size();
		vector<vector<int> > info = vector<vector<int> >(n, vector<int>(m, (int)0x80000000));
		info[n-1][m-1] = dungeon[n-1][m-1];
		if (info[n - 1][m - 1] > 0) info[n - 1][m - 1] = 0;
		for (int i = n-1; i >=0; --i) for (int j = m-1; j >=0; --j) {
			if (i) {
				info[i - 1][j] = MAX(info[i - 1][j], info[i][j] + dungeon[i - 1][j]);
				if (info[i - 1][j] > 0) info[i - 1][j] = 0;
			}
			if (j) {
				info[i][j - 1] = MAX(info[i][j - 1], info[i][j] + dungeon[i][j - 1]);
				if (info[i ][j-1] > 0) info[i][j-1] = 0;
			}
		}

		return -info[0][0] + 1;
	}
};

int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int> > vec;
	vec.resize(n, vector<int>(m));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) cin >> vec[i][j];
	}
	Solution s = Solution();
	cout << s.calculateMinimumHP(vec);
}