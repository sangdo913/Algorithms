#pragma once
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

int memoi[100][100][100], n;
int cel[101][101];
const int MOD = 1000000007;

// 0 : win, 1 : lose
int info[100][2], rating[100], lp[100];

int getNum(int idx, int win, int lose, const int fw) {
	
	if (idx == n) {
		return win == 0 && lose == (n - fw);
	}

	int &ret = memoi[idx][win][lose];
	if (ret != -1) return ret;

	ret = 0;
	if (win && info[idx][0] - (fw - win)) {
		ret += (getNum(idx + 1, win - 1, lose, fw) * (info[idx][0] - (fw - win)));
		ret %= MOD;
	}

	int rl = n - fw - lose;
	if (rl > lp[idx]) return 0;

	int  m = rl > info[idx][1] ? info[idx][1] : rl;

	for (int i = 0; i < m; i++) {
		ret += (getNum(idx + 1, win, lose + 1, fw) * info[idx][1]);
		ret %= MOD;

		ret += (getNum(idx + 1, win, lose, fw) * cel[info[idx][1]][i]);
		ret %= MOD;

	}

	return ret;
}

int ManagerThinking()
{
	int t; 
	scanf("%d\n", &t);
	for (int i = 0; i <= 100; i++) {
		cel[i][0] = cel[i][i] = 1;
	}

	for (int i = 1; i <= 100; i++) {
		for (int j = 1; j < i; j++) {
			cel[i][j] = cel[i - 1][j] + cel[i - 1][j - 1];
			cel[i][j] %= MOD;
		}
	}

	for (int tc = 1; tc <= t; tc++) {

		memset(memoi, -1, sizeof(memoi));

		scanf("%d\n", &n);

		for (int i = 0; i < n; i++) {
			scanf("%d \n", &rating[i]);
		}

		sort(rating, rating + n);

		int temp;
		for (int i = 0; i < n; i++) {
			scanf("%d \n", &temp);
			for (int j = n-1; j >= 0; j--) {
				if (rating[j] < temp) break;
				info[j][0] ++;
			}
		}
		
		lp[n-1] = info[n-1][1] = n - info[n-1][0];
	
		for (int i = n-2; i >= 0 ; i--) {
			lp[i] = n - info[i][0];
			info[i][1] = lp[i] - lp[i + 1];
		}

		int res[101] = { 0 };
		for (int i = 0; i <= n; i++) {
			res[i] = getNum(0, i, 0, i);
		}
	
		printf("#%d ", tc);
		for (int i = 0; i <= n; i++) {
			printf("%d ", res[i]);
		}
		printf("\n");
	}
	return 0;
}