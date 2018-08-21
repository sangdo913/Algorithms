//https://codeforces.com/contest/1025/problem/D
//D. Recovering BST
#pragma once
#include<cstdio>
#include<cstring>
using namespace std;

int gcd(int i1, int i2) {
	int r;
	if (i1 < i2) {
		int temp = i1;
		i1 = i2;
		i2 = temp;
	}

	while (i2) {
		r = i1 % i2;
		i1 = i2;
		i2 = r;
	}

	return i1;
}

int arr[701];
char canMake[3][701][701];
bool adj[701][701];

bool make(int p, int l, int r) {
	char &ret = canMake[p][l][r];

	if (l > r) return  ret = true;
	if (ret != -1) return ret;

	ret = 0;
	int parent;

	switch (p) {
	case 0:
		parent = 0;
		break;
	case 1:
		parent = r + 1;
		break;
	case 2:
		parent = l - 1;
		break;
	}

	for (int i = l; i <= r; i++) {
		if (adj[parent][i] && make(1, l, i - 1) && make(2, i + 1, r)) {
			return ret = 1;
		}
	}

	return ret;
}

int Codeforce0819D() {
	int n;
	scanf("%d\n", &n);
	memset(canMake, -1, sizeof(canMake));

	for (int i = 1; i <= n; i++) {
		scanf("%d\n", &arr[i]);
	}

	for (int i = 1; i <= n; i++) {
		adj[0][i] = true;

		for (int j = i + 1; j <= n; j++) {
			if (gcd(arr[i], arr[j]) != 1) {
				adj[i][j] = true;
				adj[j][i] = true;
			}
		}
	}

	if (make(0,1, n)) {
		printf("Yes\n");
		return 0;
	}
	printf("No\n");
	return 0;
}