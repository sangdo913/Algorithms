#include<iostream>

using namespace std;

int heap[101], hsize;

void push(int i) {
	int c = ++hsize, p;
	while ((p = c>>1) && i < heap[p]) heap[c] = heap[p], c = p;
	heap[c] = i;
}

int getchild(int  idx) {
	int l = idx * 2;
	int r = l + 1;
	if (l > hsize) return 0;
	else if (r > hsize) return l;
	else if (heap[l] < heap[r]) return l;
	return r;
}

int pop() {
	int ret = heap[1];
	int data = heap[hsize--];
	int p = 1,  c;
	while ((c = getchild(p)) && data > heap[c]) heap[p] = heap[c], p = c; 
	heap[p] = data;
	return ret;
}

int main() {
	int c;
	cin >> c;

	while (c--) {
		int n;
		int res = 0;
		hsize = 0;

		cin >> n;
		int in;
		for (int i = 0; i < n; ++i) cin >> in, push(in);
		

		while (hsize!= 1) {
			int i1, i2;
			i1 = pop();
			i2 = pop();
			res += i1  +i2;
			push(i1 + i2);
		}

		cout << res << '\n';
	}
}