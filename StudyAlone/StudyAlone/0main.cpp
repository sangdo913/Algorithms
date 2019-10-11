#include"AOJ/GRADUATION.h"

//TEST
//#include<iostream>
//#include<queue>
//#include<algorithm>
//#include<vector>
//#include<set>
//
//using namespace std;
//
//typedef long long ll;
//
//struct NODE {
//	ll s, e, v;
//};
//queue<NODE> Q;
//vector<long long> res;
//set<ll> visit;
//
//int main() {
//	int n;
//	n = 2;
//	for (ll i = 1; i <= 1000000; ++i) {
//		if (i*(i + 1) <= 1e12) {
//			Q.push({ i,i + 1,i*(i + 1) });
//			visit.insert(i*(i+1));
//		}
//	}
//
//	while (Q.size()) {
//		// now : s * s+1 * s+2 * ... * e
//		NODE now=  Q.front(); 
//		Q.pop();
//		res.push_back(now.v);
//
//		NODE next;
//		
//		// next1 : s-1 * s * s+1 * ... * e
//		next = now;
//		next.s--;
//		next.v *= next.s;
//		if (next.s && visit.find(next.v) == visit.end() && next.v <= 1e12) {
//			Q.push(next);
//			visit.insert(next.v);
//		}
//
//		// next2 : s * s+1 * s+2 * ... *e * e+1
//		next = now;
//		next.e++;
//		next.v *= next.e;
//		if (next.v <= 1e12 && visit.find(next.v) == visit.end()) {
//			visit.insert(next.v);
//			Q.push(next);
//		}
//	}
//
//	res.push_back(0);
//	sort(res.begin(), res.end());
//	cout << res.size() <<endl;
//	
//	for (int i = 0; i < 10; ++i) cout << res[i] << ' ';
//	cout << endl;
//	cout << res.back() << endl;
//
//	return 0;
//}