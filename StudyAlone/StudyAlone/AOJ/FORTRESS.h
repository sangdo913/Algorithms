#include<cstdio>

#define DIST(x1,x2,y1,y2) (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)

int X[100];
int Y[100];
int R[100];
int idx[100];
int temp[100];
int n;

void mergeSort(int s, int e) {
	int l = s, m = (s + e) / 2, r = m + 1, k = s;
	while (l <= m && r <= e) {
		temp[k++] = R[idx[l]] > R[idx[r]] ? idx[l++] : idx[r++];
	}
	while (l <= m) temp[k++] = idx[l++];
	while (r <= e) temp[k++] = idx[r++];
	for (int i = s; i <= e; ++i) idx[i] = temp[i];
}
void merge(int s, int e) {
	if (s < e) {
		int m = (s + e) / 2;
		merge(s, m);
		merge(m + 1, e);
		mergeSort(s, e);
	}
}

struct WALL {
	int idx;
	int child[100];
	int csize;
}walls[100];

double getroot(int i) {
	double s = 0, e = 1000,m;
	int cnt = 100;
	while (cnt--) {
		m = (s + e) / 2;
		if (m*m < (double)i) s = m;
		else e = m;
	}
	return m;
}
bool isin(int i, int j) {
	return getroot(DIST(X[i], X[j], Y[i], Y[j])) + (double)R[j] < (double)R[i];
}

void insert(int wid, int id) {
	for (int i = 0; i < walls[wid].csize; ++i) {
		if (isin(walls[wid].child[i], id)) {
			insert(walls[wid].child[i], id);
			return;
		}
	}
	walls[wid].child[walls[wid].csize++] = id;
}

int mmax;

int getmaxlen(int wid) {
	int first = 0, second = 0;
	int num;

	for (int i = 0; i < walls[wid].csize; ++i) {
		num = getmaxlen(walls[wid].child[i]);
		if (num > first) num ^= first ^= num ^= first;
		if (num > second) num ^= second ^= num ^= second;
	}
	mmax = first + second > mmax ? first + second : mmax;
	return first + 1;
}

int main() {
	int tc;
	scanf("%d", &tc);

	while (tc--) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%d %d %d", X + i, Y + i, R + i);
		}
		for (int i = 0; i < n; ++i) idx[i] = i;
		merge(0, n - 1);
		walls[0].csize = 0;
		walls[0].idx = 0;
		mmax = 0;
		
		for (int i = 1; i < n; ++i) {
			walls[idx[i]].csize = 0;
			walls[idx[i]].idx = idx[i];
			insert(0, idx[i]);
		}
		int res = getmaxlen(0)-1;
		printf("%d\n", res > mmax ? res : mmax);
	}
	return 0;
}