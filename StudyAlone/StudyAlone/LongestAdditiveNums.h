#include<stdio.h>
#include<string.h>

int LonestAdditiveNums()
{
    unsigned int size, t, n, tc, i, j, nums[1000], additive[1000];
    scanf("%d\n", &t);

    for(tc = 1; tc <= t; tc++)
    {
        memset(additive, -1, sizeof(additive));

        scanf("%d\n", &n);
        size = 0;
        for(i = 0; i < n ; i++ )
        {
            scanf("%ud ", &nums[i]);
            for(j = 0; j < size; j++)
            {
                if(additive[j] > nums[i]) break;
            }
            additive[j++] = nums[i];
            size = size < j ? j : size;
        }

        printf("#%d %d\n", tc, size);
    }
    return 0;
}