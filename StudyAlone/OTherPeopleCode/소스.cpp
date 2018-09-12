#include<stdlib.h>
#include<stdio.h>
#include<queue>
#include<cstring>
#include<utility>
using namespace std;
typedef struct info {
	int people;
	int A_index;
	int flag;
	int time;
};
queue<info>Q1;
queue<info>Q2;
int N, M, K, A, B;
int A_arr[10];
int B_arr[10];
int time[1005];
info A_check[10];
info B_check[10];

int main() {
	int T, i, j, ti, sum;
	int index, cnt;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		memset(time, -1, sizeof(time));
		while (!Q1.empty())
		{
			Q1.pop();
		}
		while (!Q2.empty())
		{
			Q2.pop();
		}
		index = 0;
		sum = 0;
		ti = -1;
		cnt = 0;
		scanf("%d %d %d %d %d", &N, &M, &K, &A, &B);
		for (i = 0; i < N; i++) {
			scanf("%d", &A_arr[i]);
			A_check[i] = { 0,0,-1,0 };
		}
		for (i = 0; i < M; i++) {
			scanf("%d", &B_arr[i]);
			B_check[i] = { 0,0,-1,0 };
		}
		for (i = 0; i < K; i++)
			scanf("%d", &time[i]);
		int cnum = 1;
		while (1)
		{
			if (cnt == K)
				break;
			ti++;

			while (ti == time[index])
			{
				Q1.push({ index,0,0,ti });	// 접수창고 기다리는 사람
				index++;
			}

			for (i = 0; i < N; i++) {	//접수 창고에서 나온다
				if ((ti - A_check[i].time)   == A_arr[i] && A_check[i].flag != -1) {
					Q2.push({ A_check[i].people,i,0,ti }); A_check[i].flag = -1;	//사람 번호랑 접수창고 번호
				}
			}

			for (i = 0; i < N; i++) {	//접수 창고에 들어간다
				if (A_check[i].flag == -1 && !Q1.empty()) {	//i번째 창고가 비어있고 기다리는 사람있으면
					A_check[i] = Q1.front(); Q1.pop(); //A_check[i]에는 사람 번호 들어가있음
					A_check[i].flag = 0;
					A_check[i].time = ti;
				}
			}

			for (j = 0; j < M; j++) {	//정비창고에서 나온다
				if ((ti - B_check[j].time) % B_arr[j] == 0 && B_check[j].flag != -1) {
					if (j == B - 1 && B_check[j].A_index == A - 1) {
						sum += (B_check[j].people +1);
					}
					cnt++;
					B_check[j].flag = -1;
				}
			}

			for (j = 0; j < M; j++) {	//정비창고에 들어간다.
				if (B_check[j].flag == -1 && !Q2.empty()) {
					B_check[j] = Q2.front(); Q2.pop();	//j번쨰 정비창구에 들어간 사람번호 및 접수창고 번호
					B_check[j].time = ti;
					B_check[j].flag = 0;
				}
			}
			/*printf("\ntime : %d\n", ti);
			for (i = 0; i < N; i++) {
			if (A_check[i].flag != -1)
			printf("%d ", A_check[i].people + 1);
			else
			printf("0 ");
			}
			for (j = 0; j < M; j++) {
			if (B_check[j].flag != -1)
			printf("%d ", B_check[j].people + 1);
			else
			printf("0 ");
			}*/
		}
		if (sum == 0)
			printf("#%d -1\n", tc);
		else
			printf("#%d %d\n", tc, sum);

	}
	return 0;
}