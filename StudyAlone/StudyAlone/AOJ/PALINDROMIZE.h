#include<stdio.h>

int kmp[200001];
int len;
char str[200001], s1[100001], s2[100001];
int mystrplus(char *s1, char *s2) {
	int len = 0;
	while (s1[len]) str[len] = s1[len], ++len;
	while (*s2) str[len++] = *s2++;
	return len;
}

void mkkmp(int len) {
	int match = 0;
	for (int i = 1; i < len; ++i) {
		while (match && str[i] != str[match]) match = kmp[match - 1];

		if (str[i] == str[match]) {
			match++;
			if (match == len / 2) match = kmp[match - 1];
		}
		kmp[i] = match;
	}
}

int main() {
	int tc;
	scanf("%d", &tc);
	while (tc--) {
		scanf("%s", s1);
		int len = 0;
		while (s1[len]) len++;

		bool pelin = true;
		for (int i = 0; i < len / 2; ++i) {
			if (s1[i] != s1[len - 1 - i]) {
				pelin = false;
				break;
			}
		}

		if (pelin) {
			printf("%d\n", len);
			continue;
		}

		for (int i = len - 1; i>=0; --i) s2[len - i - 1] = s1[i];

		s2[len] = 0;
		mystrplus(s2, s1);
		mkkmp(len*2);
		printf("%d\n", 2*len - kmp[2*len-1]);
	}
	return 0;
}