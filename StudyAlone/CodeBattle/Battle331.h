//5515. 2016년 요일 맞추기

#pragma once
#include<iostream>
using namespace std;

int day[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int Battle331() {
	int t;
	scanf("%d\n", &t);
	for (int i = 0; i < 13; i++) {
		day[i + 1] = day[i] + day[i + 1];
	}
	for (int tc = 1; tc <= t; tc++) {
		int m, d;
		scanf("%d %d", &m, &d);

		d--;
		m--;
		
		int dn = day[m] + d;
		printf("#%d %d\n", tc, ((dn % 7) + 4) % 7);
	}
	return 0;
}