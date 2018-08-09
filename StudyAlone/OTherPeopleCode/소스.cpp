#include<cstdio>

int main() {
	int n, i = 0;
	while (scanf("\n%d\n", &n) != -1) {
		printf("#%d %d\n", i++, n);
	}
	return 0;
}