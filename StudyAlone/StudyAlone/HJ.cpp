
#include <cstdio>
using namespace std;

int R, C;                    // 필드 크기
int dr[4] = { 0, 0, -1, 1 }; // 좌 우 상 하
int dc[4] = { -1, 1, 0, 0 };
static char map[20][20];            // 필드
long long rec[20][20];       // 필드 위치 별 방향, 메모리 기록

							 // 기록 초기화
void init_rec() {
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			rec[i][j] = 0;
}

// 혁셈블리 검증
bool solve(int r, int c, int dir, int mem) {
	// 프로그램 종료
	if (map[r][c] == '@')    return true;
	// 같은 조건으로 재방문 시 무한 루프로 실패
	if (rec[r][c] & ((long long)1 << (dir * 16 + mem)))    return false;
	rec[r][c] = rec[r][c] | ((long long)1 << (dir * 16 + mem));

	// 방향 설정
	int ndir = dir, nmem = mem;   // 변경한 방향, 메모리
	if (map[r][c] == '<')              ndir = 0;
	else if (map[r][c] == '>')          ndir = 1;
	else if (map[r][c] == '^')          ndir = 2;
	else if (map[r][c] == 'v')          ndir = 3;
	else if (map[r][c] == '_')          ndir = nmem == 0 ? 1 : 0;
	else if (map[r][c] == '|')          ndir = nmem == 0 ? 3 : 2;
	else if (map[r][c] == '+')          nmem = (mem + 1) % 16;
	else if (map[r][c] == '-')          nmem = mem == 0 ? 15 : mem - 1;
	else if (map[r][c] >= 48 && map[r][c] <= 57)    nmem = map[r][c] - 48;
	else if (map[r][c] == '?') {  // 4방향에 대한 DFS
		for (int ndir = 0; ndir < 4; ndir++) {
			int nr = r + dr[ndir] >= 0 ? (r + dr[ndir]) % R : R - 1;
			int nc = c + dc[ndir] >= 0 ? (c + dc[ndir]) % C : C - 1;
			if (solve(nr, nc, ndir, nmem))    return true;   // 정지 성공
		}
	}
	// 이동 및 재귀호출
	if (map[r][c] != '?') {
		int nr = r + dr[ndir] >= 0 ? (r + dr[ndir]) % R : R - 1;
		int nc = c + dc[ndir] >= 0 ? (c + dc[ndir]) % C : C - 1;
		if (solve(nr, nc, ndir, nmem))    return true;       // 정지 성공
	}
	return false;    // 정지 실패
}

int main() {
	int T;
	scanf("%d",&T);
	for (int tc = 1; tc <= T; tc++) {
		// 데이터 입력
		scanf("%d %d", &R, &C);
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
					scanf("%c", &map[i][j]);
		init_rec();    // 기록 초기화

					   // 혁셈블리 수행
		printf("#%d ", tc);
		if (solve(0, 0, 1, 0))    printf("YES\n");  // 정지
		else                    printf("NO\n");   // 정지 실패
	}
	return 0;
}

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