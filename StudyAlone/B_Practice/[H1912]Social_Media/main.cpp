#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>
#include"user.cpp"

extern void init(int N);
extern void follow(int uId1, int uId2, int timestamp);
extern void makePost(int uId, int pId, int timestamp);
extern void like(int pId, int timestamp);
extern void getFeed(int uId, int timestamp, int pIdList[]);

static int mSeed;
static int pseudo_rand(void)
{
	mSeed = mSeed * 431345 + 2531999;
	return mSeed & 0x7FFFFFFF;
}

static int follow_status[1005][1005];
static int answer_score;
static int n; // n >= 2 && n <= 1000
static int end_timestamp;
static int follow_ratio; // follow_ratio >= 1 && follow_ratio <= 10000
static int make_ratio; // make_ratio >= 1 && make_ratio <= 10000
static int like_ratio; // like_ratio >= 1 && like_ratio <= 10000
static int get_feed_ratio; // get_feed_ratio >= 1 && get_feed_ratio <= 10000
static int post_arr[200000];
static int total_post_cnt;
static int min_post_cnt;

static bool run()
{
	int uId1, uId2, pId, pIdList[10], ans_pIdList[10], rand_val;
	bool ret = true;

	scanf("%d%d%d%d%d%d%d", &mSeed, &n, &end_timestamp, &follow_ratio, &make_ratio, &like_ratio, &get_feed_ratio);
	init(n);

	for (int uId1 = 1; uId1 <= n; uId1++)
	{
		follow_status[uId1][uId1] = 1;
		int m = n / 10 + 1;
		if (m > 10)
			m = 10;
		for (int i = 0; i < m; i++)
		{
			uId2 = uId1;
			while (follow_status[uId1][uId2] == 1)
			{
				uId2 = pseudo_rand() % n + 1;
			}
			follow(uId1, uId2, 1);
			follow_status[uId1][uId2] = 1;
		}
	}
	min_post_cnt = total_post_cnt = 1;

	for (int timestamp = 1; timestamp <= end_timestamp; timestamp++)
	{
		rand_val = pseudo_rand() % 10000;
		if (rand_val < follow_ratio)
		{
			uId1 = pseudo_rand() % n + 1;
			uId2 = pseudo_rand() % n + 1;
			int lim = 0;
			while (follow_status[uId1][uId2] == 1 || uId1 == uId2)
			{
				uId2 = pseudo_rand() % n + 1;
				lim++;
				if (lim >= 5)
					break;
			}
			if (follow_status[uId1][uId2] == 0)
			{
				follow(uId1, uId2, timestamp);
				follow_status[uId1][uId2] = 1;
			}
		}
		rand_val = pseudo_rand() % 10000;

		if (rand_val < make_ratio)
		{
			uId1 = pseudo_rand() % n + 1;
			post_arr[total_post_cnt] = timestamp;

			makePost(uId1, total_post_cnt, timestamp);
			total_post_cnt += 1;
		}

		rand_val = pseudo_rand() % 10000;

		if (rand_val < like_ratio && total_post_cnt - min_post_cnt > 0)
		{
			while (post_arr[min_post_cnt] < timestamp - 1000 && min_post_cnt < total_post_cnt)
				min_post_cnt++;

			if (total_post_cnt != min_post_cnt)
			{
				pId = pseudo_rand() % (total_post_cnt - min_post_cnt) + min_post_cnt;
				like(pId, timestamp);
			}
		}

		rand_val = pseudo_rand() % 10000;
		if (rand_val < get_feed_ratio && total_post_cnt > 0)
		{
			uId1 = pseudo_rand() % n + 1;
			getFeed(uId1, timestamp, pIdList);

			for (int i = 0; i < 10; i++)
			{
				scanf("%d", ans_pIdList + i);
			}

			for (int i = 0; i < 10; i++)
			{
				if (ans_pIdList[i] == 0)
					break;

				if (ans_pIdList[i] != pIdList[i])
				{
					ret = false;
				}
			}
		}
	}

	return ret;
}

int main()
{
	freopen("0Text.txt", "r", stdin);
	setbuf(stdout, NULL);
	int tc;
	scanf("%d%d", &tc, &answer_score);

	for (int t = 1; t <= tc; t++)
	{
		int score;
		for (int i = 0; i < 1005; i++)
			for (int j = 0; j < 1005; j++)
				follow_status[i][j] = 0;

		if (run())
			score = answer_score;
		else
			score = 0;

		printf("#%d %d\n", t, score);
	}
	return 0;
}
