#include<stdio.h>
char str[400001];
char str1[400001], str2[400001];
int kmptable[400000];
int st[400000];
int sz = 0;
int mystrplus(char *s1, char *s2) {
	int len = 0,len2 = 0;
	while (s1[len]) str[len] = str1[len], len++;
	while (*s2) str[len++] = *(s2++);
	return len;
}

void mkkmp(int len) {
	int match = 0;
	for (int i = 1; i < len; ++i) {
		while (match && str[i] != str[match]) 
			match = kmptable[match-1];
		
		if (str[match] == str[i]) {
			match++;
			kmptable[i] = match;

			if (match == len) {
				match = kmptable[i - 1];
			}
		}
	}
}

int main() {
	scanf("%s %s", str1, str2);

	int len = mystrplus(str1, str2);
	mkkmp(len);

	int match = len;

	while (match) {
		st[sz++] = match;
		match = kmptable[match - 1];
	}
	while (sz) {
		printf("%d ", st[--sz]);
	}
	return 0;
}