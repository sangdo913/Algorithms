#include<cstdio>

int DeockHwanPopCard()
{
    int t;
    scanf("%d\n", &t);
    long long n, k;
    for(int tc = 1; tc <= t; tc++)
    {
        scanf("%lld %lld\n", &n, &k);
        int res = ++k % 2, now = 3;

        while(now <= n)
        {
            int st = k % now;
            res = (st + res) % now;
            now++;
        }
        printf("#%d %d\n", tc, ++res);
    }

    return 0;
}