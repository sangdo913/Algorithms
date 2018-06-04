#include<stdio.h>
#include<string.h>

int length(char *num)
{
    int i = 0;
    while(num[i++]);
    return i-1;
}

char sum(char a, char b, bool &up)
{
    int s = a + b - '0' - '0' + up;
    
    up = s / 10;
    return (s % 10) + '0';
}

int TwoNumAdd()
{
    char num1[103] = {'0'}, num2[103] = {'0'}, res[103];
    int t, tc, len1, len2;
    bool up;

    scanf("%d\n", &t);

    for(tc = 1; tc <= t; tc++)
    {
        scanf("%s %s\n", num1 + 1, num2 + 1);
        len1 = length(num1 + 1);
        len2 = length(num2 + 1);

        int longer = len1 > len2 ? len1 : len2;
        up = false;
        for(int i = 0; i < longer; i++)
        {
            int i1 = len1 - i > 0 ? len1 - i : 0;
            int i2 = len2 - i > 0 ? len2 - i : 0;

            res[longer - i] = sum(num1[i1], num2[i2], up);
        }
        
        res[longer + 1] = 0;
        res[0] = up + '0';

        printf("#%d %s\n", tc, res + !up);
    }
    return 0;
}