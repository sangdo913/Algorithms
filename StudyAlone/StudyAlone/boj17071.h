#include<iostream>
#define SIZE (500010*2)

using namespace std;

int visit[500001][2];
int que[SIZE];
int fr, re;

int main() {
	int n, k;
	cin >> n >> k;
	for (int i = 0; i <= 500000; ++i) visit[i][0] = visit[i][1] = 0x3f3f3f3f;

	int t = 0;
	fr = re = 0;
	que[re++] = n;
	visit[n][t] = 0;

	while (fr != re) {
		t++;
		int cnt = (re + SIZE - fr)%SIZE;
		while (cnt--) {
			int now = que[fr++%SIZE];

			int next = now + 1;

			if (next <= 500000 &&visit[next][t &1] > t) {
				visit[next][t&1] = t;
				que[re++%SIZE] = next;
			}
			next = now - 1;
			if (next >= 0&& visit[next][t&1]>t) {
				visit[next][t&1] = t;
				que[re++%SIZE] = next;
			}
			next = now * 2;
			if (next <= 500000 && visit[next][t &1] > t) {
				visit[next][t&1] = t;
				que[re++%SIZE] = next;
			}
		}
	}

	t = 0;
	int d = 1;
	while (k <= 500000) {
		if (visit[k][t & 1] <= t) {
			return !(cout << t);
		}
		k += d;
		d++;
		t++;
	}

	return !(cout<<-1);
}