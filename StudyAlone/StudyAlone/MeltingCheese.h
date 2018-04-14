#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

struct Info
{
    int map[102][102],n,m;
    typedef struct Cod {int r, c;} cod;
    const int dr[4] = {-1,1,0,0};
    const int dc[4] = {0,0,-1,1};

    queue<cod> cheeses;
    queue<cod> air;

    void init()
    {
        cin >> n >> m;

        memset(map,-1,sizeof(map));

        for(int r = 1; r <= n; r++)
        {
            for(int c = 1; c <= m; c++)
            {
                cin >> map[r][c];
                if(map[r][c])
                {
                    cod p;
                    p.r = r;
                    p.c = c;
                    cheeses.push(p);
                }
            }
        }
        
        cod p;
        p.r = p.c = 1;
        air.push(p);
        spreadAir();
    }

    void melt()
    {
        int size = cheeses.size();
        cod now, next;
        bool isMelt[102][102] = {false};

        while(size--)
        {
            now = cheeses.front();
            cheeses.pop();
    
            int cnt = 0;
        
            for(int d = 0; d < 4; d++)
            {
                next.r = now.r + dr[d];
                next.c = now.c + dc[d];

                if(map[next.r][next.c] == 2 && !isMelt[next.r][next.c])
                {
                    cnt++;
                }          
            }

            if(cnt >= 2)
            {
                map[now.r][now.c] = 2;
                isMelt[now.r][now.c] = true;
                air.push(now);
            }

            else
            {
                cheeses.push(now);
            }
        }
    }

    void spreadAir()
    {
        cod now, next;

        while(air.size())
        {
            now = air.front();
            air.pop();

            for(int d = 0 ; d < 4; d++)
            {
                next.r = now.r + dr[d];
                next.c = now.c + dc[d];

                if(map[next.r][next.c] == 0)
                {
                    map[next.r][next.c] = 2;
                    air.push(next);
                }
            }    
        }
    }

    bool check()
    {
        return cheeses.size();
    }
} info;

int MeltingCheese()
{
    info.init();
    int time = 0;
    while(info.check())
    {  
        time++;
        info.melt();
        info.spreadAir();
    }

    cout << time << '\n';
    return 0;
}