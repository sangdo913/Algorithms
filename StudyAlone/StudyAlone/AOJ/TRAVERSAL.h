#include<cstdio>
struct NODE {
	int num;
	int l, r;
}nodes[1001];
int nsize;

int n;
int preorder[1000];
int inorder[1000];
int pos[1001];
int cnt;

void makeTree(int l, int r) {
	if (r < l) return ;
	if (l < 0) return ;
	if (r == n) return ;

	int num = preorder[cnt++];
	int idx = pos[num];

	makeTree(l, idx-1);
	makeTree(idx + 1,r);
	printf("%d ", num);
	return ;
}

int main() {
	int tc;
	scanf("%d", &tc);
	while (tc--) {
		nsize = 0;
		cnt = 0;

		scanf("%d", &n);

		for (int i = 0; i < n; ++i) scanf("%d", preorder + i);
		for (int i = 0; i < n; ++i) {
			scanf("%d", inorder + i);
			pos[inorder[i]] = i;
		}

		makeTree(0, n - 1);
		printf("\n");
	}
	return 0;
}