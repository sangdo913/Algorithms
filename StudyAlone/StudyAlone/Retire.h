#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;
typedef enum {Time = 0, Price = 1, size} type;
int info[2][16];
int retireMax[16];

inline int Retire_Max(int i1, int i2)
{
    return i1 > i2 ? i1 : i2;
}

int Retire()
{
    memset(retireMax, 0, sizeof(retireMax));
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d %d\n", &info[Time][i], &info[Price][i]);
        if(info[Time][i] + i - 1 <= n) retireMax[info[Time][i] + i - 1] = Retire_Max(retireMax[info[Time][i] + i - 1], retireMax[i-1] + info[Price][i]);
        retireMax[i] = Retire_Max(retireMax[i], retireMax[i-1]);
    }

    printf("%d\n", retireMax[n]);

    return 0;
}