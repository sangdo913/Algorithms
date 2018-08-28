#pragma once
#include<cstdio>
#include<algorithm>
#include<stack>
#include<set>
using namespace std;
typedef pair<int, int> PII;
typedef pair<PII, PII> REC;
REC rec[200000];
REC lis[200000];
stack<REC> st;
struct CMP {
	bool operator() ( REC rec1, REC rec2 ) {
	long long s = (rec1.second.first - rec1.first.first)*(rec1.second.second - rec1.first.second);
	long long s2= (rec2.second.first - rec2.first.first)*(rec2.second.second - rec2.first.second);
	return s < s2;
	}
};

bool first(REC rec1, REC rec2) {
		if (rec1.first == rec2.first) {
			return rec1.second > rec2.second;
		}
		else {
			return rec1.first < rec2.first;
		}
}

bool cmp(REC rec1, REC rec2) {

	return rec1.second.first >= rec2.first.first && rec1.second.second >= rec2.first.second && rec1.first.first <= rec2.first.first && rec1.first.second <= rec2.first.second;
}

bool isfold(REC& rec1, REC& rec2) {
	if (!first(rec1,rec2)) {
		REC t = rec1;
		rec1 = rec2;
		rec2 = t;
	}
	REC r1 = rec1, r2 = rec2;
	rec1.first = rec2.first;
	rec1.second.first = rec1.second.first < rec2.second.first ? rec1.second.first : rec2.second.first;
	rec1.second.second = rec1.second.second < rec2.second.first ? rec1.second.first : rec2.second.first;
	return cmp(r1, r2);
}

int CodeforceAIMC() {
	int n;
	scanf("%d\n", &n);
	int x1, y1, x2, y2;
	lis[0].second.second = lis[0].second.first = 0x7fffffff;
	
	for (int i = 1; i <= n; i++) {
		scanf("%d %d %d %d\n", &x1, &y1, &x2, &y2);
		rec[i].first.first = x1;
		rec[i].first.second = y1;
		rec[i].second.first = x2;
		rec[i].second.second = y2;
	}

	if (n == 2) {
		if (first(rec[0], rec[1])) {
			printf("%d %d\n", rec[1].first.first, rec[1].first.second);
			return 0;
		}
	}

	sort(rec + 1, rec + n+1, CMP());
	REC res;
	REC temp[2] = { rec[1], rec[2] };
	if (isfold(temp[0], temp[1])) {
		res = temp[0];
		for (int i = 3; i <= n; i++) {
			REC t = res;
			if (isfold(t, rec[i])) {
				res = t;
			}
		}
	}
	else {
		temp[0] = rec[1];
		if (isfold(temp[0], rec[3])) {
			res = temp[0];
			for (int i = 4; i <= n; i++) {
				REC t = res;
				if (isfold(t, rec[i])) {
					res = t;
				}
			}
		}
		else {
			isfold(rec[2], rec[3]);
			res = rec[2];

			for (int i = 4; i <= n; i++) {
				REC t = res;
				if (isfold(t, rec[i])) {
					res = t;
				}
			}
		}
	}
		printf("%d %d\n", res.first.first, res.first.second);
	return 0;
}
