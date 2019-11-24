#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include<time.h>

#define INIT         0
#define SENDMAIL     1
#define GETCOUNT     2
#define DELETEMAIL   3
#define SEARCHMAIL   4

extern void init(int N, int K);
extern void sendMail(char subject[], int uID, int cnt, int rIDs[]);
extern int getCount(int uID);
extern int deleteMail(int uID, char subject[]);
extern int searchMail(int uID, char text[]);
clock_t st;

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

#define MAX_WORD 10000
static char Word[MAX_WORD][11];

static int N, W, minR, maxR, SW;

static int mSeed;
static int pseudo_rand(void)
{
	mSeed = mSeed * 214013 + 2531011;
	return (mSeed >> 16) & 0x7FFF;
}

static void make_string(int seed)
{
	mSeed = seed;

	for (int i = 0; i < W; ++i) {
		int length = 5 + pseudo_rand() % 6;
		for (int k = 0; k < length; ++k) {
			Word[i][k] = 'a' + pseudo_rand() % 26;
		}
		Word[i][length] = '\0';
	}
}

static void send_mail(int seed)
{
	char str[200];
	int pos = 0;

	mSeed = seed;

	int wcnt = 1 + pseudo_rand() % SW;
	for (int i = 0; i < wcnt; ++i) {
		int widx = pseudo_rand() % W;
		for (int k = 0; k < 10; ++k) {
			if (Word[widx][k] == '\0') break;
			str[pos++] = Word[widx][k];
		}
		str[pos++] = ' ';
	}
	str[pos - 1] = '\0';

	int uid = pseudo_rand() % N;
	int rcnt = minR + pseudo_rand() % (maxR - minR + 1);
	int rids[50];
	for (int i = 0; i < rcnt; ++i) {
		rids[i] = pseudo_rand() % N;
	}

	st = clock();
	sendMail(str, uid, rcnt, rids);
}

static int delete_mail(int uid, int seed)
{
	char str[200];
	int pos = 0;

	mSeed = seed;

	int wcnt = 1 + pseudo_rand() % SW;
	for (int i = 0; i < wcnt; ++i) {
		int widx = pseudo_rand() % W;
		for (int k = 0; k < 10; ++k) {
			if (Word[widx][k] == '\0') break;
			str[pos++] = Word[widx][k];
		}
		str[pos++] = ' ';
	}
	str[pos - 1] = '\0';

	st = clock();
	return deleteMail(uid, str);
}

static int run(int answer)
{
	int Q, K, cmd, sample, seed, param1, param2, ret;
	char str[30];

	scanf("%d %d %d %d", &Q, &sample, &N, &K);
	if (sample == 0) {
		scanf("%d %d %d %d %d", &W, &minR, &maxR, &SW, &seed);
		make_string(seed);
	}

	init(N, K);

	int fcnt[100] = {};
	clock_t mytime[4] = {};
	for (int i = 1; i < Q; ++i) {
		scanf("%d", &cmd);
		switch (cmd) {
		case SENDMAIL:
			fcnt[0]++;
			if (sample == 1) {
				int uid, rcnt;
				int rids[10];
				scanf("%s %d %d", str, &uid, &rcnt);
				for (int k = 0; k < rcnt; ++k) scanf("%d", &rids[k]);
				for (int k = 0; k < 30; ++k) {
					if (str[k] == '\0') break;
					if (str[k] == '_') str[k] = ' ';
				}
				st = clock();
				sendMail(str, uid, rcnt, rids);
			}
			else {
				scanf("%d", &seed);
				send_mail(seed);
			}
			mytime[0] += clock() - st;
			break;
		case GETCOUNT:
			fcnt[1]++;
			scanf("%d %d", &param1, &param2);
			st = clock();
			ret = getCount(param1);
			mytime[1] += clock() - st;
			if (ret != param2)
				answer = 0;
			break;
		case DELETEMAIL:
			fcnt[2]++;
			if (sample == 1) {
				int uid;
				scanf("%d %s %d", &param1, str, &param2);
				for (int k = 0; k < 30; ++k) {
					if (str[k] == '\0') break;
					if (str[k] == '_') str[k] = ' ';
				}
				st = clock();
				ret = deleteMail(param1, str);
				mytime[2] += clock() - st;
				if (ret != param2)
					answer = 0;
			}
			else {
				scanf("%d %d %d", &param1, &seed, &param2);
				ret = delete_mail(param1, seed);
				mytime[2] += clock() - st;
				if (ret != param2)
					answer = 0;
			}
			break;
		case SEARCHMAIL:
			fcnt[3]++;
			scanf("%d %s %d", &param1, str, &param2);
			st = clock();
			ret = searchMail(param1, str);
			mytime[3] += clock() - st;
			if (ret != param2)
				answer = 0;
			break;
		default:
			break;
		}
	}

	printf("%d %d %d %d\n", fcnt[0], fcnt[1], fcnt[2], fcnt[3]);
	printf("%d %d %d %d\n", mytime[0], mytime[1], mytime[2], mytime[3]);
	return answer;
}

int main()
{
	setbuf(stdout, NULL);
	//freopen("sample_input.txt", "r", stdin);

	int T, Mark;
	scanf("%d %d", &T, &Mark);

	for (int tc = 1; tc <= T; tc++) {
		printf("#%d %d\n", tc, run(Mark));
	}

	return 0;
}
