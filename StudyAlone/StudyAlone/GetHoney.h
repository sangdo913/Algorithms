#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
using namespace std;

struct GetHoney_Info
{
    int map[10][10];
    int prevX;
    int prevY;
    int x;
    int y;
    int n;
    int m;
    int c;
    int max;
    
    void init()
    {
        max = 0;
        for(int i = 0; i<n; i++)
        {
            for(int j = 0 ; j<n;j++)
            {
                cin >> map[i][j];
            }
        }
    }
    int getMax(int i1, int i2)
    {
        return i1 > i2? i1 : i2;
    }

    int getValueOne(int x, int y)
    {
        int max = 0;
       for(int i = 1 ; i< (1<<m); i++)
       {
           int temp = 0;
           int value = 0;           
           int visit = i;
           
           for(int h = 0 ; h<m; h++)
           {
                if(visit&1)
                {
                    temp +=map[y][x+h];
                    value+= map[y][x+h]*map[y][x+h];
                }
                if(temp > c) break;
                visit >>= 1;
           }
           if(temp > c) continue;
            max = getMax(max, value);
       }
        return max;
    }
    int getValue(int x, int y)
    {
        return getValueOne(x,y) + getValueOne(prevX, prevY);
    }
} GetHoney_info;

void GetMax(int bulk, int x, int y)
{
    if(bulk == 2)
    {
        if(x < GetHoney_info.n)
            GetHoney_info.max = GetHoney_info.getMax(GetHoney_info.getValue(x,y),GetHoney_info.max);

        return;
    }

    for(int i = y ; i< GetHoney_info.n; i++)
    {
        for(int j = i == y ? x : 0 ; j < GetHoney_info.n-GetHoney_info.m+1; j++)
        {
            
            if(!bulk)
            {
                GetHoney_info.prevX = j; GetHoney_info.prevY= i;
                GetMax(bulk+1, j+GetHoney_info.m,i);
            }
            else
            {
                GetMax(bulk+1, j,i);
            }
        }
    }

}

int GetHoney()
{
    int T;
    cin>>T;
    GetHoney_Info& info = GetHoney_info;
    for(int tc=1 ; tc<=T;tc++)
    {
        cin >> info.n >> info.m >> info.c;

        info.init();

        GetMax(0,0,0);

        printf("#%d %d\n",tc, info.max);
    }
    return 0;
}