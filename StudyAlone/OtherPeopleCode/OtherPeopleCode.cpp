#include<iostream>
#include<vector>
#include <string>
#include<set>

using namespace std;
vector<string> vectorString;
int grid[4][4];

void countString(int a, int b, string s) {
	if (a>3 || b>3 || a<0 || b<0) return;
	if (s.size() == 7) {
		if (find(vectorString.begin(), vectorString.end(), s) == vectorString.end()) {
			vectorString.push_back(s);
			return;
		}
		return;
	}
	s += grid[a][b];

	countString(a + 1, b, s);//동
	countString(a - 1, b, s);//서
	countString(a, b - 1, s);//남
	countString(a, b + 1, s);//북
}



int main() {
	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		for (int j = 0; j<4; j++) {
			for (int k = 0; k<4; k++) {
				cin >> grid[3 - k][3 - j];
			}
		}
		for (int j = 0; j<4; j++) {
			for (int k = 0; k<4; k++) {
				countString(j, k, "");
			}
		}
		cout << "#" << i << ' ' << vectorString.size() <<'\n';

		vectorString.clear();
	}


	return 0;
}
