#include"BOJ6603.h"
#include<cstdio>

int main()
{
	//printf("%d\n", solution(2147483647));
	//BOJ6603();
	char a[4][4] = {
		{ 0b1101, 0b1001, 0b0001, 0b1111 },
		{ 0b1001, 0b0100, 0b0101, 0b1011 },
		{ 0b1111, 0b1000, 0b1011, 0b1001 },
		{ 0b1111, 0b1011, 0b1101, 0b1111 }
	};

	int b[2] = { 0,0 };
	// 인트 2개에 char 16개 넣기
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			b[(i * 4 + j) / 8] <<= 4;
			b[(i * 4 + j) / 8] |= a[i][j];
		}
	}

	char out[4][4] = { 0 };

	//인트 2개에 char 16개 빼기
	for (int i = 15; i >= 0; i--) {
		out[i / 4][i % 4] = 0b1111 & b[i / 8];
		b[i / 8] >>= 4;
	}
	int x = 1;
	return 0;
}
//2147483647