#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define N              4
#define MAX_QUERYCOUNT 1000000

#include<stdlib.h>
static int digits[N];
static int digits_c[10];

static int T;

extern void doUserImplementation(int guess[]);

static int querycount;

// the value of limit_query will be changed in evaluation
static const int limit_query = 2520;

typedef struct {
	int strike;
	int ball;
} Result;

static bool isValid(int guess[]) {
	int guess_c[10];

	for (int count = 0; count < 10; ++count) guess_c[count] = 0;
	for (int idx = 0; idx < N; ++idx) {
		if (guess[idx] < 0 || guess[idx] >= 10 || guess_c[guess[idx]] > 0) return false;
		guess_c[guess[idx]]++;
	}
	return true;
}

// API : return a result for comparison with digits[] and guess[]
Result query(int guess[]) {
	Result result;

	if (querycount >= MAX_QUERYCOUNT) {
		result.strike = -1;
		result.ball = -1;
		return result;
	}

	querycount++;

	if (!isValid(guess)) {
		result.strike = -1;
		result.ball = -1;
		return result;
	}

	result.strike = 0;
	result.ball = 0;

	for (int idx = 0; idx < N; ++idx)
		if (guess[idx] == digits[idx])
			result.strike++;
		else if (digits_c[guess[idx]] > 0)
			result.ball++;

	return result;
}

struct List {
	int nums[4];
	List *next;
	List() {
		next = 0;
	}
}li[10000];

int lidx = 0;

static void initialize() {
	for (int count = 0; count < 10; ++count) digits_c[count] = 0;
	for (int idx = 0; idx < N; ++idx) {
		char c;
		digits[idx] = li[lidx].nums[idx];
		digits_c[digits[idx]]++;
	}
	lidx++;
	querycount = 0;
}

static bool check(int guess[]) {
	for (int idx = 0; idx < N; ++idx)
		if (guess[idx] != digits[idx]) return false;
	return true;
}

int allnum[10] = { 0,1,2,3,4,5,6,7,8,9};

void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}
void setDigits(int depth) {
	if (depth == 4) {
		for (int i = 0; i < 4; i++) {
			li[lidx].nums[i] = allnum[i];
		}
		lidx++;
		return;
	}
	for (int i = depth; i < 10; i++) {
		swap(allnum[depth], allnum[i]);
		setDigits(depth + 1);
		swap(allnum[depth], allnum[i]);
	}
}
int main() {
	int total_score = 0;
	int total_querycount = 0;;

	// freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);

	setDigits(0);
	for (int i = 0; i < 9999; i++)
	{
		if(li[i].nums[1] != 0 || li[i].nums[1] != 0 || li[i].nums[2] != 0 || li[i].nums[3] != 0)
			li[i].next = &li[i + 1];
	}
	scanf("%d", &T);
	int testcase;
	lidx = 0;
	for ( testcase = 1; li[lidx].next ; ++testcase) {
		
		initialize();

		int guess[N];
		doUserImplementation(guess);

		if (!check(guess)) querycount = MAX_QUERYCOUNT;
		if (querycount <= limit_query) total_score++;
		printf("#%d %d\n", testcase, querycount);
		total_querycount += querycount;
	}
	if (total_querycount > MAX_QUERYCOUNT) total_querycount = MAX_QUERYCOUNT;
	printf("total score = %d\ntotal query = %d\n", total_score * 100 /(testcase-1) , total_querycount);
	return 0;
}