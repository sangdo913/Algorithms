#include<cstdio>

int AreumThrowStone()
{
    int min, cnt;
    int t;
    scanf("%d\n", &t);
    for(int tc = 1; tc <= t; tc++)
    {
        int n;
        cnt = 0;
        scanf("%d\n", &n);
        
        min = 1000000;
        int dist;
        while(n--)
        {
            scanf("%d ", &dist);
            dist = dist < 0 ? -dist : dist;
            
            if(dist < min)
            {
                min = dist;
                cnt = 1;
            }
            else if(dist == min)
            {
                cnt ++;
            }
        }

        printf("#%d %d %d\n", tc, min, cnt);
    }
    return 0;
}