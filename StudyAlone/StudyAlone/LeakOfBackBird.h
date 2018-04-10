#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;

struct LeakOfBackBird_Info
{
    typedef struct Pos{int r, c;} pos;

    queue<pos> check;
    queue<pos> melt;
    queue<pos> meltG;
    pos p[2];

    int n; int m;
    bool melted[1502][1502];
    bool meltedG[1502][1502];
    char map[1502][1502];

    const int dr[4] = {-1,1,0,0};
    const int dc[4] = {0,0,-1,1};

    void init()
    {
        scanf("%d %d\n", &n, &m);
        memset(meltedG,false,sizeof(meltedG));
        memset(map, -1, sizeof(map));
        memset(melted, false, sizeof(melted));
        int birdIndex = 0;
        for(int r = 1; r <= n; r++)
        {
            for(int c = 1; c <= m; c++)
            {
                scanf("%c \n",&map[r][c]);
                if(map[r][c] == 'L')
                {
                    p[birdIndex].r = r;
                    p[birdIndex++].c = c;
                    map[r][c] = '.';
                }
            }
        }

        check.push(p[0]);
        
        for(int r = 1; r <= n; r++)
        {
            for(int c = 1; c <= m; c++)
            {
                if(map[r][c] == 'X' && !melted[r][c])
                {
                    for(int d = 0; d < 4; d++)
                    {
                            pos ground;
                            ground.r = r + dr[d];
                            ground.c = c + dc[d];
                            if(map[ground.r][ground.c] == '.')
                            {
                                melted[r][c] = true;
                                melt.push({r,c});
                                break;
                            }
                    }
                }
            }
        }

        map[p[0].r][p[0].c] = 'S';
        map[p[1].r][p[1].c] = '.';
    }
    
    void iceMelt()
    {
        int size = melt.size();
        pos now, next;
        
        check = meltG;

        while(size--)
        {
            now = melt.front();
            melt.pop();
    
            map[now.r][now.c] = '.';
            for(int d = 0; d < 4; d++)
            {
                next.r = now.r + dr[d];
                next.c = now.c + dc[d];

                if(melted[next.r][next.c]) continue;
                melted[next.r][next.c] = true;
                if(map[next.r][next.c] == 'X')
                {
                    melt.push(next);
                }
            }
        }

        while(meltG.size())
        {
            now = meltG.front();
            meltG.pop();
            map[now.r][now.c] = 'S';
            melted[now.r][now.c] = true;
        }
    }

    void print()
    {
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= m; j++)
            {
                printf("%c ", map[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    bool canVisit()
    {
        pos now, next;

        while(check.size())
        {
            pos now = check.front();
            check.pop();

            if(now.r == p[1].r && now.c == p[1].c ) return true;

            for(int d = 0 ; d < 4; d++)
            {
                next.r = now.r + dr[d];
                next.c = now.c + dc[d];

                if(map[next.r][next.c] == 'X' && !meltedG[next.r][next.c])
                {
                    meltedG[next.r][next.c] = true;
                    meltG.push(next);
                }
                else if(map[next.r][next.c] == '.')
                {
                    map[next.r][next.c] = 'S';
                    check.push(next);
                }
            }
        }
        
        return false;
    }
} info;

int LeakOfBackBird()
{
    int t = 0;
    info.init();
    while(!info.canVisit())
    {
        info.iceMelt();
        t++;
    }
    printf("%d\n", t);
    return 0;
}