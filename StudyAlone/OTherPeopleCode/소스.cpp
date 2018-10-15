#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int SIZE;
bool visit[1000000][11];
int n, change;
string ans;
string S;

void solve(int x, int cnt) {
	//if (x == SIZE) return;
	//if (visit[stoi(S)][cnt]) return;
	//visit[stoi(S)][cnt] = true;

	if (cnt == change) {
		if (S > ans)
			ans = S;
		return;
	}

	for (int i = 0; i < SIZE; i++) {
		if (x == i)
			continue;
		if (S[x] <= S[i]) {
			swap(S[x], S[i]);
			solve(x + 1, cnt + 1);
			swap(S[x], S[i]);
		}
	}

}

int main() {
	int t; scanf("%d\n", &t);
	for (int i = 1; i <= t; i++){

		cin >> S;
		SIZE = S.size();
		scanf("%d", &change);

		solve(0, 0);

		cout << ans << endl;

	}
	return 0;
}