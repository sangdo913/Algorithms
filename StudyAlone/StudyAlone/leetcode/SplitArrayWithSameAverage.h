#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

int dp[30][30][300001];
int n;

int getdp(vector<int> &A, int l, int k, int dest) {
	if (dest == 0) {
		if (k) return false;
		return true;
	}
	if (k == 0) return false;
	if (l == n) return false;
	if (dp[l][k][dest]!= -1) return dp[l][k][dest];
	if (A[l] <= dest) dp[l][k][dest] = getdp(A, l + 1, k - 1, dest - A[l]);
	else dp[l][k][dest] = 0;
	if (dp[l][k][dest]) return true;
	return getdp(A, l + 1, k, dest);
}
class Solution {
public:
	bool splitArraySameAverage(vector<int>& A) {
		int sum = 0;
		for (int i = 0; i < A.size(); ++i) sum += A[i];
		n = A.size();
		for (int i = 0; i < n; ++i)for(int k = 0; k < n; ++k) for (int j = 0; j <= sum; ++j) dp[i][k][j] = -1;
		for (int k = 1; k < n; ++k) {
			if (sum*(n-k)%n == 0 && (sum*k) % n == 0) {
				if (getdp(A, 0, k, sum*k/n)) return true;
			}
		}
		return false;
	}
};

int main() {
	int n;
	scanf("%d", &n);
	vector <int> A;
	for (int i = 0; i < n; ++i) {
		int in;
		scanf("%d", &in);
		A.push_back(in);
	}
	printf("%d\n", Solution().splitArraySameAverage(A));
	return 0;
}
