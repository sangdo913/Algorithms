#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include"user.cpp"

#define CMD_INIT 100
#define CMD_GETRECT 200
#define CMD_MERGE 300
#define CMD_SPLIT 400
#define CMD_UNDO 500
#define CMD_CHKRECT 600

#define MAX_SELECT 15

extern void init(int R, int C);
extern void getRect(int r, int c, int rect[]);
extern int mergeCells(int cnt, int rs[], int cs[], int rect[]);
extern int splitCell(int r, int c, int rect[]);
extern void undo();
extern int checkRectangle(int r1, int c1, int r2, int c2);

static bool run()
{

	int Q, cmd;
	int rr, C;
	int r, c, cnt, rs[MAX_SELECT], cs[MAX_SELECT];
	int r1, c1, r2, c2;
	int ans_rect[4];
	int rect[4];

	int ret = 0;
	int ans = 0;
	scanf("%d", &Q);
	bool okay = false;

	for (int order = 0; order < Q; ++order)
	{
		scanf("%d", &cmd);
		switch (cmd)
		{
		case CMD_INIT:
			scanf("%d %d", &rr, &C);
			init(rr, C);
			okay = true;
			break;
		case CMD_GETRECT:
			scanf("%d %d", &r, &c);
			getRect(r, c, rect);
			for (int i = 0; i < 4; i++)
			{
				scanf("%d", &ans_rect[i]);
				if (ans_rect[i] != rect[i])
					okay = false;
			}
			break;
		case CMD_MERGE:
			scanf("%d", &cnt);
			for (int i = 0; i < cnt; i++)
				scanf("%d", &rs[i]);
			for (int i = 0; i < cnt; i++)
				scanf("%d", &cs[i]);
			ret = mergeCells(cnt, rs, cs, rect);
			scanf("%d", &ans);
			if (ans != ret)
				okay = false;
			if (ans == 0)
				break;
			for (int i = 0; i < 4; i++)
			{
				scanf("%d", &ans_rect[i]);
				if (ans_rect[i] != rect[i])
					okay = false;
			}
			break;
		case CMD_SPLIT:
			scanf("%d %d", &r, &c);
			ret = splitCell(r, c, rect);
			scanf("%d", &ans);
			if (ans != ret)
				okay = false;
			if (ans == 0)
				break;
			for (int i = 0; i < 4; i++)
			{
				scanf("%d", &ans_rect[i]);
				if (ans_rect[i] != rect[i])
					okay = false;
			}
			break;
		case CMD_UNDO:
			undo();
			break;
		case CMD_CHKRECT:
			scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
			ret = checkRectangle(r1, c1, r2, c2);
			scanf("%d", &ans);
			if (ans != ret)
				okay = false;
			break;
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
	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}
	return 0;
}