#include <iostream>
#include<vector>
using namespace std;
int c;
int p;
vector<int> comm;
struct CARD {
	int num;
	CARD* prev;
	CARD* next;
	CARD() {
		prev = next = 0;
	}
};

CARD cards[1002];
int main() {
	cin >> c >> p;
	for (int i = 0; i < p; i++) {
		int in; 
		cin >> in;
		comm.push_back(in);
	}

	for (int i = 1; i <= c; i++) {
		cards[i].num = i;
		cards[i].prev = &cards[i - 1];
		cards[i].next = &cards[i + 1];
	}

	cards[1].prev = 0;
	cards[c].next = 0;

	CARD *first, *last;
	CARD* part[2];
	

	first = part[0] = &cards[1];
	last = part[1] = &cards[c];


	for (int i = 0; i < p; i++) {
		int size = c;
		int n = comm[i];
		part[0] = first;
		part[1] = last;

		while (size > 2 * n) {
			CARD* temp[4];
			temp[0] = part[0];
			temp[3] = part[1];

			temp[1] = temp[0];
			for (int i = 0; i < n; i++) {
				temp[1] = temp[1]->next;
			}

			temp[2] = temp[3];
			for (int i = 0; i < n; i++) {
				temp[2] = temp[2]->prev;
			}

			part[0] = temp[1];
			part[1] = temp[2];
			
			CARD *t[4] = { temp[1]->prev, temp[2]->next};

			temp[0]->prev = temp[2];
			temp[2]->next = temp[0];
			t[0]->next = t[1];
			t[1]->prev = t[0];
			
			size -= 2 * n;
			first = part[0];
			
		}
		CARD* head = first;

	}
	for (int i = 0; i < 5; i++) {
		cout << first->num << '\n';
		first = first->next;
	}
	return 0;
}