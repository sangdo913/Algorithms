//https://www.acmicpc.net/problem/1620
//BOJ1620 나는야 포켓몬 마스터 이다솜
#pragma once
#include<iostream>

using namespace std;
typedef char NAME[21];

struct NODE {
	int num;
	NAME name;
	NODE *left, *right, *p;
	NODE() : num(0), left(0), right(0) {};
}nodes[1100000];

struct LNODE {
	int num;
	NAME name;
	LNODE* next;
	LNODE() : num(0), next(0) {}
}lnodes[1000000];


struct MYAL {
	int idx;
	MYAL() :idx(0) {}

	NODE* alloc() {
		return &nodes[idx++];
	}
	LNODE* lloc() {
		return &lnodes[idx++];
	}

}al;

int len(char* name) {
	int res = 0;
	while (*name) res++, name++;
	return res;
}
int cmp(char* s1, char* s2) {
	while (*s1 && *s2 && *s1 == *s2) s1++, s2++;
	return *s1 - *s2;
}

void cpy(char*s1, char*s2, int l) {
	for (int i = 0; i < l; i++) {
		s1[i] = s2[i];
	}
}

struct BST {
	NODE *root;

	BST() :root(al.alloc()) {}

	void insert(int i, NAME name) {
		insert(root, i, name);

	}
	void insert(NODE* node, int i, NAME name) {
		int comp = cmp(name, node->name);
		if (comp > 0) {
			if (node->right) insert(node->right, i, name);
			else {
				NODE* n = al.alloc();
				cpy(n->name, name, len(name));
				n->num = i;
				n->p = node;
				node->right = n;
			}
		}
		else if (comp < 0) {
			if (node->left) insert(node->left, i, name);
			else {
				NODE* n = al.alloc();
				cpy(n->name, name, len(name));
				n->num = i;
				n->p = node;
				node->left = n;
			}
		}
	}

	int find(NAME i) {
		return find(root, i);
	}
	int find(NODE* node, NAME i) {
		int comp = cmp(i, node->name);
		if (comp > 0) {
			return find(node->right, i);
		}
		else if (comp < 0) return find(node->left, i);
		else {
			return node->num;
		}
	}
}bst;

int atoi(char*s) {
	int res = 0;
	while (*s) {
		res *= 10;
		res += *s - '0';
		s++;
	}
	return res;
}

struct List {
	LNODE* head, *tail;
	List() : head(al.lloc()), tail(al.lloc()) {
		head->next = tail;
	}

	void insert(int i, NAME name) {
		LNODE* n = al.lloc();
		cpy(n->name, name, len(name));
		n->num = i;
		n->next = head->next;
		head->next = n;
	}

	int find(NAME name) {
		LNODE* cursor = head->next;
		while (cursor != tail) {
			if (cmp(name, cursor->name) == 0) {
				return cursor->num;
			}
			cursor = cursor->next;
		}
		return -1;
	}

};

int conv[256];

struct HASH {
	List li[200003];

	int key(NAME name) {
		int l = len(name);
		int res = 0;
		for (int i = 0; i < l; i++) {
			res *= 52;
			res += conv[name[i]];
			res %= 200003;
		}
		return res;
	}

	void insert(int i, NAME name) {
		int k = key(name);
		li[k].insert(i, name);
	}

	int find(NAME name) {
		int k = key(name);
		return li[k].find(name);
	}

}myhash;

NAME names[300000];

int BOJ1620() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	int flag = 0;
	for (int i = 'A'; i <= 'Z'; i++) conv[i] = flag++;
	for (int i = 'a'; i <= 'z'; i++) conv[i] = flag++;

	for (int i = 1; i <= n; i++) {
		cin >> names[i];
		myhash.insert(i, names[i]);
	}
	while (m--) {
		NAME query;
		cin >> query;
		if (query[0] >= '0' && query[0] <= '9') {
			int num = atoi(query);
			cout << names[num] << '\n';
		}
		else {
			cout << myhash.find(query) << '\n';
		}
	}

	return 0;
}
