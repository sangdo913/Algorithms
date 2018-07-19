#pragma once
#include<cstdio>
struct Heap {
	long long arr[100001];
	int size;
	int getRight(int idx) {
		return (idx << 1) + 1;
	}
	int getLeft(int idx) {
		return (idx << 1);
	}

	int getChild(int idx) {
		int l = getLeft(idx);
		int r = getRight(idx);

		if (l > size) return 0;
		else if (r > size) return l;
		else {
			return arr[l] < arr[r] ? l : r;
		}
	}
	int getParent(int idx) {
		return idx >> 1;
	}
	void push(long long i) {
		size++;
		int idx = size, parent = getParent(idx);
		while (parent && i < arr[parent]) {
			arr[idx] = arr[parent];
			idx = parent;
			parent = getParent(idx);
		}
		arr[idx] = i;
	}

	long long pop() {
		int idx = 1, child = getChild(idx);
		long long ret = arr[1];
		long long last = arr[size--];
		while (child && last > arr[child]) {
			arr[idx] = arr[child];
			idx = child;
			child = getChild(idx);
		}

		arr[idx] = last;
		return ret;
	}
	Heap() {
		size = 0;
	}
	void clear() {
		size = 0;
	}
} heap;

int n;

int OldCalculator() {
	int t;
	scanf("%d\n", &t);
	for (int tc = 1; tc <= t; tc++) {
		scanf("%d\n", &n);

		while (n--) {
			int in;
			scanf("%d\n", &in);
			heap.push(in);
		}

		long long time = 0, temp;

		temp = heap.pop() + heap.pop();
		time += temp;
		while (heap.size) {
			heap.push(temp);

			temp = heap.pop() + heap.pop();
			time += temp;
		}
		printf("#%d %lld\n", tc, time);
	}
	return 0;
}