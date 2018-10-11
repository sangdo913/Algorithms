//https://www.acmicpc.net/problem/5446
//BOJ 5446 용량 부족
#pragma once
#include<iostream>

using namespace std;

struct NODE {
	char c;
	bool no;
	bool end;
	bool notend;
	NODE* next[63];
	NODE() :c(0), no(false) {}
}nodes[70000];
int conv[256];

struct MYAL {
	int idx;
	MYAL() :idx(0) {}

	void init() {
		idx = 0;
	}
	NODE* alloc() {
		return &nodes[idx++];
	}
}al;

struct TRIE {
	NODE* root;
	void init() {
		root = al.alloc();
		for (int i = 0; i < 63; i++) root->next[i] = 0;
		root->no = false;
		root->notend = false;
		root->end = false;
	}

	void insert(char* str) {
		insert(root, str);
	}
	void insert(NODE* node, char*s) {
		if (*s == 0) {
			node->end = true;
			return;
		}

		if (node->next[conv[*s]] == 0) {
			NODE* n = al.alloc();
			n->c = *s;
			n->no = false;
			n->end = false;
			n->notend = false;
			for (int i = 0; i < 63; i++) {
				n->next[i] = 0;
			}
			node->next[conv[*s]] = n;
		}
		insert(node->next[conv[*s]], s + 1);
	}

	void setNot(char*s) {
		setNot(root, s);
	}

	void setNot(NODE* node, char* s) {
		node->no = true;
		if (*s == 0) {
			node->notend = true;
			return;
		}
		
		if (node->next[conv[*s]]) {
			setNot(node->next[conv[*s]], s + 1);
		}
	}
	int getCount() {
		if (root->no == false) return 1;
		return getCount(root);
	}

	int getCount(NODE *node) {
		int res = node->end && !node->notend;

		for (int i = 0; i < 63; i++) {
			if (node->next[i] && node->next[i]->no) {
				res += getCount(node->next[i]);
			}
			else if (node->next[i]) res++;
		}
		return res;
	}

}trie;

int BOJ5446() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int flag = 0;
	for (int i = 'a'; i <= 'z'; i++) {
		conv[i] = flag++;
	}
	for (int i = 'A'; i <= 'Z'; i++) {
		conv[i] = flag++;
	}
	for (int i = '0'; i <= '9'; i++) {
		conv[i] = flag++;
	}
	conv['.'] = flag++;

	int t;
	cin >> t;
	while (t--) {
		al.init();
		trie.init();

		int n;
		cin >> n;
		char s[21];
		while (n--) {
			cin >> s;
			trie.insert(s);
		}
		int m;
		cin >> m;
		while (m--) {
			cin >> s;
			trie.setNot(s);
		}

		cout << trie.getCount() << '\n';
	}
	return 0;
}
