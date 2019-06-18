#include<iostream>

using namespace std;

bool num[100];

void tobinary(int n) {
	if (n == 0) {
		cout << 0; return;
	}

	int top = 0;

	while (n) {
		num[top++] = n & 1;
		n >>= 1;
	}

	while (top) {
		cout << (int)num[--top];
	}
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;

	cin >> n;
	
	for (int i = 0; i <= n; ++i) {
		tobinary(i);
	}

	return 0;
}
