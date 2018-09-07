#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
int T, D, W, K;
int ans;
int map[13][20];
int original[13][20];
bool check[13];
int cnt;
bool isCheck(int x)
{
	int acnt = 0, bcnt = 0;
	bool flag = false;
	for (int i = 0; i <= D - K; i++)
	{
		if (map[i][x] == map[i + 1][x])
		{
			for (int m = i; m < i + K; m++)
			{
				if (map[i][x] == map[m][x])
				{
					acnt++;
				}
			}
		}
		if (acnt >= K) return true;
		else  acnt = 0;
	}
	return false;
}
void Swap(int row, int num)
{
	if (num == -1 || row<0) return;
	for (int i = 0; i < W; i++)
		map[row][i] = num;
}
void recur(int row)
{
	for (int i = 0; i < W; i++)
		map[row][i] = original[row][i];
}
bool totalCheck()
{
	bool flag = false;
	for (int i = 0; i < W; i++)
	{
		flag = isCheck(i);
		if (flag == false) break;
	}
	return flag;
}
void dfs(int idx, int cnt, int num)
{

	if (idx > D) return;
	if (cnt > ans) return;
	if (totalCheck())
	{
		ans = min(ans, cnt);
		return;
	}
	for (int i = -1; i <= 1; i++)
	{
		cnt = (i == -1) ? cnt : cnt + 1;
		if (idx >= 0) Swap(idx, num);
		dfs(idx + 1, cnt, i);
		if (idx >= 0)recur(idx);
	}

}
int main()
{
	vector<int> vec;
	
	freopen("input.txt", "r", stdin);
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> D >> W >> K;
		int tmp = 0;
		for (int i = 0; i < D; i++)
		{
			for (int j = 0; j < W; j++)
			{
				cin >> tmp;
				map[i][j] = tmp;
				original[i][j] = tmp;
			}
		}
		ans = K;
			dfs(-1, 0, 0);
		cout << "#" << tc << " " << ans << "\n";
	}
}