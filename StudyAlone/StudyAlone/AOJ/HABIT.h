#include<cstdio>

char str[5000];
int g[5000];
int ng[5000];
int len;
int sa[5000];
int temp[5000];
int invsa[5000];
int lca[5000];
int t;


bool cmp(int i, int j) {
	if (g[i] != g[j]) return g[i] < g[j];
	return g[i + t] < g[j + t];
}

int mystrlen(char *str) {
	int ret = 0;
	while (str[ret])ret ++;
	return ret;
}

void mergeSort(int l, int r) {
	int s = l,  m = (l + r) / 2, e = m+1;
	int k = l;

	while (s <= m&& e <= r) { temp[k++] = cmp(sa[s], sa[e]) ? sa[s++] : sa[e++]; }
	while (s <= m) temp[k++] = sa[s++];
	while (e <= r) temp[k++] = sa[e++];
	for (int i = l; i <= r; ++i) sa[i] = temp[i];
}
void merge(int l, int r) {
	if (l < r) {
		int m = (l + r) / 2;
		merge(l, m);
		merge(m + 1, r);
		mergeSort(l, r);
	}
}
int main() {
	int tc;
	scanf("%d", &tc);
	while (tc--) {
		int k;
		scanf("%d %s", &k, str);
		len = mystrlen(str);
		for (int i = 0; i < len; ++i) sa[i] = i, g[i] = str[i];

		t = 1;
		g[len] = -1;
		while (t <= len) {
			merge(0, len - 1);
			ng[sa[0]] = 0; 

			for (int i = 1; i < len; ++i) {
				if (cmp(sa[i - 1], sa[i])) ng[sa[i]] = ng[sa[i-1]] + 1;
				else ng[sa[i]] = ng[sa[i-1]];
			}
			for (int i = 0; i < len; ++i) g[i] = ng[i];
			t <<= 1;
		}

		for (int i = 0; i < len; ++i) { invsa[sa[i]] = i; }

		int size = 0;
		for (int i = 0; i < len; ++i) {
			int inv = invsa[i];
			if (inv) {
				while (str[sa[inv] + size] == str[sa[inv - 1] + size]) size++;
				lca[inv] = size;
			}
			size -= size > 0;
		}

		int res = 0;
		for (int i = 0; i <= len-k+1; ++i) {
			int mmin = 0x3f3f3f3f;
			for (int j = 0; j < k-1; ++j) {
				mmin = mmin < lca[i + j] ? mmin : lca[i + j];
			}
			res = mmin > res ? mmin : res;
		}
		printf("%d\n", k == 1 ? len : res);
	}
}