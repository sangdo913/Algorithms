#include <stdio.h>
#include <string.h>
#include "user.cpp"
extern void init();
extern void add_q(char* name, int point);
extern void solve_specific_num(int num);
extern void solve_specific_name(char* name);
extern int get_total_point();
extern void solve_highest_score();
static int Score;

static void cmd_init()
{
	init();
}



static void cmd_add()
{
	int point;
	char str[20];
	scanf("%s %d", str, &point);
	add_q(str, point);
}

static void cmd_solve_num()
{
	int num;
	scanf("%d", &num);
	solve_specific_num(num);
}

static void cmd_solve_name()
{
	char str[20];
	scanf("%s", str);
	solve_specific_name(str);
}

static void cmd_get_point()
{
	int num1, num2;
	scanf("%d", &num1);

	num2 = get_total_point();

	if (num1 != num2) {
		Score = 0;
	}
}
static void cmd_solve_high_score() {
	solve_highest_score();
}

static void run(){
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		int cmd;
		scanf("%d", &cmd);
		switch (cmd)
		{
		case 100: cmd_add();    break;
		case 200: cmd_solve_num(); break;
		case 300: cmd_solve_name(); break;
		case 900: cmd_get_point(); break;
		case 400: cmd_solve_high_score(); break;
		default: break;
		}
	}
}


static void init_members()
{
	Score = 100;
	cmd_init();
}

int main()
{
	freopen("0Text.txt", "r", stdin);
	setbuf(stdout, NULL);
	int T;
	scanf("%d", &T);
	int TotalScore = 0;
	for (int tc = 1; tc <= T; tc++)
	{
		init_members();
		run();

		TotalScore += Score;
		printf("#%d %d\n", tc, Score);
	}
	printf("TotalScore = %d\n", TotalScore);
	return 0;
}