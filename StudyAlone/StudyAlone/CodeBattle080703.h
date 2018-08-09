#pragma once
#include<cstdio>
#include<vector>

using namespace std;
vector<int> bmul(vector<int>& in1, vector<int>& in2) {
	if (in2.size() == 0 || in2.size() == 0) return vector<int>(0);
	vector<int> res;
	res.resize(in1.size() + in2.size(), 0);

	for (int i = 0; i < in1.size(); i++) {
		for (int j = 0; j < in2.size(); j++) {
			res[i + j] += in1[i] * in2[j];
		}
	}
	int cnt = 0;
	for (int i = res.size() - 1; res[i]==0; i--, cnt++);

	for (int i = 0; i < res.size(); i++) {
		res[i] %= 3;
	}
	res.resize(res.size() - cnt);
	return res;
}

vector<int> mul(vector<int>& in1, long long pow) {
	if (pow == 0) return vector<int>(1, 1);

	vector<int> half = mul(in1, pow / 2);
	half = bmul(half, half);
	return pow & 1 ? bmul(half, in1) : half;
}

int CodeBattle080703() {
	
	int t;
	scanf("%d\n", &t);

	for (int tc = 1; tc <= 1; tc++) {
		long long n, k;
		scanf("%lld %lld\n", &n, &k);
		for (int i = 0; i < 99; i++) {
			vector<int> in;
			in.resize(3);
			in[0] = in[1] = in[2] = 1;
			vector<int> res = mul(in, i);
			for (int i = res.size() - 1; i >= 0; i--) printf("%d ", res[i]);
			printf("\n");
		}
	}
	return 0;
}