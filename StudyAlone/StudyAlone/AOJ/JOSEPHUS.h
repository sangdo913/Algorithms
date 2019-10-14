#include<stdio.h>

struct NODE{
	int i;
	NODE *prev, *next;
}nodes[1000];

int nidx;
int n, k;

int main() {
	int tc;
	scanf("%d", &tc);

	for (int i = 0; i < 1000; ++i) nodes[i].i = i + 1;

	while (tc--) {
		scanf("%d %d", &n, &k);

		nidx = 0;
		int cnt;
		NODE* cursor = nodes;
		nodes[0].prev = nodes[0].next = nodes;
		nodes[0].i = 1;
		nidx = 1;
		cnt = n;

		for (int i = 1; i < n; ++i) {
			NODE &nn = nodes[nidx++];
			nn.prev = cursor->prev;
			nn.next = cursor;

			cursor->prev = cursor->prev->next = &nn;
		}

		while (cnt != 2) {
			cursor->prev->next = cursor->next;
			cursor->next->prev = cursor->prev;
			int j = k;
			while(j--) cursor = cursor->next;
			cnt--;
		}
		int r1 = cursor->i;
		int r2 = cursor->next->i;
		if (r1 > r2) r1 ^= r2 ^= r1 ^= r2;
		printf("%d %d\n", r1, r2);
	}
	return 0;
}