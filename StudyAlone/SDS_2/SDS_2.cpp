//////////////////////////////////////////////////////////////////////////
// main 함수는 수정 및 접근이 불가능 합니다.

#include <iostream>
#include <cstdlib>
#include <cstdio>

#define MAX 4096
using namespace std;
static unsigned char ori_pattern[MAX][32][32];
int dummy1[MAX];
unsigned char pattern[MAX][32][32];
int dummy2[MAX];
unsigned char input[64][64];
int dummy3[MAX];
extern void init(unsigned char pattern[][32][32]);
extern int solve(unsigned char pattern[][32][32], unsigned char picture[][64]);
int main() {
	int seed;
	cin >> seed;
	srand(seed);
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < 32; j++) {
			for (int k = 0; k < 32; k++) {
				ori_pattern[i][j][k] = rand() % 256;
			}
		}
	}
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < 32; j++) {
			for (int k = 0; k < 32; k++) {
				pattern[i][j][k] = ori_pattern[i][j][k];
			}
		}
	}

	int problemNum = 4096;
	int correct = 0;
	int score = 0;

	init(pattern);

	for (int TestCase = 1; TestCase <= problemNum; TestCase++) {
		int curIdx = rand() % MAX;
		for (int i = 0; i < 64; i++) {
			for (int j = 0; j < 64; j++) {
				input[i][j] = rand() % 256;
			}
		}

		int sr = rand() % 33;
		int sc = rand() % 33;

		for (int i = 0; i < 32; i++) {
			for (int j = 0; j < 32; j++) {
				input[sr + i][sc + j] = ori_pattern[curIdx][i][j];
			}
		}
		int result = solve(pattern, input);
		if (result == curIdx) score += 1;
	}

	cout << "score : " << score;
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

// user 영역은 수정 및 접근이 가능합니다.
// user 영역에서 init 함수 및 solve 함수를 구현하여 score 값을 최대화 하시오.
#define MAX 4096

#include<unordered_map>
#include<cstring>

unordered_multimap<int, unsigned int> mp;
unsigned char store[MAX][32][32];
unsigned char store_picture[64][64];

extern void init(unsigned char pattern[][32][32]) {
	mp.clear();
	memcpy(store, pattern, sizeof(store));

	for (int i = 0; i < MAX; i++) {
		unsigned int key = 0;
		for (int j = 0; j < 4; j++) {
			key <<= 8;
			key += pattern[i][0][j];
		}
		mp.insert({ key, i });
	}
}

int find(unordered_multimap<int, unsigned int>::iterator it1, unordered_multimap<int, unsigned int>::iterator it2, int sr, int sc) {
	while (it1 != it2) {
		bool find = true;
		int index = it1->second;
		for (int i = 0; i < 32; i++) {
			for (int j = 0; j < 32; j++) {
				if (store[index][i][j] != store_picture[sr + i][sc + j]) {
					find = false; break;
				}
			}
			if (!find) break;
		}
		if (find) return index;
		it1++;
	}

	return -1;
};

int solve(unsigned char pattern[][32][32], unsigned char picture[][64]) {
	memcpy(store_picture, picture, sizeof(store_picture));

	for (int i = 0; i < 33; i++) {
		unsigned int key = 0;

		for (int j = 0; j < 4; j++) {
			key <<= 8;
			key += picture[i][j];
		}
		int j = 0;

		auto range = mp.equal_range(key);
		int res = find(range.first, range.second, i, j);
		if (res != -1) return res;

		while (j <32) {
			key <<= 8;
			key += picture[i][j + 4];
			j++;

			auto rg = mp.equal_range(key);
			res = find(rg.first, rg.second, i, j);
			if (res != -1) return res;
		}
	}

	return -1;
}