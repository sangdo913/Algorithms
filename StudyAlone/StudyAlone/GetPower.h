#include<cstdio>

int GetPower()
{
    int n, m, t;
    int tc = 10;
    
    while(tc--)
    {
        scanf("%d\n %d %d\n", &t, &n, &m);
        int res = 1;
        while(m--)
        {
            res *= n;
        }

        printf("#%d %d\n", t, res);
    }
    return 0;
}