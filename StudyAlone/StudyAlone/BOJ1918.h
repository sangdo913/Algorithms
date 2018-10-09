//https://www.acmicpc.net/problem/1918
//BOJ 1918 후위표기식
#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<stack>

using namespace std;

stack<char> st;

int len(char* str) {
	int res = 0;
	while (*str) {
		res++;
		str++;
	}
	return res;
}


int BOJ1918() {
	string st;
	stack<char> op;
	int conv[256];
	conv['+'] = conv['-'] = 1;
	conv['*'] = conv['/'] = 2;
	conv['('] = 0;

	char str[100000];
	cin >> str;

	int l = len(str);
	for (int i = 0; i < l; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			st.push_back(str[i]);
		}
		else if(str[i] == '('){
			op.push(str[i]);
		}
		else if (str[i] == ')') {
			while (op.top() != '(') {
				st.push_back(op.top());
				op.pop();
			}
			op.pop();
		}
		else {
			while (op.size() && conv[op.top()] >= conv[str[i]]) {
				st.push_back(op.top());
				op.pop();
			}
			op.push(str[i]);
		}
		
	}
	while (op.size()) {
		st.push_back(op.top());
		op.pop();
	}

	cout << st;
	return 0;
}
