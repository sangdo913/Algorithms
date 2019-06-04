#include<iostream>

using namespace std;

typedef unsigned long long ull;

char in[500001][21];
#define HASHSIZE 1000007

int mystrlen(char *in) {
	int ret = 0;
	while (*in)in++, ret++;
	return ret;
}

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
int rlen;
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
		if (table[key]) res[rlen++] = table[key];
	}

	printf("%d\n", rlen);


	return 0;
}
