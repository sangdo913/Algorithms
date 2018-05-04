#include<cstdio>

int length(char* str)
{
    int res = 0;
    while(*str)
    {
        res++;
        str++;
    }
    return res;
}
int Base64Decode()
{
    char str[100001];   
    int t, len;
    scanf("%d\n", &t);
    for(int tc = 1; tc <= t; tc++)
    {
        scanf("%s", str);
        len = length(str);  
    }
    return 0;
}

/*
T G l m
19          6           37          38
010011      000110      100101      100110

01001100 01101001 01100110
76



71 = 64 + 4 + 2 + 1

108 = 64 + 32 + 8 + 4
*/