#pragma once
#include<cstring>
#include<cstdio>

int sn, m;

char conv[256], str[31];
int cnts[30000][31];

struct TNODE {
	int end, num;
	TNODE* nodes[26];
	TNODE() {
		num = 0;
		end = -1;
		for (int i = 0; i < 26; i++) nodes[i] = NULL;
	}
} tnodes[900000];

struct MYAL {
	int i;
	const int SIZE = 900000;
	MYAL() {
		i = 0;
	}
	
	TNODE* alloc() {
		if (i == SIZE) return NULL;
		return &tnodes[i++];
	}

	void clear() {
		for (int j = 0; j < i; j++) {
			for (int k = 0; k < 26; k++) {
				tnodes[j].nodes[k] = 0;
			}
			tnodes[j].end = -1;
			tnodes[j].num = 0;
		}
		i = 0;
	}
}al;

struct TRIE {
	TNODE n;
	long long res, idx;

	long long find(const char* str) {
		res = 0;
		idx = -1;
		allFind(&n, str, 0);
		
		return res;
	}

	void insert(const char* str, int idx) {
		insert(&n, str, idx,0);
	}

	void insert(TNODE *n, const char* str, int idx, int depth) {
		if (*str == 0) {
			n->end = idx;
			cnts[idx][depth] = ++(n->num);
			
			return;
		}

		if (n->nodes[conv[*str]] == 0) {
			n->nodes[conv[*str]] = al.alloc();
		}

		cnts[idx][depth] = ++(n->num);

		insert(n->nodes[conv[*str]], str + 1, idx, depth + 1);
	}

	int allFind(TNODE* n, const char* str, int depth) {
		if (*str == 0) {
			idx = n->end;
			int ret = idx == -1 ? n->num : cnts[idx][depth];
			res = ret * (depth+1);

			return ret;
		}

		int sum = 0;
		sum = n->nodes[conv[*str]] ? allFind(n->nodes[conv[*str]], str + 1, depth + 1) : 0;
		int ret = idx == -1 ? n->num : cnts[idx][depth];

		res += (ret - sum)*(depth+1);
		return ret;
	}
	void clear() {
		for (int i = 0; i < 26; i++) {
			n.nodes[i] = NULL;
		}
		n.num = 0;
	}
} trie;

void init() {
	for (char i = 'a'; i <= 'z'; i++) {
		conv[i] = i - 'a';
	}
}

void set()
{
	scanf("%d\n", &sn);
	memset(cnts, 0, sizeof(cnts));

	trie.clear();
	al.clear();

	for (int i = 0; i < sn; i++) {
		scanf("%s\n", str);
		trie.insert(str, i);
	}

	scanf("%d\n", &m);
}

int hodongFindStr() {
	int t;
	scanf("%d\n", &t);
	
	init();
	
	for (int tc = 1; tc <= t; tc++) {
		set();
		long long res = 0, res2 = 0;
		
		while (m--) {
			scanf("%s\n", str);

			res += (long long)trie.find(str);
		}

		printf("#%d %lld\n", tc, res); 
	}
	return 0;
}