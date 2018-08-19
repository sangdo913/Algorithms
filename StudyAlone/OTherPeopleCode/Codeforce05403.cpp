#include<cstdio>
#include<cstring>

char stack[5000], top;
int dr[2] = { -1,0 };
int dc[2] = { 0,-1 };
char c[2] = { 'D','R' };
int main() {
	int n;
	scanf("%d\n", &n);

	int st[2] = { 1,1 }, dt[2] = { n,n };

	for (int i = 2 * (n - 1) - 1; i > 0; i--) {
		int q[2] = { dt[0] + dr[0], dt[1] + dc[0] };
		if (dt[0] == 1 || dt[1] == 1) break;

		char query[10] = "         ";
		char res[10];
		query[0] = '?';
		query[2] = '0' + st[0];
		query[4] = '0' + st[1];
		query[6] = '0' + q[0];
		query[8] = '0' + q[1];

		printf("? %d %d %d %d\n", st[0], st[1], q[0], q[1]);
		fflush(stdout);
		scanf("\n%s\n", res);
		if (strcmp(res, "YES") == 0) {
			dt[0] += dr[0];
			dt[1] += dc[0];
			stack[top++] = 'D';
		}
		else {
			dt[0] += dr[1];
			dt[1] += dc[1];
			stack[top++] = 'R';
		}
	}
	if (dt[0] == 1) {
		while (top < 2 * (n - 1)) {
			stack[top++] = 'R';
		}
	}
	else {
		while (top < 2 * (n - 1)) {
			stack[top++] = 'D';
		}
	}
	printf("! ");
	while (top) {
		printf("%c", stack[--top]);
	}
	printf("\n");
	return 0;
}