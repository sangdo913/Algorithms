#pragma once
#include<iostream>
#include<vector>

struct INFO {
	int p[4];
};
using namespace std;

int BOJ15660() {
	
	INFO in1, in2;
	for (int i = 0; i < 4; i++) {
		in1.p[i] = i;
	}

	in2 = in1;

	for (int i = 0; i < 4; i++) {
		cout << in2.p[i] << ' ';
	}
	cout << endl;
	return 0;
}