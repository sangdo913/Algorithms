#include<stdio.h>

char str[10000][12];
int nums[10000];
int conv[128];
struct TRIE {
	int strid;
	int max;
	TRIE* child[26];
}nodes[110000];
int nid;
int n, m;

TRIE root;

int mystrcmp(char *a, char *b) {
	while (*a && *a == *b) ++a, ++b;
	return *a - *b;
}

void insert(TRIE* r, int i) {
	int cnt = 0;
	int m = nums[i];
	while (str[i][cnt]) {
		if (!r->child[conv[str[i][cnt]]]) {
			TRIE* nn = &nodes[nid++];
			for (int i = 0; i < 26; ++i) nn->child[i] = 0;
			nn->max = -100;
			r->child[conv[str[i][cnt]]] = nn;
		}
		r = r->child[conv[str[i][cnt]]];
		if (r->max < m) {
			r->strid = i;
			r->max = m;
		}
		else if (r->max == m && mystrcmp(str[i], str[r->strid]) < 0) {
			r->strid = i;
		}
		cnt++;
	}
}

int mystrlen(char *in) {
	int res = 0;
	while (*in) res++,in++;
	return res;
}

int getcnt(char *in) {
	TRIE *r = &root;
	int cnt = 0;
	while (in[cnt]) {
		if (r->child[conv[in[cnt]]] == 0) return 0x3f3f3f3f;
		r = r->child[conv[in[cnt]]];
		if (mystrcmp(str[r->strid], in) == 0) { return cnt + 2; }
		cnt++;
	}
	return cnt;
}

int main() {
	int tc;
	scanf("%d", &tc);
	int cnt = 0;
	char in[10000];
	for (int i = 'A'; i <= 'Z'; ++i) conv[i] = cnt++;
	while (tc--) {
		nid = 0;
		scanf("%d %d", &n, &m);
		for (int i = 0; i < 26; ++i) root.child[i] = 0;

		for (int i = 0; i < n; ++i) {

			scanf("%s %d", str[i], &nums[i]);
			insert(&root, i);
		}

		int res = 0;
		for (int i = 0; i < m; ++i) {
			scanf("%s ", in);
			int ret = getcnt(in);
			int len = mystrlen(in);
			res += ret >len ? len : ret;
		}
		res += m - 1;
		printf("%d\n", res);
	}
	return 0;
}

