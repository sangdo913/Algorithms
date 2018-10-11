#include <stdio.h>
using namespace std;
int ans = 100;
int N, M, H;
void cal2(int arr[11][32], int cnt) {
	int t;
	for (int i = 0; i < N - 1; i++) {
		t = i;
		for (int j = 0; j < H; j++) {
			if (arr[j][t] == 1) { t++; }
			else if (arr[j][t] == 2) { t--; }
		}
		if (t != i) { return; }
	}
	if (ans > cnt) { ans = cnt; }
	return;
}
void go(int arr[11][32], int cnt, int a, int b) {
	if (cnt == 3) { cal2(arr, cnt); return; }
	else if (cnt == 1) { cal2(arr, cnt); }
	else if (cnt == 2) { cal2(arr, cnt); }
	//int jj = b+1;
	int j;
	int c = cnt;
	for (int i = a; i < H; i++) {
		for (j = b; j < N - 1; j++) {
			if (arr[i][j] == 0 && arr[i][j + 1] == 0) {
				if (cnt < 3) {
					arr[i][j] = 1;
					arr[i][j + 1] = 2;
					go(arr, c + 1, i, j);
					arr[i][j] = 0;
					arr[i][j + 1] = 0;
				}
			}
		}
		b = 0;
	}
	return;
}
int main()
{
	int a, b;
	int arr[11][32];
	scanf("%d %d %d", &N, &M, &H);
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= H; j++) {
			arr[i][j] = 0;
		}
	}
	if (M != 0) {
		for (int i = 0; i < M; i++) {
			scanf("%d %d", &a, &b);
			a -= 1;
			b -= 1;
			arr[a][b] = 1;
			arr[a][b + 1] = 2;
		}
	}
	else { printf("0 \n"); return 0; }
	cal2(arr, 0);
	if (ans == 0) { printf("0 \n"); return 0; }
	go(arr, 0, 0, 0);
	if (ans > 3) { ans = -1; }
	printf("%d \n", ans);
	return 0;
}