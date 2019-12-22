#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>
#include<string.h>
#include"user.cpp"

extern void init(int mScreenSize);
extern void create_memo(int mId, int mY, int mX, int mHeight, int mWidth, char str[]);
extern AXIS select_memo(int mId);
extern void move_memo(int mId, int mY, int mX);
extern void modify_memo(int mId, int mHeight, int mWidth, char str[]);
extern void get_screen_context(int mY, int mX, char res[5][5]);

static int pseudo_rand(void);
static void make_command_list();
static void make_input_string(char a[], int max_len);
static int make_hash(char a[5][5]);

enum COMMAND
{
	CREATE = 100,
	SELECT = 200,
	MOVE = 300,
	MODIFY = 400,
	GETRES = 999
};

static int dummy1[9389], dummy2[745];
static int status[5], commandList[100005], listsize = 0, seed;
static int newCommand[4] = { CREATE, SELECT, MOVE, MODIFY };
static char input_str[2555], user_ans_str[5][5];
int mydebug = 0;

int main()
{
	int tc, totalScore = 0;


	freopen("0Text.txt", "r", stdin);
	setbuf(stdout, NULL);

	scanf("%d", &tc);
	for (int t = 1; t <= tc; t++)
	{
		int accepted = 0, id_size = 0, input_cnt = 0, ans_cnt = 0, H, W, Y, X;
		int screen_size, memo_size, correct_ans, user_ans;
		AXIS cur_axis;

		scanf("%d%d%d%d", &seed, &screen_size, &memo_size, &id_size);

		if (memo_size * 2 >= screen_size)
			memo_size = screen_size / 2;

		for (int i = 0; i < 4; i++)
		{
			scanf("%d", status + i);
			input_cnt += status[i] * 2;
			ans_cnt += status[i];
		}

		init(screen_size);

		for (int mid = 0; mid < id_size; mid++)
		{
			H = pseudo_rand() % memo_size + 1;
			W = pseudo_rand() % memo_size + 1;
			cur_axis.y = Y = pseudo_rand() % (screen_size - H + 1);
			cur_axis.x = X = pseudo_rand() % (screen_size - W + 1);
			make_input_string(input_str, H*W);
			if(mydebug)printf("create %d Y(%d) X(%d) H(%d) W(%d) str(%s)\n", id_size, Y, X, H, W, input_str);
			create_memo(mid, Y, X, H, W, input_str);
		}

		make_command_list();

		for (int i = 0; i < input_cnt; i++)
		{
			int comm = commandList[i], target_id;

			switch (comm)
			{
			case CREATE:
				H = pseudo_rand() % memo_size + 1;
				W = pseudo_rand() % memo_size + 1;
				cur_axis.y = Y = pseudo_rand() % (screen_size - H + 1);
				cur_axis.x = X = pseudo_rand() % (screen_size - W + 1);
				make_input_string(input_str, H*W);

				if(mydebug)printf("create %d Y(%d) X(%d) H(%d) W(%d) str(%s)\n", id_size, Y, X, H, W, input_str);
				create_memo(id_size, Y, X, H, W, input_str);
				id_size++;
				break;
			case SELECT:
				target_id = pseudo_rand() % id_size;

				if(mydebug)printf("SEL id(%d)\n", target_id);
				cur_axis = select_memo(target_id);
				if(mydebug)printf("cur_axis y(%d), x(%d)\n", cur_axis.y, cur_axis.x);
				break;
			case MOVE:
				target_id = pseudo_rand() % id_size;
				cur_axis.y = Y = pseudo_rand() % (screen_size - memo_size + 1);
				cur_axis.x = X = pseudo_rand() % (screen_size - memo_size + 1);

				if(mydebug)printf("move memo %d y(%d) x(%d)\n", target_id, Y, X);
				move_memo(target_id, Y, X);
				break;
			case MODIFY:
				target_id = pseudo_rand() % id_size;
				H = pseudo_rand() % memo_size + 1;
				W = pseudo_rand() % memo_size + 1;
				make_input_string(input_str, memo_size * memo_size);

				if(mydebug)printf("modify %d H(%d) W(%d) str(%s)\n", target_id, H, W, input_str);
				modify_memo(target_id, H, W, input_str);
				break;
			case GETRES:
				Y = cur_axis.y + pseudo_rand() % 11 - 5;
				X = cur_axis.x + pseudo_rand() % 11 - 5;

				if (Y < 0)
					Y = 0;
				if (Y + 5 >= screen_size)
					Y = screen_size - 5;

				if (X < 0)
					X = 0;
				if (X + 5 >= screen_size)
					X = screen_size - 5;

				get_screen_context(Y, X, user_ans_str);
				if(mydebug)printf("GETERS Y(%d) X(%d)\n", Y, X);
                if(mydebug)
				for (int i = 0; i < 5; ++i) {
					for (int j = 0; j < 5; ++j) printf("%c", user_ans_str[i][j]);
					printf("\n");
				}
				user_ans = make_hash(user_ans_str);

				scanf("%d", &correct_ans);
				if (correct_ans == user_ans)
					accepted++;
				else
					int debug = 1;

				break;
			default:
				break;
			}
		}

		if (accepted == ans_cnt)
			printf("#%d 100\n", t), totalScore += 100;
		else
			printf("#%d 0\n", t);

	}

	printf("Total Score = %d\n", totalScore / tc);
}

static int pseudo_rand(void)
{
	seed = seed * 431345 + 2531999;
	return seed & 0x7FFFFFFF;
}

static void make_command_list()
{
	int tot = 0, listsize = 0;
	for (int i = 0; i < 4; i++)
	{
		tot += status[i];
	}
	for (int i = tot; i > 0; i--)
	{
		int val = pseudo_rand() % i;
		int pos = 0;
		val -= status[pos];
		while (val > 0 || status[pos] == 0)
		{
			pos++;
			val -= status[pos];
			if (pos >= 4)
				break;
		}

		switch (pos)
		{
		case 0:
			commandList[listsize++] = CREATE;
			commandList[listsize++] = GETRES;
			break;
		case 1:
			commandList[listsize++] = SELECT;
			commandList[listsize++] = GETRES;
			break;
		case 2:
			commandList[listsize++] = MOVE;
			commandList[listsize++] = GETRES;
			break;
		case 3:
			commandList[listsize++] = MODIFY;
			commandList[listsize++] = GETRES;
			break;
		default:
			break;
		}
		status[pos]--;
	}
}

static void make_input_string(char a[], int max_len)
{
	int len = pseudo_rand() % max_len + 10;
	for (int i = 0; i < len; i++)
		a[i] = pseudo_rand() % 26 + 'a';

	a[len] = '\0';
}

static int make_hash(char a[5][5])
{
	int ret = 9875;

	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			if (a[y][x] == '\0')
				continue;

			ret = (ret*a[y][x]) % 32853;
		}
	}

	return ret;
}