#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
#define R 300001
#define L 100005
#define INF 987654321
using namespace std;

int dp[2][R]; // 0: 우측 이동 1: 하 이동.
int test, n, k, ex, ey; // ex: n번째 x , n번째 y
int num[2][R];  // 0: y좌표일때 해당 값의 index위치. 1: x좌표일때 index위치.
vector<int> ax[L], ay[L]; // ax: 각각의 x좌표에 해당되는 index 저장, ay : y좌표에 해당되는 indext저장.

struct point {
	int x, y, f;
	point(int _x, int _y, int _f) :x(_x), y(_y), f(_f) {};
};

bool cmp(point a, point b) {
	if (a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}

int f(int xy, int pos, int life, vector<point> &arr) { //life: 현재 에너지, pos: 현재 index, xy: 0:우측 1:아래

	if (pos >= n) return -INF;

	if (dp[xy][pos] != -1) return dp[xy][pos];

	if (arr[pos].x == ex && arr[pos].y == ey) {
		return dp[xy][pos] = arr[pos].f;
	}

	int &ret = dp[xy][pos];
	ret = -INF;
	life += arr[pos].f; // 현재 index 에너지 습득.

	if (life - k < 0) return ret;

	for (int i = 0; i < 2; i++) {
		int sz;
		vector<int> v2;
		if (i == 0) { //  i==0 우측으로 이동시(y축으로 이동시)
			sz = ax[arr[pos].x].size();
			v2 = ax[arr[pos].x];// x가 모두 동일한 index들을 저장하고있음.
		}
		else { // i==1 아래로 이동시(x축으로 이동시)
			sz = ay[arr[pos].y].size();
			v2 = ay[arr[pos].y]; // y가 모두 동일한 index들을 저장하고있음.
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
			if (i == 0) { // 시작점.
				sx = a;
				sy = b;
			}
			if (i == n - 1) { // 도착점.
				ex = a;
				ey = b;
			}
		}

		sort(arr.begin(), arr.end(), cmp);
		int cnt = 0;
		int ans = 0;

		for (auto next : arr) {
			int tmp = ax[next.x].size();  // 동일한 x좌표에 해당 좌표 저장.
			ax[next.x].push_back(cnt);
			num[0][cnt] = tmp;
			tmp = ay[next.y].size();// 동일한 y좌표에 해당 좌표 저장.
			ay[next.y].push_back(cnt);
			num[1][cnt] = tmp;
			if (sx == next.x && sy == next.y) ans = cnt; // 시작점 저장.
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