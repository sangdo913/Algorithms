//https://www.acmicpc.net/problem/1406
//BOJ 1406 ¿¡µðÅÍ
#pragma once
#include<iostream>

using namespace std;

struct NODE {
	char c;

	NODE *next, *prev;
	NODE() :c(0), next(0), prev(0) {}
}nodes[1000000];

struct MYAL {
	int idx;
	NODE* alloc() { return &nodes[idx++]; }
	MYAL() :idx(0) {}
}al;

struct List {
	NODE* head, *tail, *cursor;

	List() :head(al.alloc()), tail(al.alloc()), cursor(tail) {
		tail->prev = head;
		head->next = tail;
	}

	void insert(char a) {
		NODE* n = al.alloc();
		n->c = a;
		n->prev = cursor->prev;
		n->next = cursor;

		cursor->prev->next = n;
		cursor->prev = n;
	}

	void del() {
		if (cursor->prev == head) return;
		NODE* dnode = cursor->prev;
		dnode->prev->next = dnode->next;
		dnode->next->prev = dnode->prev;
	}
	void left() {
		if (cursor->prev == head) return;
		cursor = cursor->prev;
	}
	void right() {
		if (cursor->next == 0) return;
		cursor = cursor->next;
	}

	void print() {
		cursor = head;
		while (cursor->next != tail) {
			cursor = cursor->next;
			cout << cursor->c;
		}
	}
}li;

char in[100001];

int len(char *s) {
	int res = 0;
	while (*s) res++, s++;
	return res;
}

int BOJ1406() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> in;
	int l = len(in);

	for (int i = 0; i <l; i++) li.insert(in[i]);
	int n;

	cin >> n;

	while (n--) {
		char comm, c;
		cin >> comm;
		switch (comm) {

		case 'P':
			cin >> c;
			li.insert(c);
			break;
		case 'L':
			li.left();
			break;
		case 'D':
			li.right();
			break;
		case 'B':
			li.del(); break;
		}
	}

	li.print();
	return 0;
}