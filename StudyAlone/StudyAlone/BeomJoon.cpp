
#include<iostream>
#include<algorithm>
#include<string>
#include<queue>

using namespace std;
int L, C;
int num[16] = { 0, };
int temp[16] = { 0, };
int aeiou[5] = { 'a','e','i','o','u' };
int temp2[16] = {};
void solv() {
	for (int i = 0; i < 16; i++) temp2[i] = temp[i];

	sort(temp, temp + L);
	int cnt = 0;
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < 5; j++) {
			if (temp[i]+'a' == aeiou[j])cnt++;
		}
	}
	if (cnt > 0 && cnt < L - 1) {
		for (int i = 0; i < L; i++) {
			char ss = temp[i] + 'a';
			cout << ss;
		}
		printf("\n");
	}

	for (int i = 0; i < 16; i++) temp[i] = temp2[i];
}
void func(int l, int c) {
	if (l == C && c < L) return;
	if (c == L) {
		solv();
		return;
	}
	temp[c] = num[l];
	func(l + 1, c + 1);
	temp[c] = 0;
	func(l + 1, c);
}
int main()
{
	cin >> L >> C;
	char vv;
	for (int c = 0; c < C; c++)
	{
		cin >> vv;
		num[c] = vv - 'a';
	}
	func(0, 0);
	return 0;
}