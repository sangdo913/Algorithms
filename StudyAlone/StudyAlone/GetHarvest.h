#include<stdio.h>

inline int abs(int i)
{
    return i > 0 ? i : -i;
}

int GetHarvest()
{
    int t, n, pos, len, res, value;
    scanf("%d\n", &t);
    for(int tc = 1; tc <= t; tc++)
    {
        res = 0;
        scanf("%d\n", &n);
        pos = n >> 1;

        for(int r = 0; r < n; r++)
        {
            for(int c = 0; c < n; c++)
            {
                len = abs(r - pos) + abs(c - pos);
                scanf("%1d\n", &value);
                res += len > pos ? 0 : value; 
            }
        }
        printf("#%d %d\n", tc, res);
    }
    return 0;
}