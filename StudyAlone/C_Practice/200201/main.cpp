/*
[Score의 출력값이 적을수록 더 높은 점수를 받는다]
​
main 코드를 분석하여 더 높은 점수를 받도록 solution.cpp에 코딩.
stack 메모리: 1MB
main.cpp는 수정할 수 없다.
solution.cpp에 전역변수, static 변수 사용불가
solution.cpp에 동적할당 사용 금지
solution.cpp에 대한 코드리뷰를 철저하게 진행할 것입니다.
*/

#include<ctime>
#include<iostream>
#include<cstdlib>
#include"user.cpp"
using namespace std;
#define SIZE 1048576
#define MAX_COUNT 2048

extern void test(unsigned int data[SIZE]);
unsigned int mdata[SIZE];

long long Score;
short buf[1024];

unsigned int bak_data[SIZE];
unsigned int num[MAX_COUNT];

void ssort(short data[1024], int len)
{
	if (len < 2)
		return;

	int mid = len / 2;

	ssort(data, mid);
	ssort(data + mid, len - mid);

	int i = 0, j = mid, count = 0;

	while (i < mid && j < len) {
		if (data[i] < data[j]) {
			buf[count++] = data[i++];
		}
		else {
			buf[count++] = data[j++];
		}
	}

	while (i < mid) {
		buf[count++] = data[i++];
	}

	while (j < len) {
		buf[count++] = data[j++];
	}

	for (int a = 0; a < len; ++a) {
		data[a] = buf[a];
	}
}

void test_sort(short data[1024])
{
	clock_t start = clock();
	ssort(data, 1024);
	Score -= clock() - start;
}
int TC = 10;

int main()
{
	Score = 0;
	srand(time(0));
	while (TC--) {
		for (register int i = 0; i < MAX_COUNT; ++i) {
			num[i] = ((long long)rand() * 1007) &0xffff;
		}

		for (register int i = 0; i < SIZE; ++i) {
			int idx1 = rand() % MAX_COUNT;
			int idx2 = rand() % MAX_COUNT;

			bak_data[i] = mdata[i] = (num[idx1] << 16) + num[idx2];
		}

		clock_t start = clock();
		test(mdata);
		Score += clock() - start;

		for (register int i = 0; i < SIZE - 1; ++i) {
			if (mdata[i] < mdata[i + 1]) {
				Score += 10000000;
			}
		}

		for (register int i = 0; i < 10; ++i) {
			int idx = rand() % SIZE;

			bool check = false;
			for (register int j = 0; j < SIZE; ++j) {
				if (mdata[j] == bak_data[idx]) {
					check = true;
					break;
				}
			}
			if (!check) {
				Score += 10000000;
			}
		}
	}
	std::cout << (long long)Score * 1000 / CLOCKS_PER_SEC << "\n";

	return 0;
}