#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;



struct SwimLeague_Info
{
    typedef struct {
        int r;
        int c;
    } Cod;
    Cod pos[2];
    int map[17][17];
    bool visit[17][17];
    int n;
    const int st = 0;
    const int dt = 1;
    const int row = 0;
    const int col = 1;
    const int wall  = 1;
    const int dr[5] = {-1,1,0,0,0};
    const int dc[5] = {0,0,-1,1,0};
    void init()
    {
        scanf("%d", &n);
        memset(visit,false,sizeof(visit));

        for(int i = 0; i <= n; i++)
        {
            for(int j = 0 ; j <= n; j++)
                map[i][j] = wall;
        }

        for(int r = 1; r <= n; r++)
        {
            for(int c = 1; c <= n; c++)
            {
                scanf("%d", &map[r][c]);
            }
        }

        scanf("%d %d\n", &pos[st].r, &pos[st].c);
        scanf("%d %d\n", &pos[dt].r, &pos[dt].c);

        pos[st].r++; pos[st].c++; pos[dt].r++; pos[dt].c++;
    }

    int getMin()
    {
        queue<Cod> que;
        int size = 1;
        int t  = 0;
        Cod now, next;
        que.push(pos[st]);

        while(que.size())
        {
            now = que.front();
            que.pop();

            if(now.r == pos[dt].r && now.c == pos[dt].c) return t;

            for(int d = 0; d < 4; d++)
            {
                next.r = now.r + dr[d];
                next.c = now.c + dc[d];

                if(map[next.r][next.c] == wall) continue;
                if(visit[next.r][next.c]) continue;
                visit[next.r][next.c] = true;

                que.push(next);
            }

            size --;
            if(size == 0)
            {
                size = que.size();
                t++;
            }   
        }

        return -1;
    }
}info;

int SwimLeague()
{
    int t;
    scanf("%d", &t);

    for(int tc = 1; tc <= t; tc++)
    {
        info.init();
        int res = info.getMin();
        printf("#%d %d\n", tc, res);
    }
    return 0;
}