#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;

struct RedGreenWeakInfo
{
    char map[102][102];
    bool visit[102][102];

    typedef enum {R = 0, G = 1, B = 2} color;
    typedef struct Coord{int r, c;} cod;

    const char p[2][3] = {{'R','G','B'}, {'G','R','B'}};
    int conv['Z'];
    const int dr[4] = {-1,1,0,0};
    const int dc[4] = {0,0,-1,1};

    int n;

    void init()
    {
        memset(map,0,sizeof(map));
        memset(visit,false, sizeof(visit));
        scanf("%d\n", &n);

        conv['R'] = R;
        conv['G'] = G;
        conv['B'] = B;
        
        for(int i = 1; i <= n; i++)
        {
            scanf("%s\n", map[i] + 1);
        }
    }

    void check(int res[2])
    {
        for(int t = 0; t < 2; t++)
        {
            memset(visit,false,sizeof(visit));

            for(int i = 1; i <= n; i++)
            {
                for(int j = 1; j <= n; j++)
                {
                    if(visit[i][j]) continue;
                    visit[i][j] = true;
                    make(map[i][j], p[t][conv[map[i][j]]], {i,j});
                    
                    res[t]++;
                }
            }
        }
    }

    void make(char color1, char color2, const cod& pos)
    {
        cod now, next;
        queue<cod> que;
        que.push(pos);

        while(que.size())
        {
            now = que.front();
            que.pop();

            for(int d = 0; d < 4; d++)
            {
                next.r = now.r + dr[d];
                next.c = now.c + dc[d];

                if(visit[next.r][next.c]) continue;
                if(map[next.r][next.c] == color1 || map[next.r][next.c] == color2)
                {
                    visit[next.r][next.c] = true;
                    que.push(next);
                }
            }
        }
    }

} info;

int RedGreenWeak()
{
    info.init();
    int res[2] = {0};

    info.check(res);
    printf("%d %d\n", res[0], res[1]);

    return 0;
}