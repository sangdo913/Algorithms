#include <cstdio>
#include<fstream>
#include<iostream>
using namespace std;
#include"user.cpp"

const int SIZE = 5000000;
const int MAX_NUM = 1000000000;
static int SCORE;
static int seed;

int arr[SIZE];

extern long long solve(int* arr, int n);

static int pseudo_rand(void) {
	seed = seed * 214013 + 2531011;
	return (seed >> 16) & 0x7FFF;
}

long long _build(int* arr, int n) {
	int prev = 0;
	long long ret = 0;
	for (register int i = 0; i < n; i++) {
		arr[i] = prev + (pseudo_rand()) % (MAX_NUM / SIZE + 1);
		prev = arr[i];
		if (i & 1)ret += arr[i];
	}
	return ret;
}

void _swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

void _shuffle(int *arr, int n) {
	for (register int i = 0; i < n; i++) {
		register int a = -1, b = -1;
		while (a == b) {
			a = ((pseudo_rand() << 15) | pseudo_rand()) % SIZE;
			b = ((pseudo_rand() << 15) | pseudo_rand()) % SIZE;
		}
		_swap(arr[a], arr[b]);
	}
}

int main() {
	//scanf("%d", &seed);
	seed = 2342;
	SCORE = 0;
	for (int T = 0; T < 10; T++)
	{
		long long answer = _build(arr, SIZE);

		_shuffle(arr, SIZE);
		
		long long result = solve(arr, SIZE);

		if (answer == result) SCORE += 10;
	}
	printf("RESULT : %d\n", SCORE);
	return 0;
}