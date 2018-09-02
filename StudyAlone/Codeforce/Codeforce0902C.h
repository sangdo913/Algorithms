#pragma once
#include<string>
#include<cstdio>

using namespace std;
char str[2][1000001];

int Codeforce0902C() {
	int n;
	
	scanf("%d\n%s\n%s", &n, str[0], str[1]);
	int price = 0;
	for (int i = 0; i < n; i++)
	{
		if (str[0][i] == str[1][i]) continue;
		if (str[0][i + 1] != str[1][i + 1]) {
			if (str[0][i] != str[0][i + 1])
			{
				str[0][i + 1] = str[0][i];
				price++;
				continue;
			}
		}

		price++;
	}
	printf("%d\n", price);
	return 0;


}