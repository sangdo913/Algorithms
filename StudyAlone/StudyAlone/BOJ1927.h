#pragma once
#include<iostream>

using namespace std;

struct Heap {
	int arr[100001];
	int size = 0;
	
	bool(*comp) (int i1, int i2);
	Heap() :size(0) {}

	int lchild(int idx) { return idx << 1; }
	int rchild(int idx) { return (idx << 1) + 1; }
	int parent(int idx) { return idx >> 1; }

	int getChild(int idx) {
		int l = lchild(idx), r = rchild(idx);

		if (l > size && r > size) {
			return 0;
		}
		else if (l > size) {
			return r;
		}

		else if (r > size) {
			return l;
		}
		else {
			return comp(arr[l], arr[r]) ? l : r;
		}
		return 0;
	}

	void insert(int num) {
		size++;
		
		int i = size, p = parent(i);
		while (p && comp(num, arr[p])) {
			arr[i] = arr[p];
			i = p;
			p = parent(i);
		}
		arr[i] = num;
	}

	int pop() {
		if (size == 0) return 0;

		int res = arr[1], data = arr[size--];

		int c = getChild(1), i = 1;
		while (c&&comp(arr[c],data)) {
			arr[i] = arr[c];
			i = c;
			c = getChild(i);
		}
		arr[i] = data;

		return res;
	}
}heap;

bool comp(int i1, int i2) {
	return i1 < i2;
}

int BOJ1927() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int n;
	cin >> n;

	heap.comp = comp;

	while (n--) {
		int num;
		cin >> num;
		if (num) {
			heap.insert(num);
		}
		else {
			cout << heap.pop() << '\n';
		}
	}

	return 0;
}
