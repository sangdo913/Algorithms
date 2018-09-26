//Poker
#pragma once
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;

int nums[15];
int card[256][15];
char group[5] = "SDCH";

const char res[9][30] = { "Top", "1 Pair", "2 Pair", "Triple", "Straight", "Flush", "Full House", "4 Card", "Straight Flush" };

int check() {
	int res = 0;
	int pair = 0;
	int cnt, scnt = 0;
	bool same = false;
	bool serial = false;

	cnt = 0;

	for (int i = 1; i <= 14; i++) {

		if (nums[i]) {
			scnt++;
			if (scnt == 5) serial = true;
		}
		else {
			scnt = 0;
		}

		cnt = cnt < nums[i] ? nums[i] : cnt;
		if (nums[i] > 1) pair++;
	}

	bool royal = false;

	for (int i = 0; i < 4; i++) {
		same |= card[group[i]][0] >= 5;

		if (card[group[i]][0] >= 5) {
			int cnt2 = 0;

			for (int j = 1; j <= 14; j++) {
				if (card[group[i]][j]) {
					cnt2++;
					if (cnt2 == 5) {
						royal = true;
						break;
					}
				}

				else {
					cnt2 = 0;
				}
			}
		}
	}

	if (royal) res = 8;
	else if (cnt >= 4) res = 7;
	else if (pair >= 2 && cnt >= 3) res = 6;
	else if (same) res = 5;
	else if (serial) res = 4;
	else if (cnt >= 3) res = 3;
	else if (pair >= 2) res = 2;
	else if (pair >= 1) res = 1;

	return res;
}

#include<stdlib.h>
#include<math.h>
#include<time.h>

int main() {
	int t;
	cin >> t;
	srand(time(0));

	for (int tc = 1; tc <= 10; tc++) {
		memset(nums, 0, sizeof(nums));
		memset(card, 0, sizeof(card));

		char c; int i;

		for (int j = 0; j < 7; j++) {
			//cin >> c >> i;
			c = rand() % 4;
			i = rand() % 13 + 1;
			cout << j  << "th card : " << group[c] << ' ' << i << endl;
			card[group[c]][0]++;
			card[group[c]][i] = 1;

			if (i == 1) {
				nums[14]++;
				card[group[c]][14] = 1;
			}

			nums[i]++;
		}

		cout << '#' << tc << ' ' << res[check()] << '\n';
	}
	return 0;
}
