//swea 3951
//CRT
#pragma once
#include<iostream>
#include<cstring>

using namespace std;

int n;
long long ppa, ppb;

//확클리드
long long GCD(long long a, long long b) {
	bool conv = a < b;

	if (conv) {
		long long temp = a;
		a = b;
		b = temp;
	}

	ppa = 1, ppb = 0;
	long long pa = 0, pb = 1;

	while (b) {
		long long s, t, r, sh;
		sh = a / b;
		r = a % b;
		s = ppa - sh * pa;
		t = ppb - sh * pb;

		a = b;
		b = r;
		ppa = pa;
		ppb = pb;
		pa = s;
		pb = t;
	}

	if (conv) ppa = ppb;

	return a;
}

int SWEA3951() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n;

		int a1 = 1, b1 = 0;
		for (int i = 0; i < n; i++) {
			long long input[2];

			cin >> input[0] >> input[1];
				
			long long a, b;

			input[0] -= b1;

			if (input[0] < 0) {
				long long pl = (-input[0] / input[1] + 1);
				input[0] += pl * input[1];
			}

			long long g = GCD(input[0], input[1]);

			long long ta = a1 % input[1];

			g = GCD(g, ta);

			input[0] /= g;
			input[1] /= g;

			long long g2 = GCD(ta / g, input[1]);

			if (ppa < 0) {
				long long pl = (-ppa / input[1] + 1);
				ppa += pl * input[1];
			}

			a = a1 * input[1];
			b = (a1 * ((ppa * input[0] / g2)%input[1]) + b1) % a;
			a1 = a, b1 = b;
		}

		cout << '#' << tc << ' ' << b1 << '\n';
	}
	return 0;
}
