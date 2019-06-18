#include<iostream>

using namespace std;

long long input[100001];
long long sum[100001];
int n, m;
long long res;
#define MAX(x,y) ((x) > (y) ?(x) : (y))

long long getget(int i, int &mm) {
	if (i == n - m+1) {
		res = (MAX(res, ((sum[n] - sum[i - 1])/m)));
		mm = m;
		return sum[n] - sum[i - 1];
	}
	
	int prev;
	long long s1 = ((sum[i + m - 1] - sum[i - 1])/m);
	long long temp = getget(i + 1, prev);
	long long s2 = ((temp + input[i]) / (prev + 1));
	if (s1 < s2) {
		res = MAX(s2, res);
		mm = prev + 1;
		return temp+input[i];
	}
	else {
		res = MAX(s1, res);
		mm = m;
		return sum[i + m - 1] - sum[i - 1];
	}
}

int main() {
	cin >> n >> m;
	
	for (int i = 1; i <= n; ++i) {
		cin >> input[i];
		input[i] *= 1000;
		sum[i] = sum[i - 1] + input[i];
	}
	int prev;
	getget(1, prev);
	cout << res;

	return 0;
}