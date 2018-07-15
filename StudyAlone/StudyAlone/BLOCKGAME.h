#pragma once
#include<cstdio>
#include<cstring>

char cache[1 << 25];
int conv[256];
char map[6][6] = { 0 };
const char *win[2] = { "LOSING", "WINNING" };

// 블럭들
const char block[6][2][2]{

		{
			{1,1},
			{1,0}
		},
		{
			{1,1},
			{0,1}
		},
		{

			{0,1},
			{1,1}
		},
		{
			{1,0},
			{1,1}
		},
		{
			{1,1},
			{0,0}
		},
		{
			{1,0},
			{1,0}
		}
};

int ptb(int r, int c) {
	return 1 << (5 * r + c);
}

bool canWin(int state) {

	char &ret = cache[state];
	if (ret != -1) return ret;

	ret = 0;

	//맵 체크
	for (int r = 0; r < 5; r++) {
		for (int c = 0; c < 5; c++) {
			//블럭 6개 체크
			for (int i = 0; i < 6; i++) {
				bool canBuild = true;

				//벽 놓을 수 있는지 체크
				for (int k = 0; k < 2 && canBuild; k++) {
					for (int l = 0; l < 2; l++) {
						if (map[r + k][c + l] == '#' && block[i][k][l]) {
							canBuild = false;
							break;
						}
					}
				}

				//놓을 수 있으면 벽 놓기
				if (canBuild) {
					int ns = state;
					for (int k = 0; k < 2 && canBuild; k++) {
						for (int l = 0; l < 2; l++) {
							if (block[i][k][l]) {
								map[r + k][c + l] = '#';
								ns |= ptb(r + k, c + l);
							}
						}
					}

					ret = !canWin(ns);

					//다시 블럭 제거
					for (int k = 0; k < 2 && canBuild; k++) {
						for (int l = 0; l < 2; l++) {
							if (block[i][k][l]) {
								map[r + k][c + l] = '.';
							}
						}
					}
					//이길 수 있는 경우가 나오면 바로 return
					if (ret) return ret;
				}
			}
		}
	}

	return ret;
}

int BLOCKGAME() {
	conv['.'] = 0;
	conv['#'] = 1;
	int t;
	scanf("%d\n", &t);

	memset(cache, -1, sizeof(cache));

	while (t--) {
		int state = 0;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				scanf(" \n%c", &map[i][j]);
				if (map[i][j] == '#') state |= ptb(i, j);
			}

			map[i][5] = '#';
			map[5][i] = '#';
		}
		map[5][5] = '#';
		printf("%s\n", win[canWin(state)]);
	}
	return 0;
}