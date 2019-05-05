#pragma once
#include<iostream>
#include<string>

using namespace std;

int Do() {
	int tc;

	cin >> tc;

	for (int t = 1; t <= tc; t++) {
		string in;
		cin >> in;
		int cnt = 0;

		while (in.size() != 1) {
			int a = in[in.size() - 1]-'0';
			int b = in[in.size() - 2]-'0';
			char ne[3];
			if (a + b < 10) {
				ne[0] = a + b + '0';
				ne[1] = 0;
			}
			else {
				ne[0] = (a + b) / 10 + '0', ne[1] = (a + b) % 10 + '0', ne[2] = 0;
			}

			in.pop_back();
			in.pop_back();
			in += string(ne);
			cnt++;
		}
		cout << '#' << t << ' ' << (cnt & 1 ? 'A' : 'B') << '\n';
	}
	return 0;
}
