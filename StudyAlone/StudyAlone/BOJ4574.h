#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_set>
#include<tuple>

using namespace std;
typedef enum INFO{R=0, C = 1, S = 2};

int arr[10][10];

bool check[3][9][10];
int conv[256];
unordered_set<pair<int, int> > se;

tuple<int, int, int> getNum(int r, int c) {
	return make_tuple{r, c, 3 * ((r - 1) / 3) + (c - 1) / 3};
}


int BOJ4574() {
	int num;
	for (int i = 'A'; i <= 'Z'; i++) {
		conv[i] = i - 'A'+1;
	}

	while (true) {
		cin >> num;
		if (num == 0) break;

		while (num--) {
			pair<int, int> block;
			char pos[3];
			int n;
			int nr, nc, ns;
			cin >> n >> pos;
			pos[0] = conv[pos[0]];
			pos[1] -= '0';
			block.first = n;
			tie(nr,nc,ns) = getNum(pos[0], pos[1]);

			arr[pos[0]][pos[1]] = n;

			cin >> n >> pos;
			pos[0] = conv[pos[0]];
			pos[1] -= '0';
			block.first = n;

			tie(nr,nc,ns) = getNum(pos[0], pos[1]);

			arr[pos[0]][pos[1]] = n;
			
			if (block.first < block.second) {
				int temp = block.first;
				block.first = block.second;
				block.second = temp;
			}
			se.insert(block);
		}

		for (int i = 1; i <= 9; i++) {

		}
		break;
	}

	return 0;
}
