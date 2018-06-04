#include<stdio.h>
#include<math.h>

struct Info{
    long long measures[100001][2];
    long long a, b, n;
    void setMeasure()
    {
        for(int i = 1; i <= 100000; i++)
        {
            int sq = sqrt(i);

            while(sq >= 1)
            {
                if(i % sq == 0)
                {
                    measures[i][0] = sq;
                    measures[i][1] = i / sq;
                    break;
                }
                sq--;
            }
        }
    }    
    
    void init()
    {
        scanf("%d %d %d\n", &n, &a, &b);
    }

    long long cal(int i)
    {
        return a * (measures[i][1] - measures[i][0]) + b * (n - measures[i][0] * measures[i][1]);
    }

    long long min(long long l1, long long l2)
    {
        return l1 < l2 ? l1 : l2;
    }

    long long getMin()
    {
        long long res = 9876543210;
        for(int i = 1; i <= n; i++)
        {
            res = min(cal(i), res);
        } 

        return res;
    }
} info;

int WonJaeWallDecoration()
{
    int t;
    scanf("%d\n", &t);
    info.setMeasure();

    for(int tc = 1; tc <= t; tc++)
    {
        info.init();
        long long res = info.getMin();
        printf("#%d %lld\n", tc, res);
    }
    
    return 0;
}