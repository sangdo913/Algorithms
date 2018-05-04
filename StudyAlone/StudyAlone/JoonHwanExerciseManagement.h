#include<cstdio>

int JoonHwanExerciseManagement()
{
    int t;
    
    scanf("%d\n", &t);

    for(int tc = 1; tc <= t; tc++)
    {
        int l, u, x;
        scanf("%d %d %d\n", &l, &u, &x);
        l -= x;
        u -= x;
        
        printf("#%d ", tc);
        if(u < 0)
        {
            printf("-1");
        }
        else if(l > 0)
        {
            printf("%d", l);
        }
        else
        {
            printf("0");
        }
        printf("\n");
        
    }
    return 0;
}