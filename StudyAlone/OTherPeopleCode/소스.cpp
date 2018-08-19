<<<<<<< HEAD
﻿#pragma once
#include<cstdio>
#include<string>
#include<string.h>

using namespace std;

char str[2][300000];
int n, m;

bool find(int p) {
	int pos = m - (n - p - 1);
	if (pos < p) return false;
	return (strcmp(str[0] + p + 1, str[1] + pos) == 0);
}

int main() {

	scanf("%d %d\n", &n, &m);
	scanf("%s\n%s\n", str[0], str[1]);
	bool res = true;
	int i = 0;
	while (true) {
		if (str[0][i] == '*') {
			res = find(i);
			break;
		}

		else if (str[0][i] != str[1][i]) {
			res = false;
			break;
		}
		else if (str[0][i] == 0 && str[1][i] == 0) {
			res = true; break;
		}
		i++;
	}

	if (res) { printf("YES\n"); }
	else { printf("NO\n"); }

=======
﻿#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

float arr[1001];
int num, top;

float post(float arr[], int index, int n) {
		if (arr[index] == '+') {
			return (post(arr, 2 * index, n) + post(arr, 2 * index + 1, n));
		}
		else if (arr[index] == '-') {
			return (post(arr, 2 * index, n) - post(arr, 2 * index + 1, n));
		}
		else if (arr[index] == '*') {
			return (post(arr, 2 * index, n) * post(arr, 2 * index + 1, n));
		}
		else if (arr[index] == '/') {
			return (post(arr, 2 * index, n) / post(arr, 2 * index + 1, n));
		}
		else return arr[index];
}

int main() {
	int i, j, k;
	int index, left, right;

	for (i = 1; i <= 1; i++) {
		scanf("%d", &num);
		top = -1;
		for (j = 1; j <= num; j++) {
			float sum;
			char ch[20];
			scanf("%d", &index);
			scanf("%s", &ch[0]);
			if (ch[0] == '+' || ch[0] == '-' || ch[0] == '*' || ch[0] == '/') {
				scanf("%d %d", &left, &right);
				arr[index] = ch[0];
			}
			else {
				sum = 0;

				for (k = 0; ch[k]; k++) {
					sum += (ch[k] - '0');
					sum *= 10;
				}
				sum /= 10;
				arr[index] = sum;
			}
		}
		//for (j = 1; j <= num; j++) printf("%.f ", arr[j]);
		printf("#%d %.f\n", i, post(arr, 1, num));
		
	}

>>>>>>> d5028c8e05cf64d849338a8c5008d412372ae8a8
	return 0;
}