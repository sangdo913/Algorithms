//https://www.acmicpc.net/problem/5639
//BOJ 5639 이진 검색 트리
#pragma once
#include<iostream>

using namespace std;

struct NODE {
	int v;
	NODE *l, *r;
	NODE() :v(0), l(0), r(0) {}
}nodes[10000];

struct MYAL {
	int idx;
	MYAL() :idx(0) {}

	NODE* alloc() { return &nodes[idx++]; }
	void init() { idx = 0; }
}al;

struct BST {
	NODE dummy;
	NODE* root;
	BST() :root(&dummy) {}

	void init() { root->r = 0; }

	void insert(int num) {
		NODE* p, *c;
		p =0,  c = root;
			
		while (c) {
			p = c;
			if (c->v < num) { c = c->r; }
			else if(c->v > num){ c = c->l; }
			else return;
		}

		NODE*n = al.alloc();

		n->v = num;
		n->l = n->r = 0;

		if (num < p->v) p->l = n;
		else p->r = n;
	}

	void inorder() {
		NODE* start = root->r;
		inorder(start);
	}

	void inorder(NODE* node) {
		if (node == 0) return;
		inorder(node->l);
		inorder(node->r);
		cout << node->v << '\n';
	}
}bst;

int BOJ5639() {
	int n;
	while (cin >> n) {
		bst.insert(n);
	}

	bst.inorder();
	return 0;
}