#include<cstdio>

int TimingOfLoveOfTaeHyeock()
{
    int t;
    scanf("%d\n", &t);

    for(int tc = 1; tc <= t; tc++)
    {
        int stdTime = 11*24*60 + 11*60 + 11;
        int d,h,m;
        scanf("%d %d %d\n", &d, &h, &m);
        int shock = d * 24 * 60 + h * 60 + m;

        shock -= stdTime;
        printf("#%d %d\n", tc, shock < 0 ? -1 : shock);
    }
    return 0;
}