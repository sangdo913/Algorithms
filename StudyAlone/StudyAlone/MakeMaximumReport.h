//4466. 최대 성적표 만들기 https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWOUfCJ6qVMDFAWg&categoryId=AWOUfCJ6qVMDFAWg&categoryType=CODE

#include<stdio.h>
#include<string.h>

int scores[101];

int find(int value, int size)
{
    int l = 0; int r = size-1;
    while(l <= r)
    {
        int m = (l + r) >> 1;

        if(scores[m] < value )
        {
            l = m + 1;
        }
        else
        {
            r = m - 1;
        }
    }

    return r;
}
int MakeMaximumRepot()
{
    int t;

    scanf("%d\n", &t);
    for(int tc = 1; tc <= t; tc++ )
    {
        memset(scores, 0, sizeof(scores));
        int n, k;
        scanf("%d %d\n", &n, &k);

        int idx = 0, input;
        while(n--)
        {
            scanf("%d\n", &input);
            scores[input]++; 
        }

        int res = 0, score = 100;
        while(k)
        {
            if(scores[score]) 
            {
               res += score;
               scores[score]--; 
               k--;
            }
            else
            {
                score--;
            }
        }
        printf("#%d %d\n", tc, res);
    }
    return 0;
}