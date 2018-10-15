#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main() {
	srand(time(NULL));

	int a[10];
	char chk[10] = { 0 };
	for (int i = 0; i < 10; i++) a[i] = rand(), printf("%d ", a[i]);//scanf("%d", &a[i]);
	printf("\n");

	for (int i = 0; i < 9; i++) {
		for (int j = i + 1; j < 10; j++) {
			if (a[i] == a[j]) chk[j] = 1;
		}
	}
	for (int i = 0; i < 10; i++) {
		if (chk[i] == 0) printf("%2d", a[i]);
	}


	return 0;
}