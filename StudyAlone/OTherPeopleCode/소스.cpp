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
		} while (1); //���δٸ� ���ڸ� �̱����� ��� �����ϱ����� do while ���ѹݺ����� �Ͽ���.
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
	} while (1); //���δٸ� ���ڸ� �̱����� ��� �����ϱ����� do while ���ѹݺ����� �Ͽ���.
	do {
		printf("3���� ���� ���� :");

		selectNum(USER, B); // USER : ����� �Է�, AUTO : ���� �ֱ�
		
		if ((A[0] == B[0]) && (A[1] == B[1]) && (A[2] == B[2]))  // ��� ������ ���ӳ�
		{
			printf("game over \n");
			break;
		}
		else                  //�׷��� ������ �ݺ��� ����
		{
			strike = 0;
			ball = 0;   // ���� �ʱ�ȭ �� ������ ����ڰ� ���ӵ��߿� �õ��� Ƚ�������� ��� ������ �������� ������.
			for (j = 0; j<3; j++)
			{
				for (k = 0; k<3; k++)
				{
					if (A[j] == B[k])     // ó������ ������ �迭�� ���� �ʾҴµ� a,b,c,d,e,f �� �ϸ� ������ �ʹ� ������� �ϴ� ������ ���ڶ� ����ڰ� ������ ���ڰ� ���� ������ �������.
					{
						if (j == k) //�迭�� ���� ���� �迭 ������ ������ strike�� 1�߰� �׷��� ������ ball�߰�
							strike++;
						else
							ball++;
					}
				}
			}

			printf("%d���� ������� : %d strike, %d ball !!\n\n", i, strike, ball);
		}
		i++;
	} while (1);
}