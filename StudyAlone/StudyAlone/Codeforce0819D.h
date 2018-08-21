#pragma once
#include<cstdio>
#include<set>

using namespace std;

set<int> se;

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

int arr[700];
bool check[700][2];

int Codeforce0819D() {
	int n;
	scanf("%d\n", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d\n", &arr[i]);
	}

	for (int i = 0; i < n; i++) {
		bool isOKay = false;
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			if (gcd(arr[i], arr[j]) != 1) {
				if (i < j && check[j][0]) {
					isOKay = true; 
					break;
				}
				else if (i > j && check[j][1]) {

				}
				isOKay = true; break;
			}
		}
		if (!isOKay) {
			printf("No\n");
			return 0;
		}
	}
	printf("Yes\n");
	return 0;
}