#pragma once
#include<iostream>
#include<string>

using namespace std;

string a, b;
int ex[3] = { 0, 0, 0 };

void getminLen() {
	if (ex[0] > 0 && ex[1] > 0 && ex[2] > 0) return ;

	if (ex[0] == 0) {
		if (ex[1] == 0) {
			a[0] = 'A';
			a[1] = 'a';
		}
		else if (ex[2] == 0) {
			a[0] = 'a';
			a[1] = '1';
		}
		else {
			if (ex[1] == 1) {
				for (int i = 0; i < a.size(); i++) {
					if (a[i] >= '0' && a[i] <= '9') {
						a[i] = 'a';
						break;
					}
				}
			}
			else if (ex[2] == 1) {
				for (int i = 0; i < a.size(); i++) {
					if (a[i] >= 'A' && a[i] <= 'Z') {
						a[i] = 'a';
						break;
					}
				}
			}
			else{
				a[0] = 'a';
			}
		}
	}
	else if (ex[1] == 0) {
		if(ex[2] == 0){
			a[0] = 'A';
			a[1] = '1';
			}
		else {
			if (ex[2] == 1) {
				for (int i = 0; i < a.size(); i++) {
					if (a[i] >= 'a' && a[i] <= 'z') {
						a[i] = 'A';
						break;
					}
				}
			}
			else if (ex[0] == 1) {
				for (int i = 0; i < a.size(); i++) {
					if (a[i] >= '0'&& a[i] <= '9') {
						a[i] = 'A';
						break;
					}
				}
			}
			else {
				a[0] = 'A';
			}
		}
	}
	else if (ex[2] == 0) {
		if (ex[0] == 1) {
			for (int i = 0; i < a.size(); i++) {
				if (a[i] >= 'A' && a[i] <= 'Z') {
					a[i] = '1';
					break;
				}
			}
		}
		else if (ex[1] == 1) {
			for (int i = 0; i < a.size(); i++) {
				if (a[i] >= 'a' && a[i] <= 'z') {
					a[i] = '1';
					break;
				}
			}
		}
		else {
			a[0] = '0';
		}
	}
}
int C51A() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		ex[0] = ex[1] = ex[2] = 0;
		cin >> a ;
		for (int i = 0; i < a.size(); i++) {
			if (a[i] >= 'a' && a[i] <= 'z') {
				ex[0]++  ;
			}
		}

		for (int i = 0; i < a.size(); i++) 
		{
			if (a[i] >= 'A' && a[i] <= 'Z') {
				ex[1]++;
			}
		}

		for (int i = 0; i < a.size(); i++) {
			if (a[i] >= '0' && a[i] <= '9') {
				ex[2]++;
			}
		}
		getminLen();
		cout << a << endl;
	}
	return 0;
}
