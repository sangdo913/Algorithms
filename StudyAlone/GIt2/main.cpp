#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define TOTAL_SCORE 1000

extern void Branch(const char *str);
extern void Commit(int line_idx, int operation, const char *str, char* commit_message);
extern void Checkout(const char *str, int commit_idx, char *msg);
extern int GetDocument(char str[][15]);
extern void Init();
extern int maxfunc[10];

int total_score;
char docs[1024][15];
int main() {
	int tc;
	cin >> tc;
	for (int t = 1; t <= tc; t++) {
		Init();
		int notified_scoring;
		int num_operations, num_scoring;
		int num_correct = 0;
		cin >> num_operations >> notified_scoring;

		num_scoring = 0;
		for (int i = 0; i < num_operations; i++) {
			char cmd[10];
			char msg[25];
			char buf[25];
			int line_idx;
			int commit_idx;
			char str[1024];
			int operation;
			int num_lines;
			int correct_num_lines;
			bool correct;
			int start_idx, end_idx;
			scanf("%s", cmd);
			switch (cmd[0]) {
			case 'C':
				cin >> line_idx >> operation;
				if (operation != 2) {
					scanf("%s", str);
				}
				else {
					str[0] = 0;
				}
				scanf("%s", msg);

				Commit(line_idx, operation, str, msg);
				break;
			case 'B':
				scanf("%s", str);
				Branch(str);
				break;
			case 'K':
				scanf("%s", str);
				cin >> commit_idx;
				scanf("%s", msg);
				Checkout(str, commit_idx, buf);
				if (strcmp(msg, buf)) {
					correct = false;
					//printf("---- Commit message should be \'%s\' but \'%s\'\n", msg, buf);
				}
				else {
					correct = true;
				}
				++num_scoring;
				num_correct += correct;
				break;
			case 'G':
				num_lines = GetDocument(docs);
				cin >> correct_num_lines;
				correct = true;
				correct = num_lines == correct_num_lines;
				for (int i = 0; i < correct_num_lines; i++) {
					scanf("%s", str);
					if (strcmp(docs[i], str)) {
						//printf("---- Document should be \'%s\' but \'%s\'\n", str, docs[i]);
						correct = false;
					}
				}
				if (!correct)
					int debug = 1;
				num_correct += correct;
				++num_scoring;
				break;
			}
		}

		int score = num_correct * TOTAL_SCORE / num_scoring;
		printf("#%d %d\n", t, score);
		total_score += score;
	}
		printf("\n");
	printf("total score : %d\n", total_score);

}