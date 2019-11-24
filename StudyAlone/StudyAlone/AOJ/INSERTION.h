#include<stdio.h>

struct NODE {
	int lsize;
	int rsize;
	int priority;
	int v;
	NODE* l, *r;
}nodes[50002];

struct NODEPAIR {
	NODE *l,  *r;
};

NODE root;
NODE mynull;

#define RAND(x) ((((unsigned long long)(x) * 214013L + 2531011L))&0x7ffffff)

NODEPAIR split(NODE* node, int v) {
	if (node == &mynull) {
		return{ &mynull, &mynull };
	}

	NODEPAIR res;
	if (node->v < v) {
		res = split(node->r, v);
		node->r = res.l;
		node->rsize = node->r->lsize + node->r->rsize + 1;
		return { node, res.r };
	}
	else {
		res = split(node->l, v);
		node->l = res.r;
		node->lsize = node->l->lsize + node->l->rsize + 1;
		return { res.l, node };
	}
}

void insert(NODE* node, NODE* n) {
	NODE* p = 0, *now = node;
	while (now != &mynull && now->priority > n->priority) {
		p = now;
		if (now->v < n->v) { now->rsize++; now = now->r; }
		else now->lsize++, now = now->l;
	}
	NODEPAIR res = split(now, n->v);
	n->l = res.l, n->r = res.r;
	n->lsize = n->l->lsize + n->l->rsize + 1;
	n->rsize = n->r->lsize + n->r->rsize + 1;

	if (p->v > n->v) p->l = n;
	else p->r = n;
}

NODE* merge(NODE* a, NODE* b) {
	if (b == &mynull) return a;
	if (a == &mynull) return b;

	NODE* res;
	if (a->priority < b->priority) {
		res = b;
		res->l = merge(a, b->l);
		res->lsize = res->l->lsize + res->l->rsize + 1;
	}
	else {
		res = a;
		res->r = merge(a->r, b);
		res->rsize = res->r->lsize + res->r->rsize + 1;
	}
	return res;
}

void del(NODE *node, int v) {
	NODE* p, *now = node;
	while (now->v != v) {
		p = now;
		if (now->v < v) now->rsize--, now = now->r;
		else now->lsize--, now = now->l;
	}
	
	if (p->v < v) p->r = merge(now->l, now->r); 
	else p->l = merge(now->l, now->r);
}

int kth(NODE* node, int k) {
	while (true) {
		if (node->rsize > k) {
			node = node->r;
		}
		else {
			k -= node->rsize;
			if (!k--) {
				del(&root, node->v);
				return node->v;
			}
			node = node->l;
		}
	}
	return -1;
}

int A[50000];
int res[50000];

int main() {
	int tc;
	scanf("%d", &tc);
	tc = 100;
	root.priority = 0x3f3f3f3f;
	root.v = 0;
	mynull.lsize = -1;
	int rand = 5381;

	while (tc--) {
		int n;
		int nid = 0;
		root.l = root.r = &mynull;

		scanf("%d", &n);
		n = 50000;
		for (int i = 1; i <= n; ++i) {
			NODE &nn = nodes[nid++];
			nn.l = nn.r = &mynull;
			nn.rsize = nn.lsize = 0;
			rand = RAND(rand)%0x3f3f3f3f;
			nn.priority = rand;
			nn.v = i;
			insert(&root, &nn);
		}
		for (int i = 0; i < n; ++i) if(i)rand = RAND(rand), A[i] = rand%i;//scanf("%d", A + i);

		for (int i = n - 1; i >= 0; --i) {
			res[i] = kth(&root,A[i]);
		}
	//	for (int i = 0; i < n; ++i) printf("%d ", res[i]);
	//	printf("\n");
	}
	return 0;
}