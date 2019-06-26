#include<iostream>
#define _USE_MATH_DEFINES
#include<math.h>

using namespace std;
int beg[100];
int ed[100];
double info[3][100];
int temp[100];

void mergeSort(int arr[100],int flag, int s, int e) {
	int l = s, m = (s + e) / 2, r = m + 1, k = s;

	while (l <= m && r <= e) temp[k++] = info[flag][arr[l]] < info[flag][arr[r]] ? arr[l++] : arr[r++];
	while (l <= m) temp[k++] = arr[l++];
	while (r <= e) temp[k++] = arr[r++];

	for (int i = s; i <= e; ++i) arr[i] = temp[i];
}

void merge(int arr[100], int flag, int s, int e) {
	if (s < e) {
		int m = (s + e) / 2;
		merge(arr, flag, s, m);
		merge(arr, flag, m + 1, e);
		mergeSort(arr, flag, s, e);
	}
}

double conv(double i) {
	if (i < 0.0) return i + 2*M_PI;
	else if (i > 2 * M_PI) return i - 2 * M_PI;
	return i;
}
int getRes(int idx, int n) {
	double rotate = info[1][beg[idx]] - info[0][beg[idx]];
	if (rotate < 0.0) rotate += 2 * M_PI;
	double mmax = info[1][beg[idx]];

	int i = 1;
	int ret = 1;
	
	while (i < n &&rotate < 2 * M_PI) {
		double beggist = mmax;
		while (i<n && info[0][beg[(idx + i) % n]] <= mmax) {
			beggist = beggist > info[1][beg[(idx + i) % n]] ? beggist : info[1][beg[(idx + i) % n]];
			++i;
		}
		double plus = beggist - mmax;
		mmax = beggist;
		plus = plus < 0.0 ? plus + 2 * M_PI : plus;
		rotate += plus;
		ret++;
		if (plus == 0 && rotate < 2*M_PI) return 0x3f3f3f3f;
	}

	return rotate >= 2*M_PI ? ret : 0x3f3f3f3f;
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int c, n;

	cin >> c;

	while (c--) {
		cin >> n;
		int res = 0x3f3f3f3f;
		bool isend = false;
		int midx = 0;

		double nowmax = -1;

		for (int i = 0; i < n; ++i) {
			beg[i] = i;
			ed[i] = i;
			double x, y, r;
			cin >> y >> x >> r;


			double angle = atan2(y, x);

			if (angle < 0) angle += M_PI;

			if (y < 0.0) {
				angle += M_PI;
			}

			if (r >= 16.0) {
				res = 1;
				continue;
			}
			double alpha = asin(r / 16);
			alpha += alpha;

			if (nowmax < 2.0*alpha) {
				nowmax = 2.0*alpha;
				midx = i;
			}

			info[0][i] = conv(angle - alpha);
			info[1][i] = conv(angle + alpha);
		
			if (info[0][i] > info[1][i]) info[0][i] -= 2 * M_PI;
		}

		merge(beg, 0, 0, n - 1);

		//for (int i = 0; i < n; ++i) cout << info[0][beg[i]] << ' ' << info[1][beg[i]]<<'\n';
		//cout << '\n';

		if (res == 1){
			cout << 1 << '\n'; continue;
		}

		for (int i = 0; i < n; ++i) {
			if (info[0][beg[i]] > 0.0) { break; }
			int temp = getRes(i, n);
			res = temp < res ? temp : res;
		}

		if (res == 0x3f3f3f3f) cout << "IMPOSSIBLE\n";
		else cout << res << '\n';
	}
	
	return  0;
}
