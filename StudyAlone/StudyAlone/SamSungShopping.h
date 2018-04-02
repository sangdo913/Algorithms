#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<deque>

using namespace std;
struct SamSungShopping_Info
{
    int n;
    int m;
    int maxS;
    int p;
    int info[2][26];
    bool maxPath[26];
    bool path[26];
    void init()
    {
        scanf("%d %d\n", &n, &m);
        memset(maxPath,false,sizeof(maxPath));
        memset(path,false,sizeof(path));

        for(int i = 1; i <= m; i++)
        {
            scanf("%d %d\n", &info[0][i], &info[1][i]);
        }
        info[0][0] = 0;
        info[1][0] = 0;
    }

    int getMaxS(int now,int price,bool path[26])
    {
        int s = 0;
        bool nextPath[26] = {false};
        bool tempMax[26] = {false};
        for(int i = now+1; i <= m; i++)
        {
            int nextPrice = price + info[0][i];
            if(nextPrice <= n) 
            {
                int nextS = getMaxS(i,nextPrice,nextPath);
                if(s < nextS )
                {
                    for(int j = 1; j <= m ; j++) tempMax[j] = nextPath[j];
                    s = nextS;
                }

                memset(nextPath,false,sizeof(nextPath));
            }
        }
        
        for(int i = 1; i <= m ; i++) path[i] = tempMax[i];
        path[now] = true;
        return s + info[1][now];
    }
}SamSungShopping_info;


int SamSungShopping()
{
    int t;
    scanf("%d", &t);
    for(int tc = 1; tc <= t; tc++)
    {
        SamSungShopping_info.init();
        bool path[26] = {false};

        int res = SamSungShopping_info.getMaxS(0,0,path);
        printf("#%d", tc);
        for(int i = 1 ; i <= SamSungShopping_info.m; i++)
        {
            if(path[i]) printf(" %d", i-1);
        }
        printf(" %d\n", res);
    }
    return 0;
}