#include<cstdio>

int DeockHwanPopCard()
{
    int t;
    scanf("%d\n", &t);
    long long n, k;
    for(int tc = 1; tc <= t; tc++)
    {
        scanf("%lld %lld\n", &n, &k);
        int res = k % 2, now = 3;
        res = res == 0 ? 2 : res;

        while(now <= n)
        {
            int st = (k + 2) % now;
            res = (st + res - 1) % now;
            res = res == 0 ? now : res;
            now++;
        }
        printf("#%d %d\n", tc, res);
    }

    return 0;
}