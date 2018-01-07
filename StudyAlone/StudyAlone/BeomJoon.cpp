#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<map>
using namespace std;

static const int A = 1;
static const int P = 0;
static const int H = 2;
static const int PT = 3;
static const int PG = 4;
static const int I = 5;

static int Size;
static int edges[35][35];
static int info[6][35];
static int max_value;
static vector<int> max_path;
static int  min_hotel[35];


void dfs2(vector<bool> &check, const int &to, int reserved, const int &days, int count, vector<int> &path, int pg)
{
	for (int i = 0; i < Size; i++)
	{
		if (i == 0 && count != days) continue; //돌아가는 날이 아닌데 공항
		if (reserved + info[PT][i] + edges[to][i] > 540) continue; // 길이 540 이상
		if (check[i])
		{
			continue;// 이미 방문
		}

		// 마지막날
		if (info[I][i] == A)
		{
			path.push_back(i + 1);
			if (max_value < pg)
			{
				max_value = pg;
				max_path.clear();
				max_path.insert(max_path.begin(), path.begin(), path.end());
			}
		}

		else if (info[I][i] == H)
		{
			if (days == count || to == i)
			{
				continue;
			}

			path.push_back(i + 1);
			dfs2(check, i, 0, days, count + 1, path, pg);
		}

		else
		{
			if (count != days && reserved + info[PT][i] + edges[to][i] + min_hotel[i] > 540)
			{
				continue;
			}
			if (count == days && reserved + info[PT][i] + edges[to][i] + edges[i][0] > 540) {
				continue;
			}
			check[i] = true;

			path.push_back(i + 1);
			dfs2(check, i, reserved + info[PT][i] + edges[to][i], days, count, path, pg + info[PG][i]);
			check[i] = false;
		}

		if (path.begin() != path.end()) path.erase(path.begin() + path.size() - 1);
	}
}

int main()
{
	int N, M, K;
	ios::ios_base::sync_with_stdio(false);
	cin >> K;

	for (int k = 1; k <= K; k++)
	{
		cin >> N >> M;
		Size = N;

		max_path.clear();

		int hotel_size = 0;
		int hotel_index = 0;
		max_value = 0;
		int temp, temp2;
		char temp3;
		//input
		for (int i = 0; i < N; i++)
		{
			for (int j = i + 1; j < N; j++)
			{
				cin >> temp;
				edges[i][j] = temp;
				edges[j][i] = temp;
			}
		}

		for (int i = 0; i < N; i++)
		{
			cin >> temp3;
			switch (temp3)
			{
			case 'A':
				info[PT][i] = 0;
				info[PG][i] = 0;
				info[I][i] = A;
				break;
			case 'P':
				cin >> temp >> temp2;

				info[PT][i] = temp;
				info[PG][i] = temp2;
				info[I][i] = P;
				break;
			case 'H':
				info[I][i] = H;
				info[PG][i] = 0;
				info[PT][i] = 0;
				info[H][hotel_index++] = i;

				break;
			}
		}

		for (int i = 0; i < N; i++)
		{
			min_hotel[i] = 50000;
			for (int j = 0; j < hotel_index; j++)
			{
				min_hotel[i] = min_hotel[i] > edges[i][info[H][j]] ? edges[i][info[H][j]] : min_hotel[i];
			}
		}

		vector<bool> ch(N, false);

		vector<int> path;

		dfs2(ch, 0, 0, M, 1, path, 0);

		cout << "#" << k << " " << max_value;
		for (int i = 0; i < max_path.size(); i++)
		{
			cout << " " << max_path[i];
		}

		cout << endl;
	}

	return 0;
}