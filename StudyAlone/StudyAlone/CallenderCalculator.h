#include<cstdio>

int CallenderCalculator()
{
    int month[2];
    int day[2];
    
    const int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int t;
    scanf("%d\n", &t);
    for(int tc = 1; tc <= t; tc++)
    {
        scanf("%d %d ", &month[0], &day[0]);
        scanf("%d %d\n", &month[1], &day[1]);

        int res = 0;
        for(int m = month[0]; m <= month[1]; m++)
        {
            res += days[m];
        }
        res -= days[month[1]] - day[1] + day[0];
        res++;
        printf("#%d %d\n", tc, res);
    }
    return 0;
}