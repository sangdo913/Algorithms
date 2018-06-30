//
//#include <cstdio>
//using namespace std;
//
//int R, C;                    // 필드 크기
//int dr[4] = { 0, 0, -1, 1 }; // 좌 우 상 하
//int dc[4] = { -1, 1, 0, 0 };
//static char map[20][20];            // 필드
//long long rec[20][20];       // 필드 위치 별 방향, 메모리 기록
//
//							  기록 초기화
//void init_rec() {
//	for (int i = 0; i < R; i++)
//		for (int j = 0; j < C; j++)
//			rec[i][j] = 0;
//}
//
// 혁셈블리 검증
//bool solve(int r, int c, int dir, int mem) {
//	 프로그램 종료
//	if (map[r][c] == '@')    return true;
//	 같은 조건으로 재방문 시 무한 루프로 실패
//	if (rec[r][c] & ((long long)1 << (dir * 16 + mem)))    return false;
//	rec[r][c] = rec[r][c] | ((long long)1 << (dir * 16 + mem));
//
//	 방향 설정
//	int ndir = dir, nmem = mem;   // 변경한 방향, 메모리
//	if (map[r][c] == '<')              ndir = 0;
//	else if (map[r][c] == '>')          ndir = 1;
//	else if (map[r][c] == '^')          ndir = 2;
//	else if (map[r][c] == 'v')          ndir = 3;
//	else if (map[r][c] == '_')          ndir = nmem == 0 ? 1 : 0;
//	else if (map[r][c] == '|')          ndir = nmem == 0 ? 3 : 2;
//	else if (map[r][c] == '+')          nmem = (mem + 1) % 16;
//	else if (map[r][c] == '-')          nmem = mem == 0 ? 15 : mem - 1;
//	else if (map[r][c] >= 48 && map[r][c] <= 57)    nmem = map[r][c] - 48;
//	else if (map[r][c] == '?') {  // 4방향에 대한 DFS
//		for (int ndir = 0; ndir < 4; ndir++) {
//			int nr = r + dr[ndir] >= 0 ? (r + dr[ndir]) % R : R - 1;
//			int nc = c + dc[ndir] >= 0 ? (c + dc[ndir]) % C : C - 1;
//			if (solve(nr, nc, ndir, nmem))    return true;   // 정지 성공
//		}
//	}
//	 이동 및 재귀호출
//	if (map[r][c] != '?') {
//		int nr = r + dr[ndir] >= 0 ? (r + dr[ndir]) % R : R - 1;
//		int nc = c + dc[ndir] >= 0 ? (c + dc[ndir]) % C : C - 1;
//		if (solve(nr, nc, ndir, nmem))    return true;       // 정지 성공
//	}
//	return false;    // 정지 실패
//}
//
//int main() {
//	int T;
//	scanf("%d",&T);
//	for (int tc = 1; tc <= T; tc++) {
//		 데이터 입력
//		scanf("%d %d", &R, &C);
//		for (int i = 0; i < R; i++)
//			for (int j = 0; j < C; j++)
//					scanf("%c", &map[i][j]);
//		init_rec();    // 기록 초기화
//
//					    혁셈블리 수행
//		printf("#%d ", tc);
//		if (solve(0, 0, 1, 0))    printf("YES\n");  // 정지
//		else                    printf("NO\n");   // 정지 실패
//	}
//	return 0;
//}
//
////
//#include<cstdio>
//
//void main()
//{
//
//	char T;
//
//	for (int i = 0; i < 1000; i++)
//	{
//
//		printf("%c ", T);
//
//		if (i % 100 == 0) printf("\n");
//	}
//
//}
//
//#include <stdio.h>
//int Arr[1000001];
//int Find(int x)
//{
//	if (x == Arr[x]) return x;
//	else return Arr[x] = Find(Arr[x]);
//}
//void Union(int x, int y)
//{
//	x = Find(x);
//	y = Find(y);
//	if (x != y) Arr[y] = x;
//}
//int main(void)
//{
//	int test_case;
//	int T;
//	setbuf(stdout, NULL);
//	scanf("%d", &T);
//	for (test_case = 1; test_case <= T; ++test_case)
//	{
//		int N, M, K, A, B;
//		scanf("%d %d", &N, &M);
//		 Arr = (int*)malloc(sizeof(int)*(N+1));
//		for (int i = 0; i <= N; i++)Arr[i] = i;
//		printf("#%d ", test_case);
//		for (int i = 0; i<M; i++)
//		{
//			scanf("%d %d %d", &K, &A, &B);
//			if (K == 0)
//				if (A != B)Union(A, B);
//				else
//				{
//					if (A != B)
//					{
//						A = Find(A);
//						B = Find(B);
//						if (A == B) printf("1");
//						else printf("0");
//					}
//					else printf("1");
//				}
//		}
//		printf("\n");
//	}
//	return 0; //정상종료시 반드시 0을 리턴해야 합니다.
//}
//
//
//
//#include <iostream>
//#include <cstdio>
//
//#define MAX_SIZE 1000002
//
//using namespace std;
//int parent[MAX_SIZE];
//int ran[MAX_SIZE];
//
//int find(int x) {
//	return parent[x] == x ? x : parent[x] = find(parent[x]);
//}
//
//void uni(int x, int y) {
//	x = find(x);
//	y = find(y);
//	if (x == y) return;
//	if (ran[x] < ran[y]) parent[x] = y;
//	else parent[y] = x;
//	if (ran[x] == ran[y]) ran[x]++;
//}
//
//void init(int n) {
//	for (int i = 0; i < n + 1; i++) {
//		parent[i] = i;
//	}
//}
//
//int main() {
//
//
//	freopen("input.txt", "r", stdin);
//	setbuf(stdout, NULL);
//	int Case;
//
//	scanf("%d", &Case);
//
//	for (int tc = 1; tc <= Case; tc++) {
//		printf("#%d ", tc);
//		int N, M;
//		scanf("%d %d", &N, &M);
//		init(N);
//		for (int i = 0; i < M; i++) {
//
//			int comand, A, B;
//			scanf("%d %d %d", &comand, &A, &B);
//
//			if (comand == 0) {
//				uni(A, B);
//			}
//
//			else if (comand == 1) {
//				if (find(A) == find(B)) {
//					printf("1");
//				}
//				else printf("0");
//			}
//		}
//		printf("\n");
//	}
//
//}
//
//
//
//
//
//
//
//
/////////////merge sort
//
//#include"CLOCKSYNC.h"
//#include<stdlib.h>
//#include<time.h>
//
//int datas[100];
//int temp[100];
//
//void merge(int l, int m, int r)
//{
//	int i = l, j = m + 1, k = l;
//
//	while (i <= m && j <= r)
//	{
//		if (datas[i] < datas[j])
//		{
//			temp[k++] = datas[i++];
//		}
//		else
//		{
//			temp[k++] = datas[j++];
//		}
//	}
//
//	while (i <= m) temp[k++] = datas[i++];
//	while (j <= r) temp[k++] = datas[j++];
//
//	for (int i = l; i <= r; i++) datas[i] = temp[i];
//}
//
//void mergeSort(int l, int r)
//{
//	if (l < r)
//	{
//		int m = (l + r) / 2;
//		mergeSort(l, m);
//		mergeSort(m + 1, r);
//
//		merge(l, m, r);
//	}
//}
//
//
//int main()
//{
//	srand(time(NULL));
//
//	for (int i = 0; i < 10; i++)
//	{
//		int len = rand() % 100 + 1;
//
//		printf("len : %d\n", len);
//		printf("before\n");
//		for (int i = 0; i < len; i++)
//		{
//			datas[i] = rand() % 100;
//			printf("%2d ", datas[i]);
//		}
//		printf("\n");
//
//		mergeSort(0, len - 1);
//
//
//		printf("after\n");
//		for (int i = 0; i < len; i++)
//		{
//			printf("%2d ", datas[i]);
//		}
//		printf("\n\n");
//	}
//
//	return 0;
//}
