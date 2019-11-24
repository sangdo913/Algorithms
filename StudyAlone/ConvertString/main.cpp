
#include <stdio.h>
#include <time.h>

#define MAX_WORD_LIST 50000
#define MAX_CMD_CNT  50000

static unsigned long long seed = 0722;

extern void init(int n, char Word[]);
extern int Replace(char str1[], char str2[]);
extern void GetStr(char Result[]);

char alphabet[] = { "abcdefghijklmnopqrstuvxyz" };
char Word[MAX_WORD_LIST + 1] = { 0 };
char Result[MAX_WORD_LIST + 1];

char Chg_word[MAX_WORD_LIST][4]; int chg_word_index;


static unsigned int pseudo_rand(void)
{
	seed = seed * 25214903917ULL + 11ULL;
	return (unsigned int)(seed >> 16);
}
using namespace std;

int verify(char* d) {
	unsigned long long temp;
	scanf("%llu", &temp);
	//cin >> temp;
	unsigned long long hash = 5381;
	unsigned long long  idx = seed;
	for (register int i = 0; i < 16; i++)
	{
		idx = idx * 25214903917ULL + 11ULL;
		idx = (idx >> 16) % MAX_WORD_LIST;
		hash = (((hash << 4) + hash) + d[idx]);
	}
	if (temp == hash)  return 1;
	else return 0;
}
extern clock_t mytimes[100];

int main()
{
	time_t t = clock();

	int T = 50;
	int N = 50000;
	int M = 50000;

	//freopen("sample_input.txt", "r", stdin);

	for (register int tc = 1; tc <= T; ++tc)
	{
		chg_word_index = 0;
		register int i = 0;
		for (i = 0; i < N; ++i)
		{
			Word[i] = alphabet[pseudo_rand() % 25];
			while (pseudo_rand() % 7)
			{
				if (i + 1 >= N) break;
				Word[i + 1] = Word[i];
				++i;
			}
		}

		register int key1, key2, key3;
		char check[26][26][26] = { 0 };
		for (i = 0; i < N - 2; ++i)
		{
			key1 = Word[i] - 'a';
			key2 = Word[i + 1] - 'a';
			key3 = Word[i + 2] - 'a';
			if (!check[key1][key2][key3])
			{
				check[key1][key2][key3] = 1;

				Chg_word[chg_word_index][0] = Word[i];
				Chg_word[chg_word_index][1] = Word[i + 1];
				Chg_word[chg_word_index][2] = Word[i + 2];
				++chg_word_index;
			}
		}

		init(N, Word);

		int cmd_cnt = 0;
		int cnt = 0;
		int flag = true;
		int score = 0;

		char str2[4] = { 0 };

		while (cmd_cnt < M)
		{
			for (int i = 0; i < 3; ++i)
			{
				str2[i] = alphabet[pseudo_rand() % 25];
			}

			int idx = pseudo_rand() % chg_word_index;

			cnt = Replace(Chg_word[idx], str2);

			Chg_word[idx][0] = str2[0];
			Chg_word[idx][1] = str2[1];
			Chg_word[idx][2] = str2[2];

			int Chg_cnt;
			scanf("%d", &Chg_cnt);
			if (cnt != Chg_cnt)
			{
				flag = false;
				break;
			}

			++cmd_cnt;
		}

		if (flag)
		{
			score = 100;
			char Rsp[MAX_WORD_LIST + 1] = { 0 };
			GetStr(Rsp);
			int ret = verify(Rsp);
			if (!ret)
			{
				score = 0;
			}

		}
		printf("#%d %d\n", tc, score);

	}

	printf("time = %d\n", clock() - t);

	return 0;
}
