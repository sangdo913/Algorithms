// https://www.acmicpc.net/problem/12869/
//BOJ 12869 ¹ÂÅ»¸®½ºÅ©
#pragma once
#include<iostream>

using namespace std;

int cache[61][61][61];

int MIN(int i1, int i2) { return i1 < i2 ? i1 : i2; }
void deal(int &i1, int dmg)  { 
	i1 -= dmg;
	i1 = i1 > 0 ? i1 : 0;
}

void set(int hp[3], int h1, int h2, int h3) {
	hp[0] = h1; hp[1] = h2; hp[2] = h3;
}

void ddang(int hp[3], int i1, int i2, int i3) {
	deal(hp[i1], 9);
	deal(hp[i2], 3);
	deal(hp[i3], 1);
}

int attack(int hp1, int hp2, int hp3) {
	if (hp1 <= 0 && hp2 <= 0 && hp3 <= 0) {
		return 0;
	}

	int& res = cache[hp1][hp2][hp3];
	if (res) return res;

	res = 0x3f3f3f3f;

	int next[3];

	if (hp1 > 0) {
		set(next, hp1, hp2, hp3);
		ddang(next, 0, 1, 2);
		res = MIN(res, 1+attack(next[0], next[1], next[2]));

		set(next, hp1, hp2, hp3);
		ddang(next, 0, 2, 1);
		res = MIN(res, 1 + attack(next[0], next[1], next[2]));
	}

	if (hp2 > 0) {
		set(next, hp1, hp2, hp3);
		ddang(next, 1, 0, 2);
		res = MIN(res, 1 + attack(next[0], next[1], next[2]));

		set(next, hp1, hp2, hp3);
		ddang(next, 1, 2, 0);
		res = MIN(res, 1 + attack(next[0], next[1], next[2]));
	}

	if (hp3 > 0) {
		set(next, hp1, hp2, hp3);
		ddang(next, 2, 0, 1);
		res = MIN(res, 1 + attack(next[0], next[1], next[2]));

		set(next, hp1, hp2, hp3);
		ddang(next, 2, 1, 0);
		res = MIN(res, 1 + attack(next[0], next[1], next[2]));
	}

	return res;
}
int BOJ12869() {
	int hp[3] = { 0 };
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> hp[i];

	cout << attack(hp[0], hp[1], hp[2]);

	return 0;
}