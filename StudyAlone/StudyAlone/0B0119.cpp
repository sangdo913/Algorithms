#include<stdio.h>
#include<stdlib.h>
#include"0user.h"
#define ADDQUERY 45
#define REMOVEQUERY 50
#define SEARCH1QUERY 90

static int radius[5050];
static int N, query, seed;

static int mrand(int num)
{
	seed = seed * 1103515245 + 37209;
	if (seed < 0) seed *= -1;
	return ((seed >> 8) % num);
}

extern void init(int N);
extern void add(int mId, int mType, int y, int x);
extern void remove(int mId);
extern int search1(int mType, int mY, int mX, int radius);
extern int search2(int mType, int mY, int mX, int mlist[5]);

int run(){
	scanf("%d %d %d\n", &N, &query, &seed);

	int cmd = mrand(100);
	int mlist[5] = {};
	int mId = 0, mX, mY, mType, K = 0, r, answer, user_answer, score = 100, answer_list;

	if (N < 100){
		K = 0;

		while (radius[K] < N){
			K += radius[K];
		}
	}

	else{
		K = 5050;
	}

    init(N);
    
	while (query--){
		if (cmd < ADDQUERY){
			mType = mrand(10) + 1;
			mX = mrand(N);
			mY = mrand(N);
			add(++mId, mType, mY, mX);
		}

		else if (cmd < REMOVEQUERY){
			mType = mrand(10) + 1;
			remove(mType);
		}

		else if (cmd < SEARCH1QUERY){
			mType = mrand(11);
			mX = mrand(N);
			mY = mrand(N);
			r = mrand(K);
			user_answer = search1(mType, mY, mX, radius[r]);

			scanf("%d", &answer);

			if (user_answer != answer) {
				score = 0;
			}
		}

		else {
			mType = mrand(10) + 1;
			mX = mrand(N);
			mY = mrand(N);

			user_answer = search2(mType, mY, mX, mlist);

			scanf("%d\n", &answer);

			if (user_answer != answer){
				score = 0;
			}

			else{
				for (int i = 0; i < answer; ++i){
					scanf("%d\n", &answer_list);
					if (answer_list != mlist[i]) score = 0;
				}
			}
		}
	}

	return score;
}

int main(){
	int tc;
	scanf("%d", &tc);
	freopen("/Users/sangdolee/Desktop/Algorithm/StudyAlone/StudyAlone/0Text.txt", "r", stdin);
	
	int v = 1;
	int totalscore = 0;
	for (int i = 0; i < 5050; i++){
		int j = 0;
		for (j = 0; j < v; j++){
			radius[i + j] = v;
		}
		v++;
		i += j-1;
	}

	for (int t = 1; t <= tc; t++){
		int score = run();
		printf("#%d score : %d\n", t, score);
		totalscore += score;
	}
	printf("totalscore : %d\n", totalscore);
}