#include<iostream>
#include<algorithm>
#include<tuple>
#include<vector>

using namespace std;

typedef tuple<int, int, int,int> ti4;
typedef vector<int> vi;
ti4 rect[200000];

int CodeforceAIMC() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	vi vl, vr, vd, vu;

	int l, r, d, u;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> l >> d >> r >> u;
		vl.push_back(l);
		vd.push_back(d);
		vr.push_back(r);
		vu.push_back(u);
		rect[i] = { l,d,r,u };
	}
	sort(vl.begin(), vl.end());
	sort(vr.begin(), vr.end());
	sort(vd.begin(), vd.end());
	sort(vu.begin(), vu.end());

	for (int i = 0; i < n; i++) {
		tie(l, d, r, u) = rect[i];
		int xmin, xmax, ymin, ymax;

		xmin = l == *vl.rbegin() ? *next(vl.rbegin()) : *vl.rbegin();
		xmax = r == *vr.begin() ? *next(vr.begin()) : *vr.begin();
		ymin = d == *vd.rbegin() ? *next(vd.rbegin()) : *vd.rbegin();
		ymax = u == *vu.begin() ? *next(vu.begin()) : *vu.begin();

		if (xmin <= xmax && ymin <= ymax) {
			cout << xmin << ' ' << ymin << '\n';
			return 0;
		}
	}
	return 0;
}