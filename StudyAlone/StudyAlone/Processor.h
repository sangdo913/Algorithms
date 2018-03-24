#include<iostream>
#include<vector>

using namespace std;

bool Is_Wall(int x, int y, int size)
{
	return x < 0 || x >= size || y < 0 || y >= size;
}

void Delete_Line(vector<vector<int> > &map, int x, int y, int direct)
{
	int size = map.size();
	int dx[4] = { 0,0,-1,1 };
	int dy[4] = { 1,-1,0,0 };

	while (!Is_Wall(x + dx[direct], y + dy[direct], size))
	{
		x = x + dx[direct]; y = y + dy[direct];
		map[y][x] = 0;
	}
}
int Make_Line(vector<vector<int> > &map, int x, int y, int direct)
{
	if (direct == 4) return 0;
	int size = map.size();
	int dx[4] = { 0,0,-1,1 };
	int dy[4] = { 1,-1,0,0 };
	int tx = x;
	int ty = y;
	bool is_blocked = false;
	int result = 0;
	while (!Is_Wall(tx + dx[direct], ty + dy[direct], size))
	{
		tx = tx + dx[direct]; ty = ty + dy[direct];
		if (is_blocked = (map[ty][tx] != 0)) break;
		map[ty][tx] = 2;
		result++;
	}

	if (is_blocked)
	{
		direct ^= 1;
		while (!Is_Wall(tx + dx[direct], ty + dy[direct], size))
		{
			tx += dx[direct]; ty += dy[direct];
			if (tx == x && ty == y) break;
			else
			{
				map[ty][tx] = 0;
			}
		}
		result = 0;
	}
	return result;
}
const int PROCESSOR_MAX = 144;
int max_pro = 0;
int min_line = 0;

int dfs(vector<vector<int> > &map, int x, int y, int node_num, int count, int count_pro, int linked)
{
	if (count == node_num) return linked;

	int size = map.size();
	int ret = PROCESSOR_MAX;

	bool isConstruct = false, is_find = false;
	int tx = x; int ty = y;
	for (int i = ty; i<size - 1; i++)
	{
		if (is_find) break;
		for (int j = i == ty ? x + 1 : 1; j<size - 1; j++)
		{
			if (Is_Wall(i, j, size)) continue;

			if (map[i][j] == 1)
			{
				tx = j;
				ty = i;
				is_find = true;
				break;
			}
		}
	}

	is_find = false;

	for (int d = 0; d < 5; d++)
	{
		int line = Make_Line(map, x, y, d);
		int next_pro;
		isConstruct = line > 0;
		is_find |= !isConstruct;

		if (!isConstruct && d != 4) continue;
		else if (d == 4 && !is_find) break;

		next_pro = isConstruct ? count_pro + 1 : count_pro;

		int store = dfs(map, tx, ty, node_num, count + 1, next_pro, line + linked);

		if (next_pro > max_pro)
		{
			max_pro = next_pro;
			min_line = store;
		}

		else if (next_pro == max_pro)
		{
			min_line = min_line > store ? store : min_line;
		}

		if (isConstruct)
		{
			Delete_Line(map, x, y, d);
		}
	}
	return ret;
}

void Processor()
{
	vector<vector<int> > map;

	int N, T, result;
	cin >> T;
	for (int k = 1; k <= T; k++)
	{
		max_pro = 0;
		int line = 0;
		cin >> N;
		result = 0;

		map.resize(N);
		for (int i = 0; i < N; i++)
		{
			map[i].resize(N);
		}

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cin >> map[i][j];
				if (map[i][j] == 1 && i> 0 && i<N - 1 && j > 0 && j< N - 1) line++;
			}
		}
		int size = map.size();

		bool is_find = false;
		for (int i = 1; i < size - 1 && !is_find; i++)
			for (int j = 1; j < size - 1; j++)
			{
				if (map[i][j] != 0)
				{
					result = dfs(map, j, i, line, 0, 0, 0);
					is_find = true;
					break;
				}
			}

		cout << "#" << k << " " << min_line << endl;

		for (int i = 0; i < N; i++)
		{
			map[i].clear();
		}

		map.clear();
	}
}