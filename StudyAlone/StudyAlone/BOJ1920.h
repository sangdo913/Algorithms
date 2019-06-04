#include<iostream>
#define HASHTABLE 200013 

using namespace std;

struct NODE {
	int i;
	NODE *next;
}nodes[HASHTABLE];

NODE nd[100000];
int idx = 0;

NODE dummy;
int n, m;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	for (int i = 0; i < HASHTABLE; ++i) {
		nodes[i].next = &dummy;
	}

	cin >> n;
	int idx = 0;
	while (n--) {
		int in;
		cin >> in;
		int key = in % HASHTABLE;
		if (key < 0) key += HASHTABLE;
		nd[idx].i = in;
		nd[idx].next = nodes[key].next;
		nodes[key].next = &nd[idx];
		idx++;
	}

	cin >> m;
	while (m--) {
		int in;
		cin >> in;
		int key = in % HASHTABLE;
		if (key < 0) key += HASHTABLE;
		NODE *cur = nodes[key].next;
	
		while (cur != &dummy) {
			if (cur->i == in) {
				printf("1\n");
				goto END;
			}
			cur = cur->next;
		}
		printf("0\n");
	END:
		continue;
	}
	return 0;
}