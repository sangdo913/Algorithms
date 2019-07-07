#include<iostream>
#define SIZE 1000007

using namespace std;

int HASH[SIZE];
typedef unsigned int ui;

char s[51][11];
int res;
long long canmake[51];
int	oknum[51];
int canbemake[51][51];
int clen[51];

void mysort(int idx) {
	for (int i = 1; i < clen[idx]; ++i) {
		int j = i;

		while (j && oknum[canbemake[idx][j-1]]< oknum[canbemake[idx][j]]) 
			canbemake[idx][j] ^= canbemake[idx][j - 1] ^= canbemake[idx][j] ^= canbemake[idx][j - 1], --j;
	}
}

int n, m;

inline int getlen(int i) {
	int j = 0;
	while (s[i][j]) { ++j; }
	return j;
}

ui getK(int i) {
	ui key = 0;
	int j = 0;

	while (s[i][j]) key = ((key << 5) + 5381) % SIZE, ++j;
	
	return key;
}

int mystrcmp(const char *a, const char*b) {
	while (*a && *a == *b) a++, b++;
	return *a - *b;
}

void comb(int idx, long long visit, int cnt) {
	if (res <= cnt) return;
	if ((visit>>1) == (1LL << n) - 1) {
		res = res < cnt ? res : cnt;
		return;
	}

	if (idx == n+1) return;
	if (visit &(1LL << idx)) return comb(idx+1, visit, cnt);

	for (int i = 0; i < clen[idx]; ++i) {
		comb(idx + 1, visit | canmake[canbemake[idx][i]], cnt + 1);
	}
}

int main() {
	int tc;
	cin >> tc;
	while (tc--) {
		cin >> n >> m;
		res = 0x3f3f3f3f;
		for (int i = 0; i < m; ++i) canmake[i] = 0;
		for (int i = 1; i <= n; ++i)  clen[i] = 0;
		for (int i = 0; i < SIZE; ++i) HASH[i] = 0;
		for (int i = 1; i <= n; ++i) {
			cin >> s[i];
			
			ui key = getK(i);

			while (HASH[key]) {
				key++;
				if (key == SIZE) key = 0;
			}
			HASH[key] = i;
		}

		for (int ii = 0; ii < m; ++ii) {
			cin >> oknum[ii];

			for (int iii = 0; iii < oknum[ii]; ++iii) {
				char in[11];
				cin >> in;

				int i = 0;
				ui key = 0;
				while (in[i]) key = ((key << 5) + 5381) % SIZE, ++i;
				while (mystrcmp(s[HASH[key]], in)) key = (key + 1) % SIZE;
				canmake[ii] |= 1LL << HASH[key];
				canbemake[HASH[key]][clen[HASH[key]]++] = ii;
			}
		}

		for (int i = 1; i <= n; ++i) mysort(i);
		comb(1, 0, 0);
			
		cout << res << '\n';
	}

	return 0;
}
