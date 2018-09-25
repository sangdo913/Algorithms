#pragma once
#include<iostream>
#include<cstring>

using namespace std;

int nums[2][26];

char s[100001];
char s2[100001];
int len[2];

bool isSame() {
	for (int i = 0; i < 26; i++) {
		if (nums[0][i] != nums[1][i]) return false;
	}

	return true;
}
int SWEA3816() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t;

	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		memset(nums, 0, sizeof(nums));
		cin >> s2 >> s;
		len[0] = strlen(s);
		len[1] = strlen(s2);

		for (int i = 0; i < len[1]; i++) nums[0][s[i] - 'a']++;
		for (int i = 0; i < len[1]; i++) nums[1][s2[i] - 'a']++;
		
		int cnt = isSame();

		for (int i = len[1]; i < len[0]; i++) {
			nums[0][s[i - len[1]] - 'a']--;
			nums[0][s[i] - 'a']++;
			cnt += isSame();
		}
		cout << '#' << tc << ' ' <<  cnt << '\n';
	}

	return 0;
}