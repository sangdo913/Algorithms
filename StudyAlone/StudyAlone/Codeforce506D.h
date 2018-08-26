#pragma once
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

vector<long long> vec[12];

long long remains[200001][12];
long long remains1[200001];
int p[200001];

int getDigit(long long i) {
	int res = 0;
	while (i) {
		i /= 10;
		res++;
	}
	return res;
}

int size(vector<long long> & vec, long long value) {
	int l = 0; int r = vec.size() - 1;
	int m;
	while (l < r) {
		m = (l + r) / 2;

		if (value <= vec[m]) {
			r = m;
		}
		else {
			l = m + 1;
		}
	}

	int i1 = r;
	l = 0; r = vec.size() - 1;
	while (l < r) {
		m = (l + r) / 2;
		if (value < vec[m]) {
			r = m;
		}
		else {
			l = m + 1;
		}
	}
	if (vec[i1] != value) return 0;
	int i2 = r;
	if (vec.size() - 1 == i2 && vec[i2] == value) i2++;
	return i2 - i1;
}

int main() {
	int n; long long k;
	scanf("%d %lld\n", &n, &k);

	for (int i = 0; i < n; i++) {
		long long in;
		scanf("%lld\n", &in);
		remains[i][0] = in % k;
		p[i] = getDigit(in);
		for (int j = 1; j < 12; j++) {
			remains[i][j] = (remains[i][j - 1] * 10) % k;
			vec[j].push_back(remains[i][j]);
		}
	}
	long long res = 0;
	for (int i = 1; i < 12; i++) sort(vec[i].begin(), vec[i].end());

	for (int i = 0; i < n; i++) {
		int pow = p[i];
		res += size(vec[pow], (k - remains[i][0]) % k);
		if (remains[i][pow] == (k - remains[i][0]) % k) res--;
	}

	printf("%lld\n", res);

	return 0;
}
//#pragma once
//#include<cstdio>
//#include<vector>
//#include<algorithm>
//#include<map>
//using namespace std;
//
//map<int, int> mp[12];
//long long remains[200001][12];
//long long remains1[200001];
//int p[200001];
//
//int getDigit(long long i) {
//	int res = 0;
//	while (i) {
//		i /= 10;
//		res++;
//	}
//	return res;
//}
//
//int Codeforce506C() {
//	int n; long long k;
//	scanf("%d %lld\n", &n, &k);
//
//	for (int i = 0; i < n; i++) {
//		long long in;
//		scanf("%lld\n", &in);
//		remains[i][0] = in % k;
//		p[i] = getDigit(in);
//		for (int j = 1; j < 12; j++) {
//			remains[i][j] = (remains[i][j - 1] * 10) % k;
//			mp[j][remains[i][j]]++;
//		}
//	}
//	int res = 0;
//
//	for (int i = 0; i < n; i++) {
//		int pow = p[i];
//		mp[p[i]][(remains[i][p[i]])]--;
//		res += mp[p[i]][(k - remains[i][0]) % k];
//		mp[p[i]][(remains[i][p[i]])]++;
//	}
//
//	printf("%d\n", res);
//
//	return 0;
//}