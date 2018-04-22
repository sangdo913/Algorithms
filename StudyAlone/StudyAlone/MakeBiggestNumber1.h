<<<<<<< HEAD
#pragma once
#include <stdio.h>


int MakeLargestNum(void) {
	char card[1000][4] = { 0 };
	int both[1000] = { 0 };
	int both_count = 0;
	int both_refresh = -1;
	int N;
	int left = 0, mid = 0, right = 0, one_mid = 0;
	int left_temp = 0, right_temp = 0;
	int Answer;

	//»óµµ Ãß°¡
	typedef enum {MAX = 0, SECOND = 1} BIGORDER;

	int both_left[2] = { -1,-1 };
	int both_right[2] = { -1,-1 };
	//
	setbuf(stdout, NULL);
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%s", &card[i]);
	}

	for (int i = 0; i < N; i++) {
		//blcok
		if (card[i] == "***") continue;
		//Only Mid
		if ((card[i][0] == '*') && (card[i][2] == '*')) {
			if (card[i][1] - '0' > one_mid)
				one_mid = card[i][1] - '0';
		}
		//LEFT
		else if (card[i][0] == '*') {
=======
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
>>>>>>> 8d7653d23a18c3ad18ba1db93f991e394865eef3
			if (card[i][1] != '*') left_temp += card[i][1] - '0';
			left_temp += card[i][2] - '0';
			if (left_temp > left) left = left_temp;
			left_temp = 0;
		}
<<<<<<< HEAD
		//RIHGT
		else if (card[i][2] == '*') {
=======
		else if (card[i][2] == '*'){
>>>>>>> 8d7653d23a18c3ad18ba1db93f991e394865eef3
			right_temp += card[i][0] - '0';
			if (card[i][1] != '*') right_temp += card[i][1] - '0';
			if (right_temp > right) right = right_temp;
			right_temp = 0;
		}
<<<<<<< HEAD
		//BOTH
		else if (card[i][1] == '*') {
			both[both_count++] = i;

			//left max update
			if (both_left[MAX] == -1)
			{
				both_left[MAX] = i;
			}
			else if (card[both_left[MAX]][0] < card[i][0])
			{
				both_left[SECOND] = both_left[MAX];
				both_left[MAX] = i;
			}
			else if (both_left[SECOND] == -1)
			{
				both_left[SECOND] = i;
			}
			else if ( card[both_left[SECOND]][0] < card[i][0])
			{
				both_left[SECOND] = i;
			}

			//right max update
			if (both_right[MAX] == -1)
			{
				both_right[MAX] = i;
			}
			else if (card[both_right[MAX]][2] < card[i][2])
			{
				both_right[SECOND] = both_right[MAX];
				both_right[MAX] = i;
			}

			else if (both_right[SECOND] == -1)
			{
				both_right[SECOND] = i;
			}
			else if (card[both_right[SECOND]][2] < card[i][2])
			{
				both_right[SECOND] = i;
			}
			//////
		}

=======
		else if (card[i][1] == '*'){
			both[both_count++] = i;
		}
>>>>>>> 8d7653d23a18c3ad18ba1db93f991e394865eef3
		else
			for (int j = 0; j < 3; j++)
				mid += card[i][j] - '0';
	}

<<<<<<< HEAD
	int both_sum = 0;
	int leftIndex, rightIndex;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			leftIndex = both_left[i]; 
			rightIndex = both_right[j];
			
			if (both_left[i] == both_right[j]) continue;
			else if(card[leftIndex][0] + card[rightIndex][2] - '0' - '0' > both_sum)
			{
				both_sum = card[leftIndex][0] + card[rightIndex][2] - '0' - '0';
			}
		}
	}
	//////////
	both_sum = both_sum > left + right ? both_sum : left + right;
	both_sum = both_sum > left + card[both_left[MAX]][0] -'0' ? both_sum : left + card[both_left[MAX]][0] - '0';
	both_sum = both_sum > right + card[both_right[MAX]][2] - '0' ? both_sum : right + card[both_right[MAX]][2] - '0';
	//////////
	Answer = mid + both_sum;
=======
	a = left + right;

	//-----------0*0ë¶€ë¶?------------
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
	//-----------0*0ë¶€ë¶„ë-------------
	Answer = a + mid;
>>>>>>> 8d7653d23a18c3ad18ba1db93f991e394865eef3
	if (one_mid > Answer) Answer = one_mid;
	return Answer;
}

int MakeBiggestNumber(void)
{
	int test_case;
	int T;
<<<<<<< HEAD

=======
	//freopen("input.txt", "r", stdin);
>>>>>>> 8d7653d23a18c3ad18ba1db93f991e394865eef3
	setbuf(stdout, NULL);
	scanf("%d", &T);
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int Answer;
<<<<<<< HEAD
		Answer = MakeLargestNum();
=======
		Answer=MakeLargestNum();
>>>>>>> 8d7653d23a18c3ad18ba1db93f991e394865eef3
		printf("#%d %d\n", test_case, Answer);
	}
	return 0;
}