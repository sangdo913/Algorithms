#pragma once
#include<cstdio>
using namespace std;

typedef long long ll;
const int MAXN = 100005;

struct cht {
	long long double pa[MAXN], pb[MAXN];
	int sz, piv;

	// �� �ܹ��� ����� ����� ���� �ܹ��� ����� ����� �ð� ����
	// == �ٷ� ������ ���� �ܹ��ſ� ���� ��������� �ܹ����� ����
	long long double cross(int a, int b) 
	{
		return (pb[a] - pb[b]) / (pa[b] - pa[a]);
	}

	//���� ���� �̾� ���� �� ���� ���(���� ��� ���̰� �Ʒ��� �����̺��� ���.) ���� ������ ����Ѵ�.
	void add(long long double a, long long double b) {
		pa[sz] = a;
		pb[sz] = b;
		while (sz - 2 >= 0 && cross(sz - 2, sz - 1) > cross(sz - 1, sz)) {
			pa[sz - 1] = pa[sz];
			pb[sz - 1] = pb[sz];
			sz--;
		}
		sz++;
	}
	//parametric search , ���� ���� ���� ���� �� �ִ� ��ġ�� ���Ѵ�.
	long long double query(long long double piv) {
		int s = 0, e = sz - 1;
		while (s != e) {
			int m = (s + e) / 2;
			if (cross(m, m + 1) <= piv) s = m+1; //parametric true
			else e = m;
		}
		return pa[s] * piv + pb[s];
	}
} C;

int N, M;
ll T[MAXN], F[MAXN], S[MAXN];

int GodHongJoon() {
	int TC; 
	for (scanf("%d", &TC); TC--; ) {
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= N; i++) {
			scanf("%lld", &T[i]);
			S[i] = S[i - 1] + T[i];
		}

		C.sz = 0;
		for (int i = 0; i < N; i++) C.add(S[i + 1], -S[i]);
		for (int i = 1; i <= M; i++) scanf("%lld", &F[i]);
		ll ans = 0;
		for (int i = 1; i < M; i++) {
			long long double x = (long long double)(F[i]) / (long long double)(F[i + 1]);
			long long double y = C.query(x);
			ans += (ll)(y*(long long double)(F[i + 1]) + 1e-2);
		}
		ans += F[M] * S[N];
		static int tc = 0;
		printf("#%d %lld\n", ++tc, ans);
	}
	return 0;
}