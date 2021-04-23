#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include"user.cpp"

#define MAX_N				10
#define MAX_ORDER			20000

extern void init(void);
extern void addCookieCutter(int mID, int N, int mShapeList[]);
extern void orderCookie(int mShape, int daysLeft);
extern int  checkRemain(int mShape);
extern void newDay(void);

/////////////////////////////////////////////////////////////////////////

static int mIDList[MAX_ORDER];
static int mIDCnt;

void makeCookies(int mID)
{
	if (mIDCnt >= MAX_ORDER)
		return;
	
	mIDList[mIDCnt++] = mID;
}

/////////////////////////////////////////////////////////////////////////

#define INIT           		0
#define ADD_COOKIECUTTER    1
#define ORDER_COOKIE  		2
#define CHECK_REMAIN   		3
#define NEW_DAY         	4

int tc;

static bool run()
{
	int mID;
	int N, mShapeList[MAX_N];
	int mShape, daysLeft;
	
	int Q;
	int cmd, ret = 0, ans;
	
	scanf("%d", &Q);
	
	bool okay = false;
	
	for (int i = 0; i < Q; ++i)
	{
		scanf("%d", &cmd);
		switch (cmd)
		{
		case INIT:
			init();
			okay = true;
			break;
		case ADD_COOKIECUTTER:
			scanf("%d %d", &mID, &N);
			for (int j = 0; j < N; ++j)
				scanf("%d", &mShapeList[j]);
			if (okay)
				addCookieCutter(mID, N, mShapeList);
			break;
		case ORDER_COOKIE:
			scanf("%d %d", &mShape, &daysLeft);
			if(tc == 21) {
				// printf("ORder shape: %d left:%d\n", mShape, daysLeft);
			}
			if (okay)
				orderCookie(mShape, daysLeft);
			break;
		case CHECK_REMAIN:
			scanf("%d", &mShape);
			// if(tc == 21) printf("Remain %d\n", mShape);
			if (okay)
				ret = checkRemain(mShape);
			scanf("%d", &ans);
			if (ret != ans)
				okay = false;
			break;
		case NEW_DAY:
			mIDCnt = 0;
			if (okay)
				newDay();
			scanf("%d", &ans);
			if (mIDCnt != ans)
				okay = false;
			for (int k = 0; k < ans; ++k)
			{
				int mID_a;
				scanf("%d", &mID_a);
				if (mIDList[k] != mID_a)
					okay = false;
			}
			break;
		default:
			okay = false;
		}
	}

	return okay;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("0Text.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}
	
	return 0;
}
