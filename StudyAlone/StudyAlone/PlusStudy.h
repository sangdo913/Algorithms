#include<cstdio>

int PlusStudy()
{
    int t;
    
    scanf("%d\n", &t);
    int res = 0, tc, score, i ;

    for(tc = 1; tc <= t; tc++)
    {
        res = 0;
        for(i = 0; i < 5; i++)
        {
            scanf("%d ", &score);
            res += score > 40 ? score : 40;
        }

        printf("#%d %d\n", tc, res / 5);
    }
    return 0;
}