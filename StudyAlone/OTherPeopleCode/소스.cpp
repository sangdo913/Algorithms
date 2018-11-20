#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define INIT_ARR_SIZE 2

void add(int *size, int *arr) {
	int i;
	int newSize = 2 * (*size);
	printf("debug new size: %d\n", newSize);
	//int *temp = (int *)malloc(sizeof(int)*newSize);

	//for (i = 0; i < (*size); i++)
	//	temp[i] = arr[i];
	//free(arr);
	//arr = temp;
	//for (int j = 0; j < *size; j++)
	//	printf("[%d] ", arr[j]);
	puts("");
	*size = newSize;
}

int main(void) {
	int *arr = (int *)malloc(sizeof(int)*INIT_ARR_SIZE);
	int size = INIT_ARR_SIZE;
	int i = 0, input, sum = 0;
	int j;
	while (size) {
		printf("enter the num: ");
		scanf("%d", &input);

		if (input == -1)
			break;
		arr[i] = input;
		i++;
		if (i == size) {
			for (j = 0; j < size; j++) {
				printf("%d ", arr[j]);
			}
			printf("\n");
			add(&size, arr);
			puts("after add");
			for (j = 0; j < size; j++)
				printf("<%d> ", arr[j]);
			puts("");
		}
	}

	for (i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}

	return 0;
}