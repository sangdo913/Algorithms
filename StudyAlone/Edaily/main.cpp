#include<iostream>
using namespace std;

void print(int a, int n) {
	while (n--) {
		cout << (a & 1) << ' ';
		a>>=1;
	}
	cout << endl;
}

int main() {
	int num = 0b1010111;

	int b = num;
	int cnt = 0;
	while (b) {
		cnt++;
		print(b,7);
		b = num & (b - 1);
	}
	cout << cnt << endl;

	return 0;
}