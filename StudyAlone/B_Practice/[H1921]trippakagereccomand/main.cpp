#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include"user.cpp"

extern void init(int N, int M);
extern void befriend(int uid1, int uid2);
extern void add(int pid, int area, int price);
extern void reserve(int uid, int pid);
extern int  recommend(int uid);

#define INIT			100
#define BEFRIEND		200
#define ADD				300
#define RESERVE			400
#define RECOMMEND		500

static bool run()
{
	int L, N, M;
	bool okay = false;
	
	int pid, uid;
	int uid1, uid2;
	int area, price;
	
	int ans;
	int cmd, ret;

	scanf("%d", &L);

	for (int l = 0; l < L; ++l)
	{
		scanf("%d", &cmd);
		switch(cmd)
		{
		case INIT:
			//printf("INIT\n");
			scanf("%d %d", &N, &M);
			init(N, M);
			okay = true;
			break;
		case BEFRIEND:
			//printf("BEFRIEND\n");
			scanf("%d %d", &uid1, &uid2);
			befriend(uid1, uid2);
			break;
		case ADD:
			//printf("ADD\n");
			scanf("%d %d %d", &pid, &area, &price);
			add(pid, area, price);
			break;
		case RESERVE:
			//printf("RESERV\n");
			scanf("%d %d", &uid, &pid);
			reserve(uid, pid);
			break;
		case RECOMMEND:
			//printf("RECOMMEND\n");
			scanf("%d %d", &uid, &ans);
			ret = recommend(uid);
			if (ret != ans)
				okay = false;
			break;
		}
	}
	
	return okay;
}

int main() {
	int TC, MARK;
	
    freopen("0Text.txt", "r", stdin);

	setbuf(stdout, NULL);
    scanf("%d %d", &TC, &MARK);

    for (int testcase = 1; testcase <= TC; ++testcase) {
		int score = run() ? MARK : 0;
		printf("#%d %d\n", testcase, score);
    }

    return 0;
}