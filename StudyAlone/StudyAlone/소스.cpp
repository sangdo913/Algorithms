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
void cycle() {                           // 시계방향으로 1칸 이동

	char temp[10000];

	for (long long i = 0; i<n; i++) {
		temp[(i + 1 + n) % n] = arr[i];
	}
	for (long long i = 0; i<n; i++) {
		arr[i] = temp[i];
	}
}

long long idx = 0;
long long sep() {                            // 한 변의(idx~idx+(n/4)까지) 16진수를 떼서 10진수로 변환
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
		long long ans = sep();          // 총 4번 해서 모든 변의 숫자를 구한다

		long long flag = 0;

		for (long long i = 0; i<saveNum.size(); i++) {    // 벡터에 중복 값이 있으면 넣지 않고 아니면 넣는다.
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
void solve() {                           // 초기 16진수 4개를 10진 수로 변환 하고 저장
	save();

	for (long long i = 0; i<n - 2; i++) {       // 1번씩 총 n-1번 회전해서 나온 값을 찾아서 저장(중복 제외)
		idx = 0;
		cycle();
		save();
	}
}
void init() {                        // 초기화
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
