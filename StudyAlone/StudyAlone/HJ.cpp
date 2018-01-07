
#include <cstdio>
using namespace std;

int R, C;                    // �ʵ� ũ��
int dr[4] = { 0, 0, -1, 1 }; // �� �� �� ��
int dc[4] = { -1, 1, 0, 0 };
static char map[20][20];            // �ʵ�
long long rec[20][20];       // �ʵ� ��ġ �� ����, �޸� ���

							 // ��� �ʱ�ȭ
void init_rec() {
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			rec[i][j] = 0;
}

// ������ ����
bool solve(int r, int c, int dir, int mem) {
	// ���α׷� ����
	if (map[r][c] == '@')    return true;
	// ���� �������� ��湮 �� ���� ������ ����
	if (rec[r][c] & ((long long)1 << (dir * 16 + mem)))    return false;
	rec[r][c] = rec[r][c] | ((long long)1 << (dir * 16 + mem));

	// ���� ����
	int ndir = dir, nmem = mem;   // ������ ����, �޸�
	if (map[r][c] == '<')              ndir = 0;
	else if (map[r][c] == '>')          ndir = 1;
	else if (map[r][c] == '^')          ndir = 2;
	else if (map[r][c] == 'v')          ndir = 3;
	else if (map[r][c] == '_')          ndir = nmem == 0 ? 1 : 0;
	else if (map[r][c] == '|')          ndir = nmem == 0 ? 3 : 2;
	else if (map[r][c] == '+')          nmem = (mem + 1) % 16;
	else if (map[r][c] == '-')          nmem = mem == 0 ? 15 : mem - 1;
	else if (map[r][c] >= 48 && map[r][c] <= 57)    nmem = map[r][c] - 48;
	else if (map[r][c] == '?') {  // 4���⿡ ���� DFS
		for (int ndir = 0; ndir < 4; ndir++) {
			int nr = r + dr[ndir] >= 0 ? (r + dr[ndir]) % R : R - 1;
			int nc = c + dc[ndir] >= 0 ? (c + dc[ndir]) % C : C - 1;
			if (solve(nr, nc, ndir, nmem))    return true;   // ���� ����
		}
	}
	// �̵� �� ���ȣ��
	if (map[r][c] != '?') {
		int nr = r + dr[ndir] >= 0 ? (r + dr[ndir]) % R : R - 1;
		int nc = c + dc[ndir] >= 0 ? (c + dc[ndir]) % C : C - 1;
		if (solve(nr, nc, ndir, nmem))    return true;       // ���� ����
	}
	return false;    // ���� ����
}

int main() {
	int T;
	scanf("%d",&T);
	for (int tc = 1; tc <= T; tc++) {
		// ������ �Է�
		scanf("%d %d", &R, &C);
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
					scanf("%c", &map[i][j]);
		init_rec();    // ��� �ʱ�ȭ

					   // ������ ����
		printf("#%d ", tc);
		if (solve(0, 0, 1, 0))    printf("YES\n");  // ����
		else                    printf("NO\n");   // ���� ����
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