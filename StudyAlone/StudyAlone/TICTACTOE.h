#pragma once
#include<cstdio>
#include<cstring>

char memoi[20000];
char map[3][4];
int conv[256], loser[256];

bool win() {
	bool res = false;
	for (int i = 0; i < 3; i++) {
		res |= map[i][0] != '.' && map[i][0] == map[i][1] && map[i][1] == map[i][2];
	}
	for (int j = 0; j < 3; j++) {
		res |= map[0][j] != '.' && map[0][j] == map[1][j] && map[0][j] == map[2][j];
	}

	res |= map[1][1] != '.' && map[0][0] == map[1][1] && map[0][0] == map[2][2];
	res |= map[1][1] != '.' && map[2][0] == map[1][1] && map[2][0] == map[0][2];

	return res;
}

int getState() {
	int state = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			state *= 3;
			state += conv[map[i][j]];
		}
	}
	return state;
}

char winner(int depth, char turn) {

	char &ret = memoi[getState()];
	if (ret != -1) return ret;

	if (win()) {
		return ret = loser[turn];
	}

	if (depth == 9) return ret = 0;

	ret = loser[turn];

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (map[i][j] == '.') {
				map[i][j] = turn;
				char w = winner(depth + 1, loser[turn]);
				map[i][j] = '.';

				if (w == turn) {
					ret = turn;
					return ret;
				}

				else if (w == 0) {
					ret = 0;
				}
			}
		}
	}

	return ret;
}

int Do() {
	int t;
	scanf("%d\n", &t);
	
	memset(memoi, -1, sizeof(memoi));
	conv['.'] = 0;
	conv['o'] = 1;
	conv['x'] = 2;

	loser['o'] = 'x';
	loser['x'] = 'o';
	int depth = 0;

	for (int tc = 1; tc <= t; tc++) {
		for (int i = 0; i < 3; i++) {
			scanf("%s\n", map[i]);
		}

		for(int i = 0; i < 3; ++i){
			for(int j = 0; j <3; ++j){
				depth += map[i][j] != '.';
			}
		}

		int cnt = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cnt += map[i][j] == '.';
			}
		}
		char res = winner(depth, cnt & 1 ? 'x' : 'o');
		if (res == 0) printf("TIE\n");
		else {
			printf("%c\n", res);
		}
	}

	return 0;
}