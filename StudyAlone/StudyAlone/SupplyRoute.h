#include<iostream>
#include<queue>
#include<cstdio>
#include<cstring>

using namespace std;

struct SUPPLYROUTE
{  
    char map[102][102];
    int times[102][102], size;
    bool enQueue[102][102];

    typedef struct COD
    {
        int r, c, time;
    } COD;

    int getMin()
    {
        const int dr[4] = {-1,1,0,0};
        const int dc[4] = {0,0,-1,1};

        COD dt, st;
        st.time = times[1][1] = 0;
        dt.c = dt.r = size;
        st.r = st.c = 1;

        queue<COD> que;
        que.push(st);    

        while(que.size())
        {
            COD now = que.front();
            que.pop();

            for(int d = 0; d < 4; d++)
            {
                COD next;
                next.r = now.r + dr[d];
                next.c = now.c + dc[d];

                if(map[next.r][next.c] == 0) continue;
        
                next.time = now.time + map[next.r][next.c] - '0';
                if(next.time >= times[next.r][next.c]) continue;                


                if(next.time < times[next.r][next.c])
                {
                   times[next.r][next.c] = next.time;
                   que.push(next); 
                }
            }
        }

        return times[dt.r][dt.c];
    }

    void init()
    {
        memset(map, 0, sizeof(map));
        scanf("%d\n", & size);
        for(int i = 1; i <= size; i++)
        {
            scanf("%s\n", map[i] + 1);
            for(int j = 1; j <= size; j++)
            {
                times[i][j] = 97654321;
            }
        }

    }
} info;

int SupplyRoute()
{
    int t;
    scanf("%d\n", &t);
    for(int tc = 1; tc <= t; tc++)
    {
        info.init();
        printf("#%d %d\n", tc, info.getMin());
    }
    return 0;
}