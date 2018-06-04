#include<cstdio>

int ArrMaxSum()
{
    int arr[100][100];
    int t, tc = 10;

    int row;

    typedef enum type {DIAGONAL1 = 100, DIAGONAL2, ROW, SIZE};
    while(tc--)
    {
        int maxes[103] = { 0 };
        scanf("%d\n", &t);
        for(int i = 0; i < 100; i++)
        {
            row = 0;
            for(int j = 0; j < 100; j++)
            {
                scanf("%d \n", & arr[i][j]);
                maxes[j] += arr[i][j];
                row += arr[i][j];
                if(i == j) maxes[DIAGONAL1] += arr[i][j];
                else if(i + j == 99) maxes[DIAGONAL2] += arr[i][j];
            }

            maxes[ROW] = maxes[ROW] < row ? row : maxes[ROW];
        }

        int max = maxes[0];
        for(int i = 1 ; i < SIZE; i++)
        {
            max = max > maxes[i] ? max : maxes[i];
        }
        printf("#%d %d\n", t, max);
    }
    return 0;
}