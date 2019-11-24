#include<cstdio>
#include<cstring>

int people[50][50];
int order[51];
char mp[50][11];
int plen[50];
long long food[50];
int flen[50];
int n, m;
int c;
int answer;
#define mmin(x,y) ((x) < (y) ? (x) : (y))

int dfs(int l, int num, long long visit) {
	int pid = order[l];
	if (answer <= num) return 0x3f3f3f3f;
	if (visit == (1LL << n) - 1) return answer = num;
	if (l == n) return 0x3f3f3f3f;

	int ret = 0x3f3f3f3f;
	if (visit & (1LL << pid)) return ret = dfs(l + 1, num, visit);

	for (int i = 0; i < plen[pid]; ++i) {
		int fid = people[pid][i];
		if ((!(visit & (1LL << pid)))) {
			ret = mmin(ret,dfs(l + 1, num + 1, visit | food[fid]));
		}
	}

	return answer;
}

int mystrcmp(const char *s1, const char * s2) {
	while (*s1 && *s1 == *s2) s1++, s2++;
	return *s1 - *s2;
}


int main() {
	scanf(" %d ", &c);
	char name[11];
	while (c--) {
		scanf(" %d %d ", &n, &m);
		answer = 0x3f3f3f3f;

		for (int i = 0; i < n; ++i) {
			plen[i] = 0;
			scanf(" %s ", mp[i]);
		}

		for (int i = 0; i < m; ++i) {
			scanf(" %d ", flen + i);
			food[i] = 0;

			for (int j = 0; j < flen[i]; ++j) {
				scanf(" %s ", name);
				int k;
				for (k = 0; k < n; ++k) 
					if (strcmp(name, mp[k]) == 0) {
						food[i] |= (1LL<<k);
						people[k][plen[k]++] = i;
						break;
					}
			}
		}

		for (int i = 0; i < n; ++i) order[i] = i;
		for (int i = 1; i < n; ++i) {
			for (int k = 0; k < plen[i]; ++k) {
				int j = k;
				int temp = people[i][j];
				while (j && flen[people[i][j - 1]] < flen[people[i][j]]) {
					people[i][j] = people[i][j - 1], j--;
				}
				people[i][j] = temp;
			}
			int j = i;
			int temp = order[j];
			while (j&& plen[order[j - 1]] > plen[order[j]]) {
				order[j] = order[j - 1], j--;
			}
			order[j] = temp;
		}
		printf("%d\n", dfs(0, 0, 0));
	}

	return 0;
}


