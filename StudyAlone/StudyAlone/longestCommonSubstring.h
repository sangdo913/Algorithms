#include<cstdio>

char x[4002];
char y[4002];
int dp[4001][4001] = {0};

int longestCommonSubstring()
{
    scanf("%s\n", x + 1);
    scanf("%s\n", y + 1);
    int i, j;
    int max = 0;
    for(i = 1; x[i]; i++)
    {
        for(j = 1; y[j]; j++)
        {
            if(x[i] == y[j])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                max = max > dp[i][j] ? max : dp[i][j];
            }
        }
    }

    printf("%d\n", max);
    return 0;
}