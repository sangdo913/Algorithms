#include<iostream>
#include<cstring>

using namespace std;

char str[2][100001];
int pos[2][100001];

#define ABS(x) ((x) > (0) ? (x) : -(x))

int Do() {
	int tc;
	cin >> tc;

	for (int t = 1; t <= tc; t++) {
		cin >> str[0] >> str[1];
		long long res = 0;
		int anum[2] = {0,0};

		for (int i = 0; str[0][i]; ++i) {
			if (str[0][i] == 'a') {
				pos[0][anum[0]++] = i;
			}

			if (str[1][i] == 'a') {
				pos[1][anum[1]++] = i;
			}
		}

		for (int i = 0; i < anum[0]; i++) {
			res += ABS(pos[0][i] - pos[1][i]);
		}
		cout << '#' << t << ' ' << res << '\n';
	}

	return 0;
}
