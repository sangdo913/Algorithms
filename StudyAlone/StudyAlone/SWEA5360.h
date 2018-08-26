//https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWVWj7S6sXUDFAUO&categoryId=AWVWj7S6sXUDFAUO&categoryType=CODE&&&
// 5360. 모든 섬의 통신 비용
#pragma once
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;

int que[100001], f, r;
int indeg[100001];
vector<int> child[100001];
int info[100001][2];
int indeg2[100001];
vector<int> adj[100001];
int g[100001];
int p[100001];

int find(int idx) {
	int pa = p[idx];
	if (pa > 0) return p[idx] = find(pa);
	return idx;
}

void join(int a, int b) {
	int pa = find(a);
	int pb = find(b);

	if (pa == pb) return;

	if (p[pa] > p[pb]) {
		int temp = pa;
		pa = pb;
		pb = temp;
	}

	p[pa] += p[pb];
	p[pb] = pa;
}

int SWEA5360() {
	int t;
	scanf("%d\n", &t);
	
	for (int tc = 1; tc <= t; tc++) {
		int n;
		scanf("%d\n", &n);
		for (int i = 1; i <= n; i++) {
			adj[i].clear();
			p[i] = -1;
			indeg[i] = 0;
			child[i].clear();
			g[i] = 0;
		}

		f = r = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d %d\n", &info[i][0], &info[i][1]);
			indeg[info[i][0]]++;
			join(i, info[i][0]);
			child[info[i][0]].push_back(i);
		}

		memcpy(indeg2, indeg, sizeof(indeg));

		for (int i = 1; i <= n; i++) {
			if (indeg[i] == 0) {
				que[r++] = i;
			}
		}

		while (f != r) {
			int now = que[f++];
			int next = info[now][0];

			indeg[next]--;
			
			if (indeg[next] == 0) {
				que[r++] = next;
			}
		}
		
		int gNum = 1;
		for (int i = 1; i <= n; i++) {
			if (indeg[i]) {
				if (g[find(i)] == 0) g[find(i)] = gNum++;
				adj[g[find(i)]].push_back(i);
			}
		}

		long long res = 0;

		for (int i = 1; i <= n; i++) {
			long long max = 0, temp = 0;
			if (indeg[i] == 0 && indeg2[i] > 1) {
				for (int j = 0; j < child[i].size(); j++) {
					temp += info[child[i][j]][1];
					max = max < info[child[i][j]][1] ? info[child[i][j]][1] : max;
				}
				temp -= max;
				res += temp;
			}
		}

		long long mi = 0x7fffffffffffffff;
		bool cycle = true;

		for (int i = 1; i < gNum; i++) {
			long long temp = 0;
			mi = 0x7fffffffffffffff;

			for (int j = 0; j < adj[i].size(); j++) {
				int now = adj[i][j];

				if (child[now].size() > 1) {
					temp = 0;
					cycle = false;

					long long max = 0;
					long long max2 = 0;
					int midx = 0;
					for (int k = 0; k < child[now].size(); k++) {
						if (max < info[child[now][k]][1]) {
							max2 = max;
							max = info[child[now][k]][1];
							midx = child[now][k];
						}
						else if (max2 < info[child[now][k]][1]) {
							max2 = info[child[now][k]][1];
						}
						temp += info[child[now][k]][1];
					}

					temp -= max;
					if (indeg[midx]) {
							mi = mi > max - max2 ? max - max2 : mi;
					}
					else mi = 0;
					res += temp;
				}
			}

			for (int j = 0; j < adj[i].size(); j++) {
				mi = mi > info[adj[i][j]][1] ? info[adj[i][j]][1] : mi;
			}

			res += mi;
		}
		res -= cycle && (gNum == 2) ? mi : 0;
		printf("#%d %lld\n", tc, res);
	}
	return 0;
}