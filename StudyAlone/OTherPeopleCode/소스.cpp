#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <cstring>
#define P pair<int, int>
using namespace std;

int N, M, H;
int anw = -1;
int horizon[32][12]; //[i][j] : j��° �����ٰ� j+1��° ������ ���̿� �ִ� i��° ������ ����(������ 0 ������ 1)
int cantline[32][12]; // �������� ���� �� ���� ���� ��ǥ(������ �������� �ְų�, ���ʰ� �����ʿ� ������ �ȵȴ�.)
vector <P> v;//�������� ���� �� �ִ� ���� ��ǥ��

void check_cantline(int x, int y); //�������� ���� �� ���� ���� üũ
void check_vertical();//�������� ���� �� �ִ°��� ��ǥ���� v�� ����
bool check_answer();//i��° ���� i��°�� ���������� üũ(������ 1, Ʋ���� 0)
void dfs(int idx, int cnt, int n);//�������� n�� �߰��� �����ؼ� ���� üũ




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

	//�������� ���� �� �ִ� ���� ��ǥ�� vector�� ����
	check_vertical();
	anw = check_answer() ? 0 : -1;

	//�������� ���� �� �ִ� ���� �������� Ž��
	if (v.size() != 0)
	{
		//�������� 0������ 3������ ���� ���� Ž�� ����
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
	//���� üũ
	if (y - 1 > 0) cantline[x][y - 1] = 1;
	//���� üũ
	cantline[x][y] = 1;
	//������ üũ
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

void change(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

bool check_answer()//i��° ���� i��°�� ���������� üũ(������ 1, Ʋ���� 0)
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

	//������ �߰��ϰ� ���� idx
	if (j == 1)//���� �������̸� �����ʸ� üũ
	{
		if (horizon[i][j + 1] == 0)
		{
			horizon[i][j] = 1;
			dfs(idx + 1, cnt + 1, n);
			horizon[i][j] = 0;
		}
	}
	else if (j == N - 1)//���� ���������̸� ���ʸ� üũ
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
		if (horizon[i][j + 1] == 0 && horizon[i][j - 1] == 0)//�ƴϸ� ���� �� üũ
		{
			horizon[i][j] = 1;
			dfs(idx + 1, cnt + 1, n);
			horizon[i][j] = 0;
		}
	}

	//������ �߰����� �ʰ� ���� idx
	dfs(idx + 1, cnt, n);
}