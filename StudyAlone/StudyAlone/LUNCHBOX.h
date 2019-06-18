#include<iostream>

using namespace std;


int hot[10000];
int eat[10000];
int idx[10000];
int temp[10000];
int n;

bool priority(int a, int b) {
	if (eat[a] == eat[b]) return hot[a] < hot[b];
	return eat[a] > eat[b];
}

void  mergeSort(int s, int e) {
	int l = s, m = (s + e) / 2, k = s , r = m + 1;
	
	while (l <= m && r <= e) temp[k++] = priority(idx[l], idx[r]) ? idx[l++] : idx[r++];
	while (l <= m) temp[k++] = idx[l++];
	while (r <= e) temp[k++] = idx[r++];
	for (int i = s; i <= e; ++i) idx[i] = temp[i];
}

void merge(int s, int e) {
	if (s < e) {
		int m = (s + e) / 2;
		merge(s, m);
		merge(m + 1, e);
		mergeSort(s, e);
	}
}
int main() {
	int c;
	cin >> c;
	while (c--) {
		cin >> n;
		for (int i = 0; i < n; ++i) cin >> hot[i], idx[i] = i;
		for (int i = 0; i < n; ++i) cin >> eat[i];
		merge(0, n - 1);
		int prevs = 0;
		int res = 0;
		for (int i = 0; i < n; ++i) {
			prevs += hot[idx[i]];
			res = res > prevs +  eat[idx[i]] ? res :  prevs+eat[idx[i]];
		}
		cout << res << '\n';
	}
	return 0;
}