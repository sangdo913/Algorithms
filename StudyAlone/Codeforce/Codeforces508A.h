#pragma once
#include<iostream>
#include<queue>

using namespace std;
char str[100001];
int n,k;
int nums[26];
int Codeforce508A() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> k;
	cin >> str;

	for (int i = 0; i < n; i++) {
		nums[str[i]-'A']++;
	}
	priority_queue<int> que;
	for (int i = 0; i < 26; i++) {
		que.push(nums[i]);
	}
	int t;
	if (que.size() < k) {
		printf("0\n"); return 0;
	}

	for (int i = 0; i < k; i++) {
		t = que.top();
		que.pop();
	}
	printf("%d\n", t*k);
	return 0;
}