#include<cstring>
#include<cstdio>

int GoRCCar()
{
    int t;
    scanf("%d\n", &t);

    int v; int s, comm, dv, n;
    for(int tc = 1; tc <= t; tc++)
    {
        v = 0;
        s = 0;
        scanf("%d\n", &n);
        
        while(n--)
        {
            scanf("%d", &comm);
            switch(comm)
            {
                case 0:
                dv = 0;
                break;
                case 1:
                scanf(" %d\n", &dv);
                break;
                case 2:
                scanf(" %d\n", &dv);
                dv = -dv;
                break;
            }
            v += dv;
            v = v > 0 ? v : 0;

            s += v;
        }

        printf("#%d %d\n", tc, s);
    }

    return 0;
}