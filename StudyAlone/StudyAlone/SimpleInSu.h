#include<cstring>
#include<cstdio>

int getCount(int num, int share)
{
    int res = 0;
    while(num % share == 0)
    {
        res++;
        num /= share;
    }
    return res;
}


int SimpleInSu()
{
    const int nums[5] = {2, 3, 5, 7, 11};
    int t, n;

    scanf("%d\n", &t);

    for(int tc = 1; tc <= t; tc++)
    {
        scanf("%d\n", &n);

        printf("#%d", tc);
        
        for(int i = 0; i < 5; i++)
        {
            printf(" %d",  getCount(n,nums[i]));
        }
        printf("\n");
    }
    return 0;
}