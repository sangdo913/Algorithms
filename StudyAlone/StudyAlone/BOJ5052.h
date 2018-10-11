//https://www.acmicpc.net/problem/5052 
//BOJ 5052 전화번호 목록
#pragma once
#include<iostream>

using namespace std;
int n;

int len(char *str) {
	int res = 0;
	while (*str) str++, res++;
	return res;
}

void cpy(char* d, char*f, int l) {
	for (int i = 0; i < l; i++) {
		d[i] = f[i];
	}
}

int cmp(char* s1, char* s2) {
	while (*s1 == *s2 && *s1 && *s2) s1++, s2++;
	return *s1 - *s2;
}

struct TNODE {
	char c;
	bool end;
	TNODE* next[10];
	TNODE() : c(0), end(false) {}
} nodes[1000000];

struct MYAL {
	int idx = 0;
	MYAL() :idx(0) {}

	TNODE* alloc() {
		return &nodes[idx++];
	}
	void init() {
		idx = 0;
	}
}al;

struct Trie {
	TNODE *root;

	bool insert(char* str) {
		return insert(root, str);
	}
	bool insert(TNODE* node, char* s) {
		if (*(s) == 0) {
			for (int i = 0; i < 10; i++) {
				if (node->next[i]) return false;
			}
			node->end = true;
			return true;
		}

		if (node->end) return false;
		
		if (node->next[*s - '0'] == 0) {
			TNODE* n = al.alloc();
			n->c = *s;
			n->end = false;
			for (int i = 0; i < 10; i++) {
				n->next[i] = 0;
			}
			node->next[*s - '0'] = n;
		}

		return insert(node->next[*s - '0'], s + 1);
	}
	Trie() : root(al.alloc()) {}
	
	void init() {
		root = al.alloc();
		for (int i = 0; i < 10; i++) {
			root->next[i] = 0;
		}
		root->end = false;
	}
	
}trie;
char str[11];

int BOJ5052() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int t;
	cin >> t;

	while (t--) {
		al.init();
		trie.init();
		cin >> n;

		bool ok = true;
		while (n--) {
			cin >> str;
			
			if (ok && trie.insert(str) == false) {
				ok = false;
			}
		}
		cout << (ok ? "YES\n": "NO\n");
		int i = 0;
	}
	return 0;
}
