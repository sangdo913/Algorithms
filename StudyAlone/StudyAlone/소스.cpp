#include"CLOCKSYNC.h"
#include<stdlib.h>
#include<time.h>

int datas[100];
int temp[100];

void merge(int l, int m, int r)
{
	int i = l, j = m + 1, k = l;

	while (i <= m && j <= r)
	{
		if (datas[i] < datas[j])
		{
			temp[k++] = datas[i++];
		}
		else
		{
			temp[k++] = datas[j++];
		}
	}

	while(i <= m) temp[k++] = datas[i++];
	while (j <= r) temp[k++] = datas[j++];

	for (int i = l; i <= r; i++) datas[i] = temp[i];
}

void mergeSort(int l, int r)
{
	if (l < r)
	{
		int m = (l + r) / 2;
		mergeSort(l, m);
		mergeSort(m + 1, r);

		merge(l, m, r);
	}
}


int main()
{
	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		int len = rand() % 100 + 1;

		printf("len : %d\n", len);
		printf("before\n");
		for (int i = 0; i < len; i++)
		{
			datas[i] = rand() % 100;
			printf("%2d ", datas[i]);
		}
		printf("\n");

		mergeSort(0, len - 1);


		printf("after\n");
		for (int i = 0; i < len; i++)
		{
			printf("%2d ", datas[i]);
		}
		printf("\n\n");
	}
	
	return 0;
}
