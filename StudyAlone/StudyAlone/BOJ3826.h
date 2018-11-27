#pragma once
#include<iostream>
#include<string>
#include<stack>

using namespace std;

stack<char> st;
int nowIndent;
int conv[256];

int abs(int i) { return i < 0 ? -i : i; }
int BOJ3826() {
	int n, m;
	for (int i = 0; i < 256; i++) conv[i] = 6;
	conv['('] = 0;
	conv['{'] = 1;
	conv['['] = 2;
	conv[')'] = 3;
	conv['}'] = 4;
	conv[']'] = 5;

	string line;
	while (true) {
		cin >> n >> m;
		if (n == 0 && m == 0) return 0;
		int nums[4] = { -1,-1,-1 };

		int prevnum = 0;
		int now = -1;
		int cnt = 0;

		for (int i = 0; i < n; i++) {
			cin >> line;
			int l = 0;
			int indent = 0;

			if (now != -1 && nums[st.top()] < 0) {
				while (line[l] == '.') l++, indent++;

				nums[st.top()] = indent - prevnum;
			}

			prevnum = indent;
			
			for (; l < line.size(); l++) {
				if (line[l] == '(' || line[l] == '{' || line[l] == '[') {
					if (now == -1) {
						now = conv[line[l]];
						cnt = 0;
					}

					st.push(conv[line[l]]);
					cnt++;
				}
				else if (line[l] == ')' || line[l] == '}' || line[l] == ']') {
					st.pop();
					cnt--;
					if(cnt ==0) now = 
				}
			}
		}

		cout << "0 ";

		int cnt[8] = { 0,0,0 };
		for (int i = 1; i < m; i++) {
			cin >> line;
			bool can = true;

			if (st.size() && nums[st.size()] == -1) {
				can = false;
			}

			for (int l = 0; l < line.size(); l++) {
				cnt[conv[line[l]]]++;
				if (line[l] == '(' || line[l] == '{' || line[l] == '[') st.push(conv[line[l]]);
				else if (line[l] == ')' || line[l] == '}' || line[l] == ']') st.pop();
			}

			int res[3] = {};
			for (int i = 0; i < 3; i++) {
				res[i] = abs(nums[i]) * (cnt[i] - cnt[i + 3]);
			}


			if(can) {
				cout << res[0] + res[1] + res[2] << ' ';
			}

			else {
				cout << -1 << ' ';
			}
		}
		cin >> line;
		cout << '\n';
	}
	return 0;
}
