//https://www.acmicpc.net/problem/4195
#pragma once
#pragma once
#include<cstdio>

const int MAX = 400000;
typedef struct R {
	char *key;
	int value;
};

struct NODE {
	char key[21];
	int value;
	NODE* next;
	NODE* prev;
	NODE() {
		value = 0;
		prev = next = 0;
	}
} nodes[MAX];

struct MYAL {
	int size;
	void clear() {
		size = 0;
	}

	NODE* alloc() {
		return &nodes[size++];
	}
}al;


int strcmp(const char* c1, const char* c2) {
	int i = 0;
	while (c1[i] && c2[i] && (c1[i] == c2[i])) {
		i++;
	}

	return c1[i] - c2[i];
}

struct List {
	NODE *head, *tail, *cursor;
	List() {
		head = al.alloc();
		tail = al.alloc();
		head->next = tail;
		tail->prev = head;
	}

	void clear() {
		head = al.alloc();
		tail = al.alloc();
		head->next = tail;
		tail->prev = head;
	}

	void insert(const char* key, const int value) {
		NODE* nn = al.alloc();
		int i = 0;
		while (key[i]) {
			nn->key[i] = key[i];
			i++;
		}
		nn->key[i] = 0;
		nn->value = value;

		nn->next = tail;
		nn->prev = tail->prev;

		tail->prev->next = nn;
		tail->prev = nn;
	}

	void del() {
		if (cursor == head) return;

		cursor->prev->next = cursor->next;
		cursor->next->prev = cursor->prev;
		cursor = cursor->prev;

	}

	void init() {
		cursor = head;
	}

	R next() {
		if (cursor->next == tail) {
			return { 0,-1 };
		}

		cursor = cursor->next;
		return { cursor->key, cursor->value };
	}
};

int len;
int p[200000]; // -는 사이즈의 크기! +는 부모!
int conv[256] = { 0 }; 

struct Hash {
	const int size = 100000;
	List li[100000];

	int hash(const char *key) {
		int k = 0;
		while (*key) {
			k *= 52;
			k += conv[*key];
			k %= size;
			key++;
		}
		return k;
	}

	int find(const char * key) {
		R a;
		int k = hash(key);
		li[k].init();

		while ((a = li[k].next()).key) {
			if (strcmp(key, a.key) == 0) {
				return a.value;
			}
		};

		insert(key, len);
		int res = len++;

		return res;
	}

	void insert(const char* key, const int value) {
		int k = hash(key);
		li[k].insert(key, value);
	}

	void clear() {
		al.clear();

		for (int i = 0; i < size; i++) {
			li[i].clear();
		}
	}
}hash;

void swap(int& i1, int &i2) {
	int temp = i1;
	i1 = i2;
	i2 = temp;
}

int getParent(int i) {
	if (p[i] < 0) return i;

	return p[i] = getParent(p[i]);
}

int join(int i1, int i2) {
	int p1 = getParent(i1);
	int p2 = getParent(i2);

	if (p1 == p2) return -p[p1];
	else {
		if (p[p1] > p[p2]) {
			swap(p1, p2);
		}

		p[p1] += p[p2];
		p[p2] = p1;
		return -p[p1];
	}
}

int BackJoon4195() {
	char in[2][21];
	int t, m;
	int l = 0;
	for (int i = 'a'; i <= 'z'; i++) {
		conv[i] = l++;
	}

	for (int i = 'A'; i <= 'Z'; i++) {
		conv[i] = l++;
	}

	scanf("%d\n", &t);
	while (t--) {
		scanf("%d\n", &m);
		hash.clear();
		for (int i = 0; i < 2*m; i++) p[i] = -1; // 초기화
		len = 0;

		while (m--) {
			scanf("%s %s\n", in[0], in[1]);
			//해쉬를 통해 인덱스를 받는다.
			int i1 = hash.find(in[0]);
			int i2 = hash.find(in[1]);

			//disjoint 한다! 그리고 해당 크기를 반환받는다.
			int res = join(i1, i2);
			printf("%d\n", res);
		}
	}

	return 0;
}