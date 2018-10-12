//https://www.acmicpc.net/problem/11279
//BOJ 11279 ÃÖ´ë Èü
#pragma once
//https://www.acmicpc.net/problem/11279
//BOJ11279 ÃÖ´ë Èü
#include<iostream>

using namespace std;

struct HEAP{
	int arr[100001];
	int size;
	HEAP() :size(0) {}
	bool (*comp) (int i1, int i2);

	int getchild(int idx) {
		int l = idx << 1, r = (idx << 1) + 1;
		
		if (l > size && r > size) return 0;
		else if (l > size) return r;
		else if (r > size) return l;
		else {
			return comp(arr[l], arr[r]) ? l : r;
		}
	}

	int getparent(int idx) { return idx >> 1; }

	void insert(int num) {
		size++;
		int i = size, p = getparent(i);
		
		while (p&&comp(num, arr[p])) {
			arr[i] = arr[p];
			i = p;
			p = getparent(i);
		}
		arr[i] = num;
	}

	int pop() {
		if (size == 0) return 0;
		int res = arr[1], data = arr[size--];

		int i = 1, c = getchild(i);

		while (c && comp(arr[c], data)) {
			arr[i] = arr[c];
			i = c;
			c = getchild(i);
		}
		arr[i] = data;

		return res;
	}
}heap;

bool comp(int i1, int i2) { return i1 > i2; }
int BOJ11279() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int n;

	heap.comp = comp;

	cin >> n;

	while (n--) {
		int num;

		cin >> num;

		if (num) { heap.insert(num); }
		else { cout << heap.pop() << '\n'; }
	}

	return 0;
}
