#pragma once
#include<cstdio>
int pa[150000][2],n;

bool canConstruct(int num) {
	bool res = true;
	for (int i = 1; i < n; i++) {
		if (pa[i][0] % num == 0 || pa[i][1] % num == 0) continue;
		else {
			return false;
		}
	}
	return true;
}

int Codeforce0819B() {
	scanf("%d\n", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d\n", &pa[i][0], &pa[i][1]);
	}

	if (canConstruct(pa[0][0])) {
		printf("%d\n", pa[0][0]);
		return 0;
	}
	else if (canConstruct(pa[0][1])){
		printf("%d\n", pa[0][1]);
		return 0;
	}

	if (pa[0][0] < pa[0][1]) {
		int temp = pa[0][0];
		pa[0][0] = pa[0][1];
		pa[0][1] = temp;
	}

	for (int i = 2; i*i <= pa[0][0]; i++) {
		if (pa[0][0] % i == 0) {

			if (canConstruct(i)) {
				printf("%d\n", i);
				return 0;
			}
			if (canConstruct(pa[0][0] / i)) {
				printf("%d\n", pa[0][0] / i);
				return 0;
			}
		}

		if (pa[0][1] % i == 0 ) {
			if(canConstruct(i)){
				printf("%d\n", i);
				return 0;
			}
			if (pa[0][1] / i != 1 && canConstruct(pa[0][1] / i)) {
				printf("%d\n", pa[0][1] / i);
				return 0;
			}
		}
	}
	printf("-1\n");
	return 0;
}