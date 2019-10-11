#include<iostream>
#include<vector>

using namespace std;
int n, m, d;
typedef vector<vector<int> > VVI;

VVI arr;
vector<vector<long long> > dp;

#define MAX(x,y) ((x) > (y) ? (x) :(y))
#define MIN(x,y) ((x) > (y) ? (y) : (x))

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m >> d;
	arr.resize(n, vector<int>(m, 0));
	dp.resize(n, vector<long long>(m, -10000*200000));
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> arr[i][j];

	for (int i = 0; i < m; ++i) dp[0][i] = 0;
	long long res = -10000*200000;
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			for (int k = MAX(i-d,0); k < i; ++k) {
				int llen = MIN(m, j + d - i+ k +1);

				for (int l = MAX(0, j-d + i- k); l < llen; ++l) {
					dp[i][j] = MAX(dp[k][l] + arr[i][j] * arr[k][l], dp[i][j]);
				}
			}
		}
	}

	for (int i = 0; i < m; ++i) res = MAX(res, dp[n - 1][i]);
	cout << res << endl;
	return 0;
}