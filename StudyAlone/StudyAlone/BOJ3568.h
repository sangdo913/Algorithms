//https://www.acmicpc.net/problem/3568
//BOJ 3568 iSharp
#pragma once
#include<iostream>
#include<sstream>
#include <string>
#include<vector>
#include<stack>

using namespace std;

bool isalpha(char s) {
	return (s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z');
}

int BOJ3568() {
	string s;
	getline(cin, s);
	
	stringstream ss(s);
	int i = 0;
	vector<string> input;
	
	while (ss >> s) {
		input.push_back(s);
	}

	for (int i = 1; i < input.size(); i++) {
		string type;
		string name;

		input[i].pop_back();
		int idx = 0;
		while (idx != input[i].size() && isalpha(input[i][idx])) idx++;

		name = string(input[i].begin(), input[i].begin() + idx);
		type = string(input[i].begin() + idx, input[i].end());
		type = string(type.rbegin(), type.rend());
		for (int i = 0; i < type.size(); i++) {
			if (type[i] == '[') type[i] = ']';
			else if (type[i] == ']') type[i] = '[';
		}
		
		string res = input[0] + type +' ' + name+';';
		cout << res << '\n';
	}
		
	return 0;
}
