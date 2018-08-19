#pragma once
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> vec;
int arr[10001];
int res[2];
double diff;

int Codeeforce0818C() {
	int t;
	scanf("%d\n", &t);
	while (t--) {
		int n;
		vec.clear();
		diff = 1e12;
		scanf("%d \n", &n);
		memset(arr, 0, sizeof(arr));

		while (n--) {
			int input;
			scanf("%d\n", &input);

			arr[input]++;
			if (arr[input] == 2) vec.push_back(input);
			else if (arr[input] == 4) vec.push_back(input);
		}

		sort(vec.begin(), vec.end());

		for (int i = 1; i < vec.size(); i++) {
			  double value = 4.0*(  double)(vec[i] + vec[i - 1])*(  double)(vec[i] + vec[i - 1]) / (  double)(vec[i]) / (  double)(vec[i - 1]);
			if (diff > value ) {
				diff = value;
				res[0] = vec[i-1];
				res[1] = vec[i];
			}
		}
		printf("%d %d %d %d\n", res[0], res[0], res[1], res[1]);
	}
	return 0;
}