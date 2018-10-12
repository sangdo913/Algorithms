//https://www.acmicpc.net/problem/2866
//BOJ 2866 문자열 잘라내기

#include<iostream>

using namespace std;

typedef char NAME[1001];

int len(char* s) {
	int res = 0;
	while(*s) res++, s++;
	return res;
}

void cpy(char* d, char*f, int l) {
	for (int i = 0; i <= l; i++) {
		d[i] = f[i];
	}
}

bool cmp(char* s1, char*s2) {
	while (*s1 && *s2 && *s1 == *s2) s1++, s2++;
	return *s1 == *s2;
}

struct NODE {
	NAME name;
	NODE *next, *prev;
	NODE() : next(0), prev(0) {}
}nodes[50000];

struct MYAL {
int idx = 0;
MYAL() :idx(0) {}

NODE* alloc() { return &nodes[idx++]; }
void init() { idx = 0; }
}al;

struct List {
	NODE *head, *tail;
	List() :head(al.alloc()), tail(al.alloc()) {
		head->next = tail;
		tail->prev = head;
	}

	void init() {
		head = al.alloc();
		tail = al.alloc();
		head->next = tail;
		tail->prev = head;
	}

	void insert(NAME name) {
		NODE* n = al.alloc();

		cpy(n->name, name, len(name));

		n->name[len(name)] = 0;

		n->prev = tail->prev;
		n->next = tail;

		tail->prev->next = n;
		tail->prev = n;
	}

	bool find(NAME name) {
		NODE* cursor = head;

		while (cursor->next != tail) {
			cursor = cursor->next;
			if (cmp(cursor->name, name)) return true;
		}
		return false;
	}
};

struct HASH {
	List li[1003];

	int key(NAME name) {
		int res = 0;

		while (*name) {
			res <<= 1;
			res += *name - 'a';
			res %= 1003;
			name++;
		}
		return res;
	}

	void insert(NAME name) {
		int k = key(name);

		li[k].insert(name);
	}
	bool find(NAME name) {
		int k = key(name);

		return li[k].find(name);
	}

	void init() {
		for (int i = 0; i < 1003; i++) { li[i].init(); }
	}
}myhash;

NAME names[1000];
char s[1000][1001];
char temp[1000];

int MIN(int i1, int i2) { return i1 < i2 ? i1 : i2; }

int r, c;
bool parametric(int len) {
	al.init();
	myhash.init();
	for (int i = 0; i < c; i++) temp[i] = names[i][len];

	for (int j = 0; j < c; j++) {
		temp[j] = names[j][len];
		names[j][len] = 0;
		if (myhash.find(names[j])) {
			for (int i = 0; i < c; i++) names[i][len] = temp[i];
			return false;
		}
		else myhash.insert(names[j]);
	}

	for (int i = 0; i < c; i++) names[i][len] = temp[i];
	return true;
}

int bs(int l,int r) {

	while (l <= r) {
		int m = (l + r) / 2;

		if (parametric(m)) {
			r = m - 1;
		}
		else {
			l = m + 1;
		}
	}
	return r + 1;

}

int BOJ2866() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> r >> c;

	for (int i = 0; i < r; i++) {
		cin >> s[i];
	}

	int l = 0;
	for (int i = r - 1; i > 0; i--) {
		for (int j = 0; j < c; j++) {
			names[j][l] = s[i][j];
		}
		l++;
	}

	int res = r - bs(1, r - 1);
	cout << res;
	return 0;
}