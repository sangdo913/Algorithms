#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>

using namespace std;

struct FinalSwimLeauge
{
    typedef struct Cod
    {
        int r;
        int c;
    } cod;

    int map[17][17];
    bool visit[3][17][17];
    int n;

    cod pos[2];

    const int dr[5] = {-1,1,0,0,0};
    const int dc[5] = {0,0,-1,1,0};
    const int st = 0;
    const int dt = 1;
    const int wall =1;
    const int tonado = 2;

    void init()
    {
        scanf("%d", &n);
        for(int r = 0; r <= n + 1; r++)
        {
            for(int c = 0; c <= n + 1; c++)
                map[r][c] = wall; 
        }

        memset(visit,false,sizeof(visit));

        for(int r = 1; r <= n; r++)
            for(int c = 1; c <= n; c++)
            {
                scanf("%d", &map[r][c]);
            }

        scanf("%d %d\n", &pos[st].r, &pos[st].c);
        scanf("%d %d\n", &pos[dt].r, &pos[dt].c);
        pos[st].r++; pos[st].c++; pos[dt].c++; pos[dt].r++;
    }

    int getMin()
    {
        queue<cod> que;

        int size = 1;
        int t = 0;
        bool activate = true;
        
        que.push(pos[st]);
        cod now, next;
        
        while(que.size())
        {
            now = que.front();
            que.pop();

            if(now.r == pos[dt].r && now.c == pos[dt].c) return t;

            for(int d = 0; d < 5; d++)
            {
                next.r = now.r + dr[d];
                next.c = now.c + dc[d];

                if(map[next.r][next.c] == wall) continue;
                if(map[next.r][next.c] == tonado && activate) continue;
                if(visit[t%3][next.r][next.c]) continue;

                visit[t%3][next.r][next.c] = true;
                que.push(next);
            }

            if(!visit[t%3][now.r][now.c])
            {
                visit[t%3][now.r][now.c] = true;
                que.push(now);
            }

            size--;
            if(size == 0)
            {
                size = que.size();
                t++;
                activate = t%3 != 2;
            }
        }
        return -1;
    }
} info;

int FinalSwimLeague()
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