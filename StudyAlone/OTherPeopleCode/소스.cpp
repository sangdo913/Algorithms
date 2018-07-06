#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
#define R 300001
#define L 100005
#define INF 987654321
using namespace std;

int dp[2][R]; // 0: ���� �̵� 1: �� �̵�.
int test, n, k, ex, ey; // ex: n��° x , n��° y
int num[2][R];  // 0: y��ǥ�϶� �ش� ���� index��ġ. 1: x��ǥ�϶� index��ġ.
vector<int> ax[L], ay[L]; // ax: ������ x��ǥ�� �ش�Ǵ� index ����, ay : y��ǥ�� �ش�Ǵ� indext����.

struct point {
	int x, y, f;
	point(int _x, int _y, int _f) :x(_x), y(_y), f(_f) {};
};

bool cmp(point a, point b) {
	if (a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}

int f(int xy, int pos, int life, vector<point> &arr) { //life: ���� ������, pos: ���� index, xy: 0:���� 1:�Ʒ�

	if (pos >= n) return -INF;

	if (dp[xy][pos] != -1) return dp[xy][pos];

	if (arr[pos].x == ex && arr[pos].y == ey) {
		return dp[xy][pos] = arr[pos].f;
	}

	int &ret = dp[xy][pos];
	ret = -INF;
	life += arr[pos].f; // ���� index ������ ����.

	if (life - k < 0) return ret;

	for (int i = 0; i < 2; i++) {
		int sz;
		vector<int> v2;
		if (i == 0) { //  i==0 �������� �̵���(y������ �̵���)
			sz = ax[arr[pos].x].size();
			v2 = ax[arr[pos].x];// x�� ��� ������ index���� �����ϰ�����.
		}
		else { // i==1 �Ʒ��� �̵���(x������ �̵���)
			sz = ay[arr[pos].y].size();
			v2 = ay[arr[pos].y]; // y�� ��� ������ index���� �����ϰ�����.
		}
		for (int j = num[i][pos] + 1; j < sz; j++) {
			point t = arr[v2[j]];
			point tmp = arr[pos];
			if (i == 0 && tmp.x == t.x && tmp.y < t.y) ret = max(ret, f(0, v2[j], life - k, arr) + (arr[pos].f - k));
			else if (i == 1 && tmp.y == t.y && tmp.x < t.x) ret = max(ret, f(1, v2[j], life - k, arr) + (arr[pos].f - k));
		}
	}

	return ret;
}

int max(int i1, int i2) {
	return i1 > i2 ? i1 : i2;
}

int main() {

	scanf("%d", &test);

	for (int tc = 1; tc <= test; tc++) {

		vector<point> arr;

		memset(num, 0, sizeof(num));

		scanf("%d%d", &n, &k);
		int sx, sy;

		memset(dp, -1, sizeof(dp));

		for (int i = 0; i < n; i++) {
			int a, b, f;
			scanf("%d%d%d", &a, &b, &f);
			arr.push_back(point(a, b, f));
			if (i == 0) { // ������.
				sx = a;
				sy = b;
			}
			if (i == n - 1) { // ������.
				ex = a;
				ey = b;
			}
		}

		sort(arr.begin(), arr.end(), cmp);
		int cnt = 0;
		int ans = 0;

		for (auto next : arr) {
			int tmp = ax[next.x].size();  // ������ x��ǥ�� �ش� ��ǥ ����.
			ax[next.x].push_back(cnt);
			num[0][cnt] = tmp;
			tmp = ay[next.y].size();// ������ y��ǥ�� �ش� ��ǥ ����.
			ay[next.y].push_back(cnt);
			num[1][cnt] = tmp;
			if (sx == next.x && sy == next.y) ans = cnt; // ������ ����.
			cnt++;
		}

		int res = 
		printf("#%d %d\n", tc, f(0, ans, 0, arr));

		for (int i = 1; i < L; i++) {
			ax[i].clear();
			ay[i].clear();
		}

	}

	return 0;
}