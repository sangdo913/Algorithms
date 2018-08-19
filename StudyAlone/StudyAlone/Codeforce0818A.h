#pragma once
#include<cstdio>
#include<cstring>

char conv[256][2];
char str[101];
int Codeforce0818A() {
	for (int i = 'a'; i <= 'z'; i++) {
		conv[i][0] = ((i - 'a' + 'z' - 'a')) % 26 + 'a';
		conv[i][1] = ((i - 'a') + 1) % 26 + 'a';
	}

	int n;
	scanf("%d\n", &n);

	while (n--) {
		int len;
		scanf("%d\n", &len);

		scanf("%s\n", str);
		bool res = true;
		for (int i = 0; i < len / 2; i++) {
			if ((conv[str[i]][0] == conv[str[len - i - 1]][0]) || (conv[str[i]][0] == conv[str[len - i - 1]][1]) || (conv[str[i]][1] == conv[str[len - 1 - i]][0]) || (conv[str[i]][1] == conv[str[len - 1 - i]][1])) {
				continue;
			}
			else {
				res = false;
				break;
			}
		}
		res ? printf("YES\n") : printf("NO\n");
	}
	return 0;
}