//  해시_노래
//
//  Created by yeram Kim on 2018. 9. 15..

#include <iostream>
#include <stdlib.h>
/**
문제 개요 :
노래들은 각각의 최대 int 형 data 200개를 가지고있다.
노이즈가 낀 노래의 일부 신호8개를 인풋으로 받아 노래의 id를 찾는다.
1. 노래는 최대 10000개가 들어온다.
2. 노래의 최대 data는 200개이다.
3. 각 노래의 data신호의 범위는 -16000~16000이다.
4. find_song의 input 인 8개의 arr에 끼는 노이즈의 범위는 -128~127이다.
5. 노이즈 범위까지 포함하는 8개의 input에 대응하는 노래의 id는 유일함이 보장된다.
6. 입력되는 data는 연속적이다.
**/

using namespace std;

typedef struct Song {
	int id;
	int leng;
	int data[200];       // 범위 : -16000~16000
};
Song songs[10000];
struct NODE {
	int id;
	int pos;
	NODE *next;

	NODE() {
		next = 0;
	}
}nodes[6100000];
Song my[10001];

NODE heads[1000060];
struct Myal {
	int idx;

	NODE* alloc() {
		return &nodes[idx++];
	}
	void init() {
		idx = 0;
	}
}al;
static int cnt = 0;
struct List {
	NODE *head, *cursor;

	void insert(int id, int pos) {
		NODE *nn = al.alloc();
		nn->id = id;
		nn->pos = pos;
		nn->next = head->next;
		head->next = nn;
	}

	List() {
		head = &heads[cnt++];
	}

	void init() {
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
	List hash[1000000];
	int hkey(const int data[2], int flag) {
		// 첫번째 데이터와 첫번째 데이터와 두번째 데이터의 차이로 해싱
		long long key = data[0] + 16000;
		key *= 512;
		int diff = data[0] - data[1] + 32000 + flag;
		diff /= 512;
		key += diff;
		key %= 1000000;

		return (int)key;
	}

	void insert(int data[200], int len, int id) {
		int kcnt = 0;
		for (int i = 0; i <= len - 8; i++) {
			int key = hkey(data + i, 0);

			hash[key].insert(id, i);
			hash[(key + 1) % 1000000].insert(id, i);
		}
	}

	void init() {
		for (int i = 0; i < 1000000; i++) {
			hash[i].init();
		}
	}

	int find(int data[8]) {
		for (register int i = -127; i <= 128; i++)
		{
			int nd = data[0] + i;
			if (nd < -16000) continue;
			int dat[2] = { nd, data[1] };
			int key = hkey(dat, 255);

			hash[key].setcursor();

			NODE* n;
			while ((n = hash[key].next())) {
				int id = n->id;
				int pos = n->pos;

				bool res = check(id, pos, data);
				if (res) return id;
			}
		}
		return -1;
	}
}HA;

// N : Song의 개수: 최대 10000개

void init(int N) {
	al.init();
	HA.init();
}

void make_date_set(Song& song) {
	my[song.id] = song;
	HA.insert(song.data, song.leng, song.id);
}

// song의 일부의 data[8]개가 들어왔을때 song의 id반환 (8개가 일치시 id는 유일함을 보장)
// 단 들어오는 data[8]은 noise값 -128~127값이 더해져서 들어온다.
int find_song(int data[8]) {

	return HA.find(data);
}

#include<time.h>
int main() {
	int T = 50, LEN = 200, QUERY = 10000;
	int N = 10000;

	int seed = time(0);

	while (T--)
	{
		seed *= seed;
		seed %= 0x3f3f3f3f;

		srand(seed);
		register int i, j;
		init(N);

		for (i = 0; i < N; i++) {
			songs[i].id = i + 1;
			songs[i].leng = LEN;
			bool complete = true;

			for (j = 0; j < LEN; j++) {
				songs[i].data[j] = rand() % 32001 - 16000;
			}

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

			int fid = find_song(part);

			if (fid == songs[n].id)
				solved++;
		}
		if (query_count == solved)
			printf("RIGHT\n");
		else printf("WRONG\n");
	}
	return 0;
}