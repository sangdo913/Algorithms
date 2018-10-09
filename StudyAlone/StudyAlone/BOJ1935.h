//https://www.acmicpc.net/problem/1935
//BOJ1935 후위표기식2
#pragma once

#include<iostream>
#include<stack>
#include<string>

using namespace std;

double cal(double a, double b, char op) {
	switch (op) {
	case '*':
		return a * b;
	case'/':
		return a / b;
	case'+':
		return a + b;
	case'-':
		return a - b;
	}
	return 0;
}
int len(char*str) {
	int res = 0;
	while (*str) {
		res++;
		str++;
	}
	return res;
}

int BOJ1935() {
	double operands[256];
	int top = 0;
	
	int l, n;
	cin >> n;
	char nums[100];
	
	cin >> nums;

	l = len(nums);

	double conv[256];

	for (int i = 0; i < n; i++) {
		cin >> conv['A' + i];
	}
	for (int i = 0; i < l; i++) {
		if (nums[i] >= 'A' && nums[i] <= 'Z') {
			operands[top++] = conv[nums[i]];
		}
		else {
			double num2 = operands[--top];
			double num1 = operands[--top];
			operands[top++] = cal(num1, num2, nums[i]);
		}
	}

	cout.setf(ios::fixed);
	cout.precision(2);

	cout << operands[--top];
	return 0;
}
