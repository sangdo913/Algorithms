//Poker
#pragma once
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;

int nums[15];
int card[256][20];
char group[5] = "SDCH";
int gcnt[256];
int conv[20];


const char res[9][30] = { "Top", "1 Pair", "2 Pair", "Triple", "Straight", "Flush", "Full House", "4 Card", "Straight Flush" };
int check() {
	int res = 0;
	int pair = 0;
	int prev, cnt, scnt = 0;
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
	int cards[14];

	int ccnt = 0;

	bool royal = false;
	for (int i = 0; i < 4; i++) {
		ccnt = 0;
		same |= card[group[i]][0] >= 5;

		for (int j = 1; j <= gcnt[group[i]]; j++) {
			cards[ccnt++] = card[group[i]][j];
		}

		if (same) {
			sort(cards, cards + ccnt);
			int cnt2 = 1;
			int p = cards[0];
			for (int i = 1; i < ccnt; i++) {
				if (++p == cards[i]) {
					cnt2++;
					if (cnt2 == 5) {
						royal = true;
						break;
					}
				}
				else {
					cnt2 = 1;
					p = cards[i];
				}
			}
		}

	}



	if (royal && same) res = 8;
	else if (cnt >= 4) res = 7;
	else if (pair >= 2 && cnt >= 3) res = 6;
	else if (same) res = 5;
	else if (serial) res =  4;
	else if (cnt >= 3) res = 3;
	else if (pair >= 2) res = 2;
	else if (pair >= 1) res = 1;

	return res;
}
int SWEA3996() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	conv[1] = 14;
	int t;
	cin >> t;

	
	for (int tc = 1; tc <= t; tc++) {
		memset(nums, 0, sizeof(nums));
		memset(card, 0, sizeof(card));
		memset(gcnt, 0, sizeof(gcnt));

		char c; int i;

		for (int j = 0; j < 7; j++) {
			cin >> c >> i;

			card[c][0]++;
			card[c][++gcnt[c]] = i;
			if (i == 1) card[c][++gcnt[c]] = 14;
			nums[i]++;
			nums[conv[i]]++;
		}

		cout << '#' << tc << ' ' << res[check()] << '\n';
	}
	return 0;
}
