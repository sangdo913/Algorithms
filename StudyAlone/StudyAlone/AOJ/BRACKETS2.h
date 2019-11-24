#include<stdio.h>

int len;
char s[10001];
char st[10000];

char pair[256];

int main() {
	int tc;
	scanf("%d", &tc);
	pair[')'] = '(';
	pair['}'] = '{';
	pair[']'] = '[';

	while (tc--) {
		int top = 0;
		scanf("%s", s);
		char* str = s;

		bool res = true;
		while(*str){
			if (*str == '(' || *str == '{' || *str == '[') {
				st[top++] = *str;
			}
			else {
				if (!top || st[top - 1] != pair[*str]) {
					res = false; 
					break;
				}
				else {
					top--;
				}
			}
			++str;
		}
		printf("%s\n", res && top == 0 ? "YES": "NO");
	}
	return 0;
}
