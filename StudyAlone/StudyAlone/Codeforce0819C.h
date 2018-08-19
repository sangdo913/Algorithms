#pragma once
#include<cstdio>
#include<cstring>
int len;
char str[100001];
int max = 0;
int MAX(int i1, int i2) { return i1 > i2 ? i1 : i2; }
int check() {
	int res = 1, temp = 1;
	char prev = str[0];
	for (int i = 1; i < len; i++) {
		if (str[i] != prev) {
			temp++;
			prev = str[i];
		}
		else {
			res = MAX(res, temp);
			temp = 1;
			prev = str[i];
		}
	}
	return res;
}

void swap(char &i1, char &i2) {
	char temp = i1;
	i1 = i2;
	i2 = temp;
}

void reverse(int p) {
	for (int i = 0; i < p / 2; i++) {
		swap(str[i], str[p - i]);
	}
	for (int i = p + 1; i < (len - p - 1)/2 + p + 1; i++) {
		swap(str[i], str[len - 1 - i + p + 1]);
	}
}

int cut() {

}

int Codeforce0819C() {
	for(int i = 0 ; i)
	scanf("%s\n", str);
	len = strlen(str);
	return 0;	
}