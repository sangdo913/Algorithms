//  ????_????
//
//  Created by yeram Kim on 2018. 9. 15..

#include <iostream>
#include <stdlib.h>
#include<unordered_set>
/**
���� ���� :
�뷡���� ������ �ִ� int �� data 200���� �������ִ�.
����� �� �뷡�� �Ϻ� ��ȣ8���� ��ǲ���� �޾� �뷡�� id�� ã�´�.
1. �뷡�� �ִ� 10000���� ���´�.
2. �뷡�� �ִ� data�� 200���̴�.
3. �� �뷡�� data��ȣ�� ������ -16000~16000�̴�.
4. find_song�� input �� 8���� arr�� ���� �������� ������ -128~127�̴�.
5. ������ �������� �����ϴ� 8���� input�� �����ϴ� �뷡�� id�� �������� ����ȴ�.
6. �ԷµǴ� data�� �������̴�.
**/

using namespace std;

const int flag = 32000 / 300;


typedef struct Song {
	int id;
	int leng;
	int data[200];       // ���� : -16000~16000
};
Song songs[10000];
struct NODE {
	int id;
	int pos;
	NODE *next;

	NODE() {
		next = 0;
	}
}nodes[10000000];
Song my[10001];

struct Myal {
	int idx;

	NODE* alloc() {
		return &nodes[idx++];
	}
	void init() {
		idx = 0;
	}
}al;

struct List {
	int size;
	NODE *head, *cursor;

	void insert(int id, int pos) {
		NODE *nn = al.alloc();
		nn->id = id;
		nn->pos = pos;
		nn->next = head->next;
		head->next = nn;
		size++;
	}

	void init() {
		size = 0;
		head = al.alloc();
		head->next = 0;
	}

	void setcursor() {
		cursor = head;
	}

	NODE* next() {
		if (cursor->next) {
			cursor = cursor->next;
			return cursor;
		}
		else {
			return 0;
		}
	}
};

int keys[200];

bool check(int id, int pos, int data[8]) {
	int *comp = my[id].data + pos;

	for (int i = 0; i < 8; i++) {
		int noise = data[i] - comp[i];
		if (noise < -128 || noise > 127) {
			return false;
		}
	}
	return true;
}

struct Hash {

	List hash[2000000];
	int hkey(int data[8]) {
		long long key = 0;
		for (int i = 0; i < 7; i++) {
			key *= 512;
			key += (data[i] - data[i + 1] + 255)/512;
			key+= 512;
			key %= 2000000;
		}
		return (int)key;
	}

	void insert(int data[200],int len, int id) {
		int kcnt = 0;
		for (int i = 0; i <= len - 8; i++) {
			int key = hkey(data+i);
			keys[kcnt++] = key;
			//data += 16000;
			hash[key].insert(id, i);
		}
	}

	void init() {
		for (int i = 0; i < 2000000; i++) {
			hash[i].init();
		}
	}

	int find(int data[8]) {
		int key = hkey(data);
		printf("Find : %d\n", key);
		hash[key].setcursor();
		NODE* n;
		while ((n = hash[key].next())) {
			int id = n->id;
			int pos = n->pos;

			bool res = check(id, pos, data);
			if (res) return id;
		}
		/*for (int i = -127; i <= 128; i++)
		{
			int key = data[0] + i + 16000;
			if (key < 0) continue;
			else if (key > 32000) continue;

			hash[key].setcursor();

			NODE* n;
			while ((n = hash[key].next())) {
				int id = n->id;
				int pos = n->pos;

				bool res = check(id, pos, data);
				if (res) return id;
			}
		}*/
		return -1;
	}
}HA;

// N : Song�� ����: �ִ� 10000��

void init(int N) {
	al.init();
	HA.init();
}

void make_date_set(Song song) {
	my[song.id] = song;
	//for (int i = 0; i <= song.leng - 8; i++)
	//{
	//	HA.insert(song.data[i],song.id, i);
	//}
		HA.insert(song.data,song.leng,song.id);
	
}

// song�� �Ϻ��� data[8]���� �������� song�� id��ȯ (8���� ��ġ�� id�� �������� ����)
// �� ������ data[8]�� noise�� -128~127���� �������� ���´�.
int find_song(int data[8]) {

	return HA.find(data);
}
unordered_set<long long> mp;

#include<time.h>
int main() {
	int T = 100, LEN = 200, QUERY = 10;
	int N = 1;
	int seed = time(0);
		long long mval = 0;
		const long long MOD = 10987654321;
		for (int i = 0; i < 8; i++) {
			mval *= 32000;
			mval %= MOD;
		}
	while (T--)
	{
		seed *= seed;
		seed %= 0x3f3f3f3f;

		srand(seed);
		 int i, j;
		init(N);


		for (i = 0; i < N; i++) {
			songs[i].id = i + 1;
			songs[i].leng = LEN;
			bool complete = true;

			for (j = 0; j < LEN; j++) {
				songs[i].data[j] = rand() % 32001 - 16000;
			}
			//////�ߺ�Ȯ��
			//while (!complete) {
			//	complete = true;
			//	long long h[200] = { 0 };
			//	int idx = 0;
			//	for (int k = 0; k < 8; k++) {
			//		h[0] *= 32000;
			//		h[0] %= MOD;
			//		h[0] += songs[i].data[k];
			//	}
			//	idx++;
			//	for (int l = 8; l < songs[i].leng; l++) {

			//		h[idx] = (h[0] + MOD - (songs[i].data[l - 1] * mval) % MOD) % MOD;
			//		h[idx] *= 32000;
			//		h[idx] %= MOD;
			//		h[idx] += songs[i].data[l];
			//		h[idx] %= MOD;
			//		idx++;
			//	}
			//	for (int k = 0; k < idx; k++) {
			//		if (mp.find(h[k]) != mp.end()) {
			//			//complete = false;
			//			break;
			//		}
			//	}
			//	if (complete) {
			//		for (int i = 0; i < idx; i++) {
			//			mp.insert(h[i]);
			//		}
			//	}
			//}

			make_date_set(songs[i]);
		}

		int query_count = QUERY;
		int solved = 0;
		for (i = 0; i < query_count; i++) {
			int n = rand() % N;
			int f = rand() % (LEN - 7);
			int part[8];
			for (j = 0; j < 8; j++) {
				int noise;
				noise = rand() % 256 - 128;
				part[j] = songs[n].data[(f + j)] + noise;
			}

			printf("first : %d\n", HA.hkey(part));

			for (int i = 0; i < 7; i++) {
				int diff = (part[i] - part[i + 1]) + 255;
				diff /= 512;
				printf("%d ", diff);
			}
			printf("\n");

			printf("find1 : %d\n", keys[f]);
			Song & a = songs[n];
			for (int i = 0; i < 7; i++) {
				int diff = a.data[i + f] - a.data[i + f + 1] + 255;
				diff /= 512;
				printf("%d ", diff);
			}
			printf("\n\n");
			int fid = find_song(part);

			if (fid == songs[n].id)
				solved++;

		}
		if (query_count == solved)
			printf("RIGHT\n");
		else printf("WRONG");
	}
	return 0;
}