#include<iostream>
#include<cstdio>

using namespace std;

struct info
{
    int arr[2][20];
    int small;
    int size[2];

    void init()
    {
        scanf("%d %d\n", size, size+1);

        for(int i = 0 ; i < 2; i++)
        {
            for(int j = 0; j < size[i]; j++)
            {
                scanf("%d ", &arr[i][j]);
            }
        }

        small = size[0] > size[1];
    }
    int getMax()
    {
        int max = 0;
        for(int i = 0; i < size[small]; i++)
        {
            max += arr[small][i] * arr[!small][i];
        }

        int tempMax;        
        for(int i = 1; i <= size[!small] - size[small] ; i++)
        {
            tempMax = 0;
            for(int j = 0; j < size[small]; j++)
            {
                tempMax += arr[small][j] * arr[!small][i + j];
            }
            max = tempMax > max ? tempMax : max;
        }
        return max;
    }
} info;

int TwoNumArr()
{
    int t;
    scanf("%d\n", &t);

    for(int tc = 1; tc <= t; tc++)
    {
        info.init();
        int res = info.getMax();
        printf("#%d %d\n", tc, res);    
    }
    
    return 0;
}