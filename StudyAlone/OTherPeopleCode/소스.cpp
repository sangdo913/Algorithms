#include <stdio.h>
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

	return 0;
}