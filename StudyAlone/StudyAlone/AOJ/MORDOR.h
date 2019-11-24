#include<stdio.h>
int n;
int q;
int mymintree[400001];
int mymaxtree[400001];

struct RES {
	int min, max;
};
RES insert(int id,int to, int start, int end, int v) {
	if (to < start || end < to) return{ 0x3f3f3f3f,-0x3f3f3f3f };

	if (start == end) { mymintree[id] = mymaxtree[id] = v; return { v,v }; }

	int m = (start + end) / 2;
	RES r1 = insert(id * 2, to, start, m, v);
	RES r2 = insert(id * 2 + 1,to, m + 1, end, v);

	r1.min = r1.min < r2.min ? r1.min : r2.min;
	r1.max = r1.max < r2.max ? r2.max : r1.max;
	mymintree[id] = mymintree[id] < r1.min ? mymintree[id] : r1.min;
	mymaxtree[id] = mymaxtree[id] < r1.max ? r1.max : mymaxtree[id];

	return { mymintree[id], mymaxtree[id] };
}

RES query(int id, int from, int to, int start, int end) {
	if (to < start || end < from)  return {0x3f3f3f3f, -0x3f3f3f3f };

	if (from <= start  && end <= to) {
		return { mymintree[id], mymaxtree[id] };
	}

	int m = (start + end) / 2;
	RES r1 = query(id * 2, from, to, start, m);
	RES r2 = query(id * 2 + 1, from, to, m + 1, end);
	return { r1.min < r2.min ? r1.min : r2.min, r1.max < r2.max ? r2.max : r1.max };
}

int main() {
	int tc;
	scanf("%d", &tc);
	while (tc--) {
		int h;
		scanf("%d %d", &n, &q);

		for (int i = 1; i <= 4 * n; ++i) {
			mymintree[i] = 0x3f3f3f3f;
			mymaxtree[i] = -0x3f3f3f3f;
		}

		for (int i = 0; i < n; ++i) {
			scanf("%d", &h);
			insert(1, i, 0, n - 1, h);
		}

		int from, to;
		while (q--) {
			scanf("%d %d", &from, &to);
			RES ans = query(1, from, to, 0, n - 1);
			printf("%d\n", ans.max - ans.min);
		}
	}

	return 0;
}