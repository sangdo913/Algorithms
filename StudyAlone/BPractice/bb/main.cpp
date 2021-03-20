#ifndef _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS 
#endif

#include<stdio.h>

extern void init(int n);
extern int search(int mId, int searchTimestamp, char searchWord[11], char correctWord[5][11]);

int n, m;
char words[4000][11];

static int mstrcmp(const char *a, const char *b)
{
	int i;
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] != b[i])
			return a[i] - b[i];
	}
	return a[i] - b[i];
}

void inputWords(int wordCnt) {
	for (int i = 0; i < wordCnt; ++i) {
		scanf("%s", words[i]);
	}
}

bool run(int m) {

	bool accepted = true;

	while (m--) {

		int id, timestamp, correctWordN, answerWordN;
		int wordIdx;
		char correctWord[5][11] = { 0 };
		char answerWord[5][11] = { 0 };

		scanf("%d%d%d", &id, &timestamp, &wordIdx);

		correctWordN = search(id, timestamp, words[wordIdx], correctWord);

		scanf("%d", &answerWordN);

		for (int i = 0; i < answerWordN; ++i) {
			scanf("%s", answerWord[i]);
		}

		if (correctWordN != answerWordN) {
			accepted = false;
		}
		else {
			for (int i = 0; i < answerWordN; ++i) {
				bool isExist = false;

				for (int j = 0; j < correctWordN; ++j) {
					if (mstrcmp(answerWord[i], correctWord[j]) == 0) {
						isExist = true;
					}
				}

				if (!isExist) {
					accepted = false;
				}
			}
		}
	}

	return accepted;
}

int main(void) {

	int test, T;
	int wordCnt;

	// freopen("sample_input.txt", "r", stdin);

	setbuf(stdout, NULL);

	scanf("%d", &T);

	for (test = 1; test <= T; ++test) {

		scanf("%d", &wordCnt);

		inputWords(wordCnt);
		
		scanf("%d%d", &n, &m);

		init(n);

		if (run(m)) {
			printf("#%d 100\n", test);
		}
		else {
			printf("#%d 0\n", test);
		}
	}

	return 0;
}