//https://www.acmicpc.net/problem/1600
//BOJ 1600 ¸»ÀÌ µÇ°íÇÂ ¿ø¼þÀÌ
#pragma once
#include<iostream>
#include<queue>

using namespace std;
int k, w, h;
int info[200][200];
int order[200][200], rcnt[200][200];

int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };
queue<COD> que;

struct COD {
	int r, c, k;
	COD() :r(0), c(0), k(0) {}
	COD(int r, int c, int k) :r(r), c(c), k(k) {}
};
int bfs() {
	COD now(1, 1, 0);
	rcnt[1][1] = 1;

	que.push(now);

	while (que.size()) {
		int cnt  
	}
}

int BOJ1600() {

	return 0;
}
