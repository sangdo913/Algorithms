#include<iostream>

using namespace std;

typedef unsigned long long ull;

char in[500001][21];
#define HASHSIZE 1000007

ull gethash(char *in) {
	ull key = 0;
	while (*in) {
		key = ((key<<5) +5381 + *in++) %  HASHSIZE;
	}
	return key;
}

int n, m;
int table[HASHSIZE];

int mystrcmp(char *s1, char*s2) {
	while (*s1 &&*s1 == *s2) s1++, s2++;
	return *s1 - *s2;
}
int res[500000];
int temp[500000];
int rlen;

void mergeSort(int s, int e) {
	int l = s, m = (s + e) / 2, r = m + 1, k = l;
	while (l <= m && r <= e) {
		temp[k++] = mystrcmp(in[res[l]], in[res[r]]) < 0 ? res[l++] : res[r++];
	}
	while (l <= m) temp[k++] = res[l++];
	while (r <= e) temp[k++] = res[r++];

	for (int i = s; i <= e; ++i) res[i] = temp[i];
}

void merge(int s, int e) {
	if (s < e) {
		int m = (s + e) / 2;
		merge(s, m);
		merge(m + 1, e);
		mergeSort(s, e);
	}
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> in[i];
		int key = gethash(in[i]);
		while (table[key]) { key = (key + 1) % HASHSIZE; }
		table[key] = i;
	}

	while (m--) {
		char s[21];
		cin >> s;
		int key = gethash(s);

		while (table[key] && mystrcmp(in[table[key]], s)) {
			key = (key + 1) % HASHSIZE;
		}
		if (table[key]) {
			res[rlen++] = table[key];
		}
	}
	merge(0, rlen - 1);

	printf("%d\n", rlen);
	for (int i = 0; i < rlen; ++i) printf("%s\n", in[res[i]]);

	return 0;
}
