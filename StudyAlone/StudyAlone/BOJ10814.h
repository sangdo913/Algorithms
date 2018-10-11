//https://www.acmicpc.net/problem/10814
//BOJ 10814 나이순 정렬
#pragma once
#include<iostream>

using namespace std;

struct NODE {
	int age;
	char name[101];
}nodes[100000]; 

int indexes[100000], temp[100000];

bool comp(int i1, int i2) {
	if (nodes[i1].age == nodes[i2].age) {
		return i1 < i2;
	}
	return nodes[i1].age < nodes[i2].age;
}

void merge(int s, int e) {
	if (s < e) {
		int m = (s + e) / 2;
		int l = s, r = m + 1, k = l;

		merge(l, m);
		merge(r, e);

		while (l <= m && r <= e) {
			temp[k++] = comp(indexes[l], indexes[r]) ? indexes[l++] : indexes[r++];
		}
		while (l <= m) temp[k++] = indexes[l++];
		while (r <= e) temp[k++] = indexes[r++];

		for (int i = s; i <= e; i++) {
			indexes[i] = temp[i];
		}
	}
}

int BOJ10814() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> nodes[i].age;
		cin >> nodes[i].name;
		indexes[i] = i;
	}

	merge(0, n - 1);
	for (int i = 0; i < n; i++) {
		cout << nodes[indexes[i]].age << ' ' << nodes[indexes[i]].name << '\n';
	}
	return 0;
}