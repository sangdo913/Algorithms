//사다리타기
//전체 로직 : 주어진 사다리에서 가로선을 그릴 수 있는곳만 v에 담고, v의 원소들에 대해 1개추가, 2개추가 3개추가를 진행해 anw값이 -1에서 바뀌면 break해서 바뀐 횟수 출력
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <cstring>
#define P pair<int, int>
using namespace std;

int N, M, H;
int anw = -1;
int horizon[32][12]; //[i][j] : j번째 세로줄과 j+1번째 세로줄 사이에 있는 i번째 가로줄 유무(없으면 0 있으면 1)
int cantline[32][12]; // 가로줄을 놓을 수 없는 곳의 좌표(기존에 세로줄이 있거나, 왼쪽과 오른쪽에 있으면 안된다.)
vector <P> v;//가로줄을 놓을 수 있는 곳의 좌표들

void check_cantline(int x, int y); //가로줄을 놓을 수 없는 곳에 체크
void check_vertical();//가로줄을 놓을 수 있는곳의 좌표들을 v에 저장
bool check_answer();//i번째 줄이 i번째로 떨어지는지 체크(맞으면 1, 틀리면 0)
void dfs(int idx, int cnt, int n);//가로줄을 n개 추가로 생성해서 정답 체크




int main()
{
	scanf("%d %d %d", &N, &M, &H);
	for (int i = 0; i < M; i++)
	{
		int a, b;
		scanf("%d %d", &a, &b);
		horizon[a][b] = 1;
		check_cantline(a, b);
	}

	//세로줄을 놓을 수 있는 곳의 좌표를 vector에 저장
	check_vertical();

	//세로줄을 놓을 수 있는 곳이 있을때만 탐색
	if (v.size() != 0)
	{
		//세로줄을 0개부터 3개까지 놓는 완전 탐색 진행
		for (int i = 0; i <= 3; i++)
		{
			dfs(0, 0, i);
			if (anw != -1) break;
		}
	}


	printf("%d\n", anw);
}

void check_cantline(int x, int y)
{
	//왼쪽 체크
	if (y - 1 > 0) cantline[x][y - 1] = 1;
	//본인 체크
	cantline[x][y] = 1;
	//오른쪽 체크
	if (y + 1 <= N - 1) cantline[x][y + 1] = 1;
}

void check_vertical()
{
	for (int i = 1; i <= N - 1; i++)
	{
		for (int j = 1; j <= H; j++)
		{
			if (cantline[j][i] != 1) v.push_back(P(j, i));
		}
	}
}

bool check_answer()//i번째 줄이 i번째로 떨어지는지 체크(맞으면 1, 틀리면 0)
{
	for (int i = 1; i < N; i++)
	{
		int start_n = i;
		for (int j = 1; j <= H; j++)
		{
			if (horizon[j][start_n] == 1) start_n++;
			else if (start_n - 1 != 0)
			{
				if (horizon[j][start_n - 1] == 1) start_n--;
			}
		}
		if (start_n != i) return false;
	}
	return true;
}

void dfs(int idx, int cnt, int n)
{
	if (cnt == n)
	{
		if (check_answer())
		{
			anw = n;
		}
		return;
	}
	if (idx == v.size())
	{
		return;
	}

	int i = v[idx].first;
	int j = v[idx].second;

	//가로줄 추가하고 다음 idx
	if (j == 1)//제일 왼쪽줄이면 오른쪽만 체크
	{
		if (horizon[i][j + 1] == 0)
		{
			horizon[i][j] = 1;
			dfs(idx + 1, cnt + 1, n);
			horizon[i][j] = 0;
		}
	}
	else if (j == N - 1)//제일 오른쪽줄이면 왼쪽만 체크
	{
		if (horizon[i][j - 1] == 0)
		{
			horizon[i][j] = 1;
			dfs(idx + 1, cnt + 1, n);
			horizon[i][j] = 0;
		}
	}
	else
	{
		if (horizon[i][j + 1] == 0 && horizon[i][j - 1] == 0)//아니면 양쪽 다 체크
		{
			horizon[i][j] = 1;
			dfs(idx + 1, cnt + 1, n);
			horizon[i][j] = 0;
		}
	}

	//가로줄 추가하지 않고 다음 idx
	dfs(idx + 1, cnt, n);
}