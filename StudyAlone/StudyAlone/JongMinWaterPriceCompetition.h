#include<cstdio>

int JongMinWagterPriceCompetition()
{
    int p,q,r,s,w;

    int t;
    scanf("%d\n", &t);

    for(int tc = 1; tc <= t; tc++)
    {
        scanf("%d %d %d %d %d\n", &p, &q, &r, &s, &w);

        int p1 = w * p;
        int p2 = q;
        int remain = w - r > 0 ? w - r : 0;
        p2 += remain * s;

        printf("#%d %d\n", tc, p1 < p2 ? p1 : p2);        
    }
    return 0;
}