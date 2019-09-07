#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include"user.cpp"
#define MAX_USER      1000
#define MAX_TAG       5000
#define MAX_ID        1000000
#define MAX_TPM       10

#define CREATE 0
#define FOLLOW 1
#define SEARCH 2
#define GETMSG 3

extern void init();
extern void createMessage(int msgID, int userID, char msgData[]);
extern void followUser(int userID1, int userID2);
extern int searchByHashtag(char tagName[], int retIDs[]);
extern int getMessages(int userID, int retIDs[]);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static char HashTag[MAX_TAG][10];
static int uCnt, tCnt, initSeed;

static int mSeed;
static int pseudo_rand(void)
{
	mSeed = mSeed * 431345 + 2531999;
	return mSeed & 0x7FFFFFFF;
}

static int mstrcpy(char *dest, const char *src)
{
	int i = 0;
	while (src[i] != '\0') { dest[i] = src[i]; i++; }
	dest[i] = src[i];
	return i;
}

static void prepare()
{
	mSeed = initSeed;
	for (int i = 0; i < tCnt; ++i) {
		int length = 5 + pseudo_rand() % 4;
		for (int k = 0; k < length; ++k)
			HashTag[i][k] = 'a' + pseudo_rand() % 26;
		HashTag[i][length] = 0;
	}
}

static void create_msg()
{
	int tagid[10];
	char msgbuf[200];

	scanf("%d %s", &mSeed, msgbuf);

	int msgid = pseudo_rand() % (MAX_ID + 1);
	int userid = pseudo_rand() % uCnt;
	int tagcnt = 1 + pseudo_rand() % MAX_TPM;
	for (int i = 0; i < tagcnt; ++i) {
		tagid[i] = pseudo_rand() % tCnt;
	}

	int pos = 8;
	msgbuf[pos++] = ' ';
	for (int i = 0; i < tagcnt - 1; ++i) {
		msgbuf[pos++] = '#';
		pos += mstrcpy(msgbuf + pos, HashTag[tagid[i]]);
		msgbuf[pos++] = ' ';
	}
	msgbuf[pos++] = '#';
	pos += mstrcpy(msgbuf + pos, HashTag[tagid[tagcnt - 1]]);
	msgbuf[pos++] = 0;

	createMessage(msgid, userid, msgbuf);
}

static int run(int Ans, int sample1)
{
	int N, cmd, param1, param2, answer[5];
	char buf[10];
	int retcnt, retIDs[5];

	if (sample1 == 1) {
		scanf("%d", &N);
		uCnt = tCnt = initSeed = 0;
	}
	else {
		scanf("%d %d %d %d", &N, &uCnt, &tCnt, &initSeed);
	}

	prepare();
	init();

	for (int i = 0; i < N; ++i) {
		scanf("%d", &cmd);
		switch (cmd) {
		case CREATE:
			if (sample1 == 1) {
				char buf2[200];
				scanf("%d %d %s", &param1, &param2, &buf2);
				for (int k = 0; k < 200; ++k) {
					if (buf2[k] == '_') buf2[k] = ' ';
					if (buf2[k] == 0) break;
				}
				createMessage(param1, param2, buf2);
			}
			else {
				create_msg();
			}
			break;
		case FOLLOW:
			scanf("%d %d", &param1, &param2);
			followUser(param1, param2);
			break;
		case SEARCH:
			if (sample1 == 1) {
				scanf("%s %d", buf, &param2);
			}
			else {
				scanf("%d %d", &param1, &param2);
				buf[0] = '#';
				mstrcpy(buf + 1, HashTag[param1]);
			}
			for (int k = 0; k < param2; ++k)
				scanf("%d", &answer[k]);
			retcnt = searchByHashtag(buf, retIDs);
			if (retcnt != param2)
				Ans = 0;
			else {
				for (int k = 0; k < param2; ++k) {
					if (retIDs[k] != answer[k])
						Ans = 0;
				}
			}
			break;
		case GETMSG:
			scanf("%d %d", &param1, &param2);
			for (int k = 0; k < param2; ++k)
				scanf("%d", &answer[k]);
			retcnt = getMessages(param1, retIDs);
			if (retcnt != param2)
				Ans = 0;
			else {
				for (int k = 0; k < param2; ++k) {
					if (retIDs[k] != answer[k])
						Ans = 0;
				}
			}
			break;
		default:
			break;
		}
	}

	return Ans;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("0Text.txt", "r", stdin);

	int T, Ans, sample_1;
	scanf("%d %d %d", &T, &Ans, &sample_1);

	for (int tc = 1; tc <= T; tc++) {
		printf("#%d %d\n", tc, run(Ans, sample_1));
		sample_1 = 0;
	}

	return 0;
}
