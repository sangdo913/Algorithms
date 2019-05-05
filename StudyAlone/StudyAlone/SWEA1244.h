#include<iostream>
#include<queue>
#include<string>
#include<cstring>
#include<vector>

using namespace std;

#define MIN(x,y) (((x) > (y)) ?(y):(x))

int dfs(bool ok ,string str, int s, int k) {
	if (k == 0) {
		return atoi(str.c_str());
	}
	else if (s == str.size()-1) {
		if(!ok && k%2) str[str.size() - 1] ^= str[str.size() - 2] ^= str[str.size() - 1] ^= str[str.size() - 2];
		return atoi(str.c_str());
	}

	priority_queue<pair<char, int> > pq;
	vector<int> vec;

	for (int i = s; i < str.size(); ++i) pq.push({ str[i],i });

	auto n = pq.top(); pq.pop();
	int cnt = 1;
	
	if (n.first > str[s]) {
		while (pq.top().first == n.first) pq.pop(), ++cnt;

		cnt = MIN(cnt, k);
		priority_queue<int> pq2;

		for (int i = s; i < s+cnt; ++i) 
			if (str[i] != n.first)pq2.push(str[i]);
		
		int st = pq2.size();

		for (int i = s + pq2.size(); i < str.size(); ++i) 
			if (n.first == str[i]) vec.push_back(i);

		int idx = 0;
		for (int i = 0; i < cnt; ++i) 
			if (n.first > str[i+s]) {
				str[vec[vec.size()-st + idx++]] = pq2.top(); pq2.pop();
				str[i+s] = n.first;
				--k;
			}
	}
	return dfs(ok, str, s + cnt, k);
}

int ain() {
	int tc, k; string str;
	cin >> tc;
	for (int t = 1; t <= tc; t++) {
		cin >> str >> k;
		bool ok = false;
		bool check[10] = {};

		for (int i = 0; i < str.size(); ++i) {
			ok |= check[str[i] - '0'];
			check[str[i] - '0'] = true;
		}

		cout << '#' << t << ' ' << dfs(ok, str, 0, k) << '\n';
	}
	return 0;
}
