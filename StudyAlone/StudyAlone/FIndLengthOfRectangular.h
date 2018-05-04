#include<cstdio>

int FIndLengthOfRectangular()
{
    int t;
    scanf("%d\n", &t);
    for(int tc = 1; tc <= t; tc++)
    {
        bool isOdd[101] = {false};
        
        int num;
        for(int i = 0 ; i < 3; i++)
        {
            scanf("%d ", &num);
            isOdd[num] = !isOdd[num];
        }

        int i = 1;
        while(!isOdd[i])
        {
            i++;
        }
        printf("#%d %d\n", tc, i);
    }
    return 0;
}