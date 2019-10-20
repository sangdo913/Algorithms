#include<cstdio>

char str[101][100001];
int kmp[100000];
int rkmp[100000];
int slen;
int cursor;

int mystrlen(char *str) {
	int res = 0;
	while (str[res]) ++res;
	return res;
}
#define debug(x) ((((x)%slen)+slen)%slen)

void makeKMP(char *str) {
	int match = 0;
	for (int i = 1; i < slen; ++i) {
		while (match && str[match] != str[i]) match = kmp[match-1];

		if (str[match] == str[i]) match++;
		kmp[i] = match;
	}

	rkmp[slen - 1] = 0;
	match = 0;
	for (int i = 1; i < slen; ++i) {
		while (match && str[(slen - 1 - match)] != str[(slen - 1 - i)]) match = rkmp[slen-match];

		if (str[(slen - 1 - match)] == str[(slen -1- i)]) match++;
		rkmp[(slen -1 - i)] = match;
		if (match == slen) match = rkmp[slen-1];
	}
}
int a[100];
int rightpos(char *str,char *str2) {
	int match = 0;
	for (int i = 0; i < slen*2; ++i) {
		while (match && str2[i%slen] != str[((cursor + match) % slen)]) {
			match = kmp[(match - 1)];
		}
		if (str2[i%slen] == str[((match+ cursor) % slen)]) match++;
		if (match == slen) return i - match+1;
	}
	return slen;
}

int leftpos(char *str, char *str2) {
	int match = 0;
	for (int i = 0; i < slen*2; ++i) {
		while (match && str2[((2 * slen - 1 - i) % slen)] != str[((slen - match + cursor - 1) % slen)]) {
			match = rkmp[slen - match];
		}
		if (str2[((2*slen - 1- i)%slen)] == str[((slen -match+ cursor-1) % slen)]) match++;
		if (match == slen) return i - match+1;
	}
	
	return slen;
}

int main() {
	int tc;

	scanf(" %d ", &tc);

	while (tc--) {
		int cnt = 0;
		int n;
		scanf(" %d ", &n);
		scanf(" %s ", str);
		slen = mystrlen(str[0]);
		for (int i = 1; i <= n; ++i) {
			scanf("%s", str[i]);
			makeKMP(str[i - 1]);

			if (i & 1) {
				int r = rightpos(str[i-1], str[i]);
				cnt += r;
			}
			else {
				int l = leftpos(str[i-1], str[i]);
				cnt += l;
			}
		}

		printf("%d\n", cnt);

	}
	return 0;
}