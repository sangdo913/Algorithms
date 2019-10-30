#include<stdio.h>

int p[100000][50];
int depth[100000];
int *vec[100000];
int vsize[100000];
int vlen[100000];
int mystack[100000];

int getlog(int n) {
	int res = 0;
	while (n) res++, n>>=1;
	return  res;
}

int main() {
	int tc;
	scanf("%d", &tc);
	for(int t = 1; t <= tc; ++t){
		int n, q;
		scanf("%d %d", &n, &q);
		int until = getlog(n);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j <= until; ++j) p[i][j] = 0;
			if (vec[i]) delete[]vec[i];
			vec[i] = new int[10];
			vsize[i] = 10;
			vlen[i] = 0;
		}

		for (int i = 1; i < n; ++i) {
			 scanf("%d",p + i);
			if (vsize[p[i][0]] == vlen[p[i][0]]) {
				int *nvec = new int[vlen[p[i][0]] * 2];
				for (int j = 0; j < vsize[p[i][0]]; ++j) nvec[j] = vec[p[i][0]][j];
				delete[] vec[p[i][0]];
				vec[p[i][0]] = nvec;
				vsize[p[i][0]] *= 2;
			}
			vec[p[i][0]][vlen[p[i][0]]++] = i;
		}
		int stsize = 0;
		mystack[stsize++] = 0;
		while (stsize) {
			int now = mystack[--stsize];

			for (int i = 0; i < vlen[now]; ++i) {
				int next = vec[now][i];
				depth[next] = depth[now] + 1;
				mystack[stsize++] = next;
			}
		}

		for (int i = 0; i < until; ++i) {
			for (int j = 0; j < n; ++j) {
				p[j][i + 1] = p[p[j][i]][i];
			}
		}

		int a, b;
		while (q--) {
			scanf("%d %d", &a, &b);
			int d1 = depth[a], d2 = depth[b];
			int diff = d1 - d2;
			if (diff < 0) {
				a ^= b ^= a ^= b;
				diff = -diff;
			}

			int i = 0;
			while (diff) {
				if (diff & 1) {
					a = p[a][i];
				}
				++i;
				diff >>= 1;
			}

			if (a != b) {
				for (int i = until; i >= 0; --i) {
					if (p[a][i] != p[b][i]) b = p[b][i], a = p[a][i];
				}
				a = p[a][0];
			}

			printf("%d\n", d1 + d2 - 2 * depth[a]);
		}
	}

	for (int i = 0; i < 100000; ++i) if (vec[i]) delete[] vec[i];
	return 0;
}