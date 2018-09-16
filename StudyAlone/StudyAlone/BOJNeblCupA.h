#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

long long GCD(long long l1, long long l2) {
	int a = l1, b = l2, r;

	if (a < b) {
		long long temp = a;
		a = b;
		b = temp;
	}

	while (b) {
		r = a % b;
		a = b;
		b = r;
	}

	return a;
}

struct A {
	long long parent;
	long long child;
};
typedef long long ll;
ll ABS(ll l1) {
	return l1 > 0 ? l1 : -l1;
 }
A operator+(A a, A b) {
	A res;
	if (a.parent != b.parent) {
		long long g = GCD(a.parent, b.parent);
		long long mul[2] = { (b.parent * g ), (a.parent * g ) };
		
		int mcnt = a.parent < 0 + a.child < 0 + b.parent < 0 + b.child < 0;
		mcnt &= 1;
		a.parent = abs(a.parent);
		a.child = abs(a.child);
		b.parent = abs(b.parent);
		b.child = abs(b.child);

		a.child *= mul[0];
		b.child *= mul[1];

		res.parent = a.parent / g * b.parent;
		res.child = a.child + b.child;
		res.child = mcnt ? -res.child : res.child;
	}

	else {
		res.parent = a.parent;
		res.child = a.child + b.child;
		int mcnt = res.parent < 0 + res.child < 0;
		res.parent = abs(res.parent);
		res.child = mcnt & 1 ? -abs(res.child) : abs(res.child);
	}
	return res;
}

A slopes[50];
int parents[50];
vector<int> vec;
int BOJNeblCupA() {
	int n;
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	
	int px, ph;
	cin >> px >> ph;
	vec.push_back(px);
	for (int i = 0; i < n; i++) {
		int x , h;
		cin >> x >> h;
		vec.push_back(x);

		slopes[i].parent = x - px;
		slopes[i].child = h - ph;
	}
	int st, ed;
	cin >> st >> ed;
	auto it1 = lower_bound(vec.begin(), vec.end(), st);
	auto it2 = upper_bound(vec.begin(), vec.end(), ed);

	 it2 = prev(it2); 
	int idx[2] = { it1 - vec.begin(), it2 - vec.begin() };

	A res;
	res.parent = 1;
	res.child = 0;
	for (int i = idx[0]; i <= idx[1]; i++) {
		res = res +  slopes[i];
	}
	
	res.parent *= (idx[1] - idx[0] + 1);
	ll g = GCD(res.child, res.parent);

	res.child /= g;
	res.parent /= g;
	if (res.child == 0) {
		cout << 0 << endl;
	}

	else if (res.parent =! 1) {
		cout << res.child << '/' << res.parent << '\n';
	}
	else  {
		cout << res.child << '\n';
	}
	return 0;
}
