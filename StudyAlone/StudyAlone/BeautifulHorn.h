#include<stdio.h>
#include<string.h>

int BeautifulHorn()
{
    int t, n, m;

    scanf("%d\n", &t);

    for(int tc = 1; tc <= t; tc++)
    {
        scanf("%d %d\n", &n, &m);
        int two = n - m;
        printf("#%d %d %d\n", tc, m - two, two);
    }
    
    return 0;
}