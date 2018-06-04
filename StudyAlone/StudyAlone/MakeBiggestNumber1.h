#include <stdio.h>

int max3(int a, int b, int c){
	int temp = a;
    if(temp < b) temp = b;
    if(temp < c) temp = c;

	return temp;
}

int MakeLargestNum(void){
	char card[1000][4] = { 0 };
	int both[1000] = { 0 };
	int both_count = 0;
	int both_max = 0;
	int left = 0, mid = 0, right = 0, one_mid = 0;
	int left_temp = 0, right_temp = 0;
	int N=0;
	int Answer=0;
	setbuf(stdout, NULL);
	scanf("%d", &N);
	for (int i = 0; i < N; i++){
		scanf("%s", &card[i]);
	}

    int a;

	for (int i = 0; i < N; i++){
		if (card[i] == "***") continue;
		if ((card[i][0] == '*') && (card[i][2] == '*')){
			if (card[i][1] - '0' > one_mid)
				one_mid = card[i][1] - '0';
		}
		else if (card[i][0] == '*'){
			if (card[i][1] != '*') left_temp += card[i][1] - '0';
			left_temp += card[i][2] - '0';
			if (left_temp > left) left = left_temp;
			left_temp = 0;
		}
		else if (card[i][2] == '*'){
			right_temp += card[i][0] - '0';
			if (card[i][1] != '*') right_temp += card[i][1] - '0';
			if (right_temp > right) right = right_temp;
			right_temp = 0;
		}
		else if (card[i][1] == '*'){
			both[both_count++] = i;
		}
		else
			for (int j = 0; j < 3; j++)
				mid += card[i][j] - '0';
	}

	a = left + right;

	//-----------0*0부분-------------
	if (left < 9 || right < 9){
		for (int i = 0; i < both_count; i++){
			for (int j = 0; j < both_count; j++){
				if (i == j)continue;
				if (both_max < card[both[i]][2] + card[both[j]][0] - '0' - '0') both_max = card[both[i]][2] + card[both[j]][0] - '0' - '0';
			}
		}
		right_temp = right;
		for (int i = 0; i < both_count; i++){
			if (left + card[both[i]][0] - '0'>left + right_temp) right_temp = card[both[i]][0] - '0';
		}
		left_temp = left;
		for (int i = 0; i < both_count; i++){
			if (card[both[i]][2] - '0' + right>left_temp + right)  left_temp = card[both[i]][2] - '0';
		}
		a = max3(both_max, left + right_temp, left_temp + right);
	}
	//-----------0*0부분끝-------------
	Answer = a + mid;
	if (one_mid > Answer) Answer = one_mid;
	return Answer;
}

int MakeBiggestNumber(void)
{
	int test_case;
	int T;
	//freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);
	scanf("%d", &T);
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int Answer;
		Answer=MakeLargestNum();
		printf("#%d %d\n", test_case, Answer);
	}
	return 0;
}