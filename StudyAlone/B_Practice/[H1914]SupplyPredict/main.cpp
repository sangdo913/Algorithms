#ifndef _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS 
#endif

#include<stdio.h>
#include"user.cpp"

#define MAX_N    100
#define MAX_TOOL 50

#define ENDCASE 0
#define ADDLOT  1
#define SIMUL   2

extern void init(int N);
extern void setupTool(int T, int stepNo[5000], int procTime[5000]);
extern void addLot(int time, int number);
extern int simulate(int time, int wip[MAX_N]);

static int run() {
	int totalStep = 0, totalTool = 0, stepID[MAX_N * MAX_TOOL], procTime[MAX_N * MAX_TOOL];
	int event, time, number;
	int userOut, userWip[MAX_N], resultOut, resultWip[MAX_N];
	int score = 100;

	for (int j = 0; j < MAX_N; j++) {
		userWip[j] = resultWip[j] = 0;
	}

	scanf("%d %d", &totalStep, &totalTool);
	init(totalStep);

	for (int i = 0; i < totalTool; i++) {
		scanf("%d %d", stepID+i, procTime+i);
	}
	setupTool(totalTool, stepID, procTime);

	while (1) {
		scanf("%d", &event);
		if (event == ADDLOT) {
			scanf("%d %d", &time, &number);
			addLot(time, number);
		}

		else if (event == SIMUL) {
			scanf("%d", &time);
			for (int j = 0; j < totalStep; j++) {
				userWip[j] = 0;
				scanf("%d", &resultWip[j]);
			}
			scanf("%d", &resultOut);

			userOut = simulate(time, userWip);

			for (int j = 0; j < totalStep; j++) {
				if (userWip[j] != resultWip[j]) {
					score = 0;
                    break;
				}
			}
			if (userOut != resultOut) {
				score = 0;
			}
		}
		else {
			return score;
		}
	}
	return score;
}

int main() {
	setbuf(stdout, NULL);
	int TestCase;

	freopen("0Text.txt", "r", stdin); 
	scanf("%d", &TestCase);
	for (int t = 1; t <= TestCase; ++t)
		printf("#%d %d\n", t, run());
	return 0;
}
