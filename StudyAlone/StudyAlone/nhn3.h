#include <iostream>
#include<algorithm>

using namespace std;

int st[50000], top;
int arr[1001];
int index[1001];

struct cmp {
	bool operator()(int a, int b) {
		if (arr[a] == arr[b]) return a > b;
		return arr[a] > arr[b];
	}
};

int nhn3() {
	int d, p;
	cin >> d;

	for (int i = 0; i < d; i++) {
		cin >> arr[i];
	}

	for (int i = 0; i < d; i++) {
		index[i] = i;
	}

	sort(index, index + d, cmp());

	int prev = 0;
	int res = 0;
	for (int i = 0; i < d; i++) {
		int now = index[i];
		if (now <= prev) continue;

		int sum = 0;
		for (int j = prev; j < now; j++) {
			sum += arr[now] - arr[j];
		}
		sum--;

		if (sum > 0) res += sum;
		prev = now+1;
	}
	cout << res << '\n';
	return 0;
}