#include<vector>
#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

typedef vector<int> VEC;
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) > (b) ? (b) : (a))

void popvec(VEC& a) {
	while (a.size() && !a.back()) a.pop_back();
}

void myplus(VEC& a, VEC& b) {
	a.resize(MAX(a.size(),b.size()));
	for (int i = 0; i < b.size(); ++i) {
		a[i] += b[i];
	}
	popvec(a);
}

void mul(VEC& a, VEC&b, VEC & res) {
	res.resize(a.size() + b.size());
	for (int i = 0; i < a.size(); ++i) for (int j = 0; j < b.size(); ++j) {
		res[i + j] += a[i] * b[j];
	}
	popvec(res);
}

void karatuba(VEC&a, VEC&b, VEC&res) {
	if (!a.size() || !b.size()) return ;
	if (a.size() < b.size()) {
		karatuba(b, a, res); return;
	}
	if (a.size() < 50) {
		return mul(a, b, res);
	}

	VEC v[4];
	int len = a.size()/ 2;
	v[0] = VEC(a.begin(), a.begin() + MIN(len, a.size()));
	v[1] = VEC(a.begin() + MIN(len, a.size()), a.end());

	v[2] = VEC(b.begin(), b.begin() + MIN(len, b.size()));
	v[3] = VEC(b.begin() + MIN(len, b.size()), b.end());

	VEC z1, z2, z3; 
	karatuba(v[0], v[2], z1);
	karatuba(v[1], v[3], z3);

	myplus(v[1], v[0]);
	myplus(v[3], v[2]);
	karatuba(v[1], v[3], z2);

	res.resize(a.size() + b.size());
	len = a.size() / 2;
	for (int i = 0; i < z1.size(); ++i) z2[i] -= z1[i];
	for (int i = 0; i < z3.size(); ++i) z2[i] -= z3[i];
	for (int i = 0; i < z1.size(); ++i) res[i] += z1[i];
	for (int i = 0; i < z2.size(); ++i) res[i + len] += z2[i];
	for (int i = 0; i < z3.size(); ++i) res[i + 2 * len] += z3[i];
	popvec(res);
}

int main() {
	ios_base::sync_with_stdio(0), cout.tie(0), cin.tie(0);
	int tc;
	cin >> tc;
	while (tc--) {
		string in1, in2;
		cin >> in1 >> in2;
		reverse(in1.begin(), in1.end());
		VEC v1, v2;
		v1.resize(in1.size()), v2.resize(in2.size());
		for (int i = 0; i < in1.size(); ++i) v1[i] = in1[i] == 'M';
		for (int i = 0; i < in2.size(); ++i) v2[i] = in2[i] == 'M';

		VEC res;
		res.clear();
		popvec(v1);
		popvec(v2);
		karatuba(v1, v2, res);
		int ret = 0;
		res.resize(in1.size() + in2.size(), 0);
		for (int i = 0; i < in2.size() - in1.size() +1; ++i)
			ret += !res[i + in1.size()-1];
		cout << ret << '\n';
	}
	
	return 0;
}
