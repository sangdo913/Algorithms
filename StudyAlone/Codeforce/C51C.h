#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>

using namespace std;

vector<int> vec;
vector<int> nices;
map<int, int> mp;


int C51C() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;

	cin >> n;
	for (int i = 0; i < n; i++) {
		int in;
		cin >> in;
		vec.push_back(in);
		mp[in] = i;
	}

	sort(vec.begin(), vec.end());

	int nicenum = 0;
	int flag = vec[0];
	int cnt = 1;
	bool isnum2 = false;
	int num2 = 0;

	for (int i = 1; i < vec.size(); i++) {
		if (vec[i] != flag) {
			if (cnt == 1) {
				nices.push_back(flag);
				nicenum++;
			}
			flag = vec[i];
			cnt = 1;
		}
		else {
			cnt++;
			if (cnt > 2) {
				isnum2 = true;
				num2 = flag;
			}
		}
	}
	if (vec.size() > 1 && vec[vec.size() - 1] != vec[vec.size() - 2]) {
		nices.push_back(vec[vec.size() - 1]);
	}

	vector<char> res;
	res.resize(vec.size());
	for (int i = 0; i < res.size(); i++) {
		res[i] = 'A';
	}

	if (vec.size() == 1) {
		cout << "NO";
		return 0 ;
	}
	if (nices.size() & 1) {
		if (isnum2) {
			res[mp[num2]] = 'B';
		}
		else {
			cout << "NO";
			return 0;
		}
	}

	cout << "YES\n";
	for (int i = 0; i < nices.size() / 2; i++) {
		res[mp[nices[i]]] = 'B';
	}

	for (int i = 0; i < res.size(); i++) {
		cout << res[i];
	}
	return 0;
}
