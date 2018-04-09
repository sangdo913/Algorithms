#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;

struct Info
{
    int map[10][10];
    bool visit[10][10];
    int n,m;
    typedef struct {int r, c;} cod;
    const char result[3][15] = {"", "ZOMBIE","CANNOT ESCAPE"};
    typedef enum {wall = 1, virus = 2, exit = -1} type;
    const int dr[4] = {-1,1,0,0};
    const int dc[4] = {0,0,-1,1};

    cod pos;

    void init()
    {
        scanf("%d %d\n", &n, &m);
        memset(map,-1, sizeof(map));
        memset(visit,false, sizeof(visit));

        for(int r = 1; r <= n; r++)
        {
            for(int c = 1; c <= m; c++)
            {
                scanf("%d", &map[r][c]);
                if(map[r][c] == 3)
                {
                    map[r][c] = 0;
                    pos.r = r;
                    pos.c = c;
                }
            }
        }
    }

    int virusExtension()
    {
        queue<cod> que;
        cod v;
        int cnt = 0;
        for(int r = 1; r <= n; r++)
        {
            for(int c = 1; c <= m; c++)
            {
                if(map[r][c] == virus)
                {
                    v.r = r; v.c = c;
                    que.push(v);
                 }
            }
        }

        while(que.size())
        {
            v = que.front();
            que.pop();

            for(int d = 0; d < 4; d++)
            {
                if(map[v.r + dr[d]][v.c + dc[d]] == 0) 
                {
                    map[v.r + dr[d]][v.c + dc[d]] = 2;
                    cnt++;
                }
            }
        }
        return cnt;
    }
    
    int getMin()
    {
        queue<cod> que;
        int size = 1; 
        int t = 0;
        
        que.push(pos);
        bool isZombie = false;

        cod now, next;

        while(que.size())
        {
            now = que.front();
            que.pop();

            if(map[now.r][now.c] == exit) return t;
            if(map[now.r][now.c] != virus)
            {
                for(int d = 0; d < 4; d++)
                {
                    next.r = now.r + dr[d];
                    next.c = now.c + dc[d];

                    if(visit[next.r][next.c]) continue;
                    if(map[next.r][next.c] == virus) continue;
                    if(map[next.r][next.c] == wall) continue;

                    visit[next.r][next.c] = true;
                    que.push(next);
                }
            }

            size--;
            if(size ==0)
            {
                t++;
                virusExtension();
                size = que.size();
            }
        }
        
        while(virusExtension());
        
        return map[pos.r][pos.c] == virus ? -1 : -2;
    }
} info;

int SamSungBirus()
{
    int t;
    scanf("%d", &t);
    for(int tc = 1; tc <= t; tc++)
    {
        info.init();
        int res = info.getMin();
        if(res < 0)
        {
            printf("#%d %s\n", tc, info.result[-res]);
        }
        else
        {
            printf("#%d %d\n",tc, res);
        }
    }
}