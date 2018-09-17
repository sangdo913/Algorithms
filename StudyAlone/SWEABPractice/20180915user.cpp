//  해시_노래
//
//  Created by yeram Kim on 2018. 9. 15..

#include <iostream>
#include <stdlib.h>
#include<unordered_set>
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

struct NODE {
	int id;
	int pos;
	NODE *next;

	NODE() {
		next = 0;
	}
}nodes[2100000];


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
	NODE *head, *cursor;

	void insert(int id, int pos) {
		NODE *nn = al.alloc();
		nn->id = id;
		nn->pos = pos;
		nn->next = head->next;
		head->next = nn;
	}

	void init() {
		head = al.alloc();
	}

	void setcursor() {
		cursor = head;
	}
	
	NODE* next() {
		if (cursor->next) {
			return cursor->next;
		}
		else {
			return 0;
		}
	}
};

struct Hash {
	List hash[2000000];
	int hkey(int data[8]) {
		int key = 0;
		for (int i = 0; i < 7; i++) {
			key *= 512;
			key += data[i] - data[i + 1] + 256;
			key %= 2000000;
		}
		return key;
	}
	
	void insert(int data, int id, int pos) {
		data += 16000;

		for (int i = data - 128; i < data + 128; i++) {
			if (i < 0) continue;
			hash[data].insert(id, pos);
		}
	}

	void init() {
		for (int i = 0; i < 32001; i++) {
			hash->init();
		}
	}

	bool find(int data[8]) {

	}
};




typedef struct Song {
	int id;
	int leng;
	int data[200];       // 범위 : -16000~16000
};

// N : Song의 개수: 최대 10000개

void init(int N) {

}

void make_date_set(Song song) {

}

// song의 일부의 data[8]개가 들어왔을때 song의 id반환 (8개가 일치시 id는 유일함을 보장)
// 단 들어오는 data[8]은 noise값 -128~127값이 더해져서 들어온다.
int find_song(int data[8]) {


	return 0;
}
unordered_set<long long> mp;

int main() {

	register int i, j;
	Song songs[10000];
	int N = 10000;

	init(N);

	for (i = 0; i<10000; i++) {
		songs[i].id = i + 1;
		songs[i].leng = 200;
		bool complete = false;

		while (!complete) {
			complete = true;
			for (j = 0; j<200; j++) {
				songs[i].data[j] = rand() % 32001 - 16000;
			}
			long long h[192];
			int idx = 0;
			for (int l = 0; l <= 200 - 8; l++) {
				long long value = 0;
				for (int k = 0; k < 8; k++) {
					value += (songs[i].data[l + k] + 16000) * 32000;
					value %= 0x3fffffffffffffff;
				}
				h[idx++] = value;
			}
			for (int i = 0; i <= 192; i++) {
				if (mp.find(h[i]) != mp.end()) {
					complete = false;
					break;
				}
			}
			if (complete) {
				for (int i = 0; i <= 192; i++) {
					mp.insert(h[i]);
				}
			}
		}
		make_date_set(songs[i]);
	}

	int query_count = 1000;
	int solved = 0;
	for (i = 0; i<query_count; i++) {
		int n = rand() % 10000;
		int f = rand() % 200;
		int part[8];
		for (j = 0; j<8; j++) {
			int noise;
			noise = rand() % 256 - 128;
			part[j] = songs[n].data[(f + j)%200] + noise;
		}

		if (find_song(part) == n)
			solved++;

	}
	if (query_count == solved)
		printf("RIGHT");
	else printf("WRONG");

	return 0;
}