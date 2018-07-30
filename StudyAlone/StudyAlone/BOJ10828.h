//https://www.acmicpc.net/problem/10828
#pragma once
#include<cstdio>

bool strcmp(char *str1, char *str2) {
	while (*str1 && *str2 && *str1 == *str2) {
		str1++; str2++;
	}
	return *str1 == *str2;
}

int stack[10000], top;
char comm[5][10] = { "push", "pop", "size", "empty", "top" };

int STACK() {
	int n, in;
	char query[10];

	scanf("%d\n", &n);
	while (n--) {
		scanf("%s\n", query);

		for (int i = 0; i < 5; i++) {
			if (strcmp(comm[i], query)){
				switch (i) {
				case 0:
					scanf("%d\n", &in);
					stack[top++] = in;
					break;
				case 1:
					in = top ? stack[--top] : -1;
					printf("%d\n", in);
					break;
				case 2:
					printf("%d\n", top);
					break;
				case 3:
					printf("%d\n", top == 0);
					break;
				case 4:
					in = top ? stack[top - 1] : -1;
					printf("%d\n", in);
					break;
				}
				
				break;
			}
		}
	}
	return 0;
}