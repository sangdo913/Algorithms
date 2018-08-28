#include<stdio.h>
#include<stdlib.h>
#include<time.h>

enum TYPE{USER, AUTO};

void selectNum(int mode, int B[3]) {
	if (mode == USER) {
		scanf("%d %d %d", &B[0], &B[1], &B[2]);
	}
	else {
		do {
			B[0] = rand() % 10;
			B[1] = rand() % 10;
			B[2] = rand() % 10;
			if ((B[0] != B[1]))
				if ((B[1] != B[2]))
					if ((B[0] != B[2]))
					{
						break;
					}
		} while (1); //서로다른 숫자를 뽑기위해 계속 실행하기위해 do while 무한반복문을 하였다.
	}
}


int main()
{
	int A[3];
	int B[3];
	int i = 1;
	int j, k;
	int strike;
	int ball;
	do {
		srand(time(NULL));
		A[0] = rand() % 10;
		A[1] = rand() % 10;
		A[2] = rand() % 10;
		if ((A[0] != A[1]))
			if ((A[1] != A[2]))
				if ((A[0] != A[2]))
				{
					printf("Start Game\n");
					break;
				}
	} while (1); //서로다른 숫자를 뽑기위해 계속 실행하기위해 do while 무한반복문을 하였다.
	do {
		printf("3개의 숫자 선택 :");

		selectNum(USER, B); // USER : 사용자 입력, AUTO : 랜덤 넣기
		
		if ((A[0] == B[0]) && (A[1] == B[1]) && (A[2] == B[2]))  // 모두 같으면 게임끝
		{
			printf("game over \n");
			break;
		}
		else                  //그렇지 않으면 반복문 실행
		{
			strike = 0;
			ball = 0;   // 변수 초기화 한 이유는 사용자가 게임도중에 시도한 횟수에따라 계속 증가를 막기위한 이유다.
			for (j = 0; j<3; j++)
			{
				for (k = 0; k<3; k++)
				{
					if (A[j] == B[k])     // 처음에는 변수를 배열로 하지 않았는데 a,b,c,d,e,f 로 하면 조건이 너무 길어져서 일단 임의의 숫자랑 사용자가 선택한 숫자가 같은 조건을 만들었다.
					{
						if (j == k) //배열의 값도 같고 배열 숫서도 같으면 strike를 1추가 그렇지 않으면 ball추가
							strike++;
						else
							ball++;
					}
				}
			}

			printf("%d번쨰 도전결과 : %d strike, %d ball !!\n\n", i, strike, ball);
		}
		i++;
	} while (1);
}