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
		//단어의 끝
		if (*str == 0) {
			n->end = idx; // 해당 단어의 끝이 있다
			cnts[idx][depth] = ++(n->num); //해당 문자열이 트라이의 몇번 째 방문자인지 삽입
			
			return;
		}

		// 없는 트라이면 새로 할당
		if (n->nodes[conv[*str]] == 0) {
			n->nodes[conv[*str]] = al.alloc();
		}

		cnts[idx][depth] = ++(n->num);

		insert(n->nodes[conv[*str]], str + 1, idx, depth + 1);
	}

	int allFind(TNODE* n, const char* str, int depth) {
		//단어의 끝
		if (*str == 0) {
			idx = n->end; //단어가 사전에 존재하면 해당 인덱스가 저장된다. 존재하지 않는다면 -1
			int ret = idx == -1 ? n->num : cnts[idx][depth]; // 존재하지 않으면, 처음부터 끝까지 모든 단어를 보면된다.
			res = ret * (depth+1);

			return ret; //처리된 문자열 개수이다.
		}

		int sum = 0;
		sum = n->nodes[conv[*str]] ? allFind(n->nodes[conv[*str]], str + 1, depth + 1) : 0; // 이미 처리된 단어 수를 반환받는다.
		int ret = idx == -1 ? n->num : cnts[idx][depth]; 									// 만약, 사전에 존재하지 않으면 처음부터 끝까지 모든 단어를 보고, 아니라면
																							// 해당 인덱스까지 몇 개의 단어가 존재하는지만 보면 된다.

		res += (ret - sum)*(depth+1); // 아직 처리 안된 단어들은 현재 처리할 수 있는 단어 - 이미 처리한 단어 수이다.
		return ret; //처리한 단어를 반환한다.
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