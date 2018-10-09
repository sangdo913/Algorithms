#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long n, k;
char arr[28];
vector<long long> saveNum;
bool desc(int a, int b) {
	return a>b;
}
void cycle() {                           // �ð�������� 1ĭ �̵�

	char temp[10000];

	for (long long i = 0; i<n; i++) {
		temp[(i + 1 + n) % n] = arr[i];
	}
	for (long long i = 0; i<n; i++) {
		arr[i] = temp[i];
	}
}

long long idx = 0;
long long sep() {                            // �� ����(idx~idx+(n/4)����) 16������ ���� 10������ ��ȯ
	long long k = idx + (n / 4);
	long long ans = 0;

	for (long long i = idx; i<k; i++) {
		long long a = 0;
		if ('A' <= arr[i] && arr[i] <= 'F') {
			a = arr[i] - 'A';
		}
		else {
			a = arr[i] - '0';
		}
		ans = ans * 16 + a;
		idx = k;
	}
	return ans;
}

void save() {
	for (long long j = 0; j<4; j++) {
		long long ans = sep();          // �� 4�� �ؼ� ��� ���� ���ڸ� ���Ѵ�

		long long flag = 0;

		for (long long i = 0; i<saveNum.size(); i++) {    // ���Ϳ� �ߺ� ���� ������ ���� �ʰ� �ƴϸ� �ִ´�.
			if (ans == saveNum[i]) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			saveNum.push_back(ans);
		}
	}
}
void solve() {                           // �ʱ� 16���� 4���� 10�� ���� ��ȯ �ϰ� ����
	save();

	for (long long i = 0; i<n - 2; i++) {       // 1���� �� n-1�� ȸ���ؼ� ���� ���� ã�Ƽ� ����(�ߺ� ����)
		idx = 0;
		cycle();
		save();
	}
}
void init() {                        // �ʱ�ȭ
	idx = 0;
	for (long long i = 0; i<28; i++) {
		arr[i] = ' ';
	}
	saveNum.clear();
}

int main() {
	long long t;
	cin >> t;
	cout << (char)55 << endl;
	for (long long i = 1; i <= 5; i++) {

		init();

		cin >> n;
		cin >> k;


		for (long long i = 0; i<n; i++) {
			cin >> arr[i];
		}

		solve();
		sort(saveNum.begin(), saveNum.end(), desc);

		cout << "#" << i << " " << saveNum[k - 1] << endl;
	}
	return 0;
}
