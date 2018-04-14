#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

struct Info
{
    int map[302][302];
    int n , m;

    const int dr[4] = {-1,1,0,0};
    const int dc[4] = {0,0,-1,1};

    typedef struct Cod {int r,c;} cod;

    queue<cod> ice;

    void init()
    {
        cin >> n >> m;

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

                    ice.push(p);
                }
            }
        }
    }

    void melt()
    {
        int size = ice.size();

        bool isMelt[302][302] = {false};
        cod now, next;

        while(size--)
        {
            now = ice.front();
            ice.pop();

            int cnt  = 0;
            for(int d = 0; d < 4; d++)
            {
                next.r = now.r + dr[d];
                next.c = now.c + dc[d];

                if(map[next.r][next.c] <= 0 && !isMelt[next.r][next.c]) cnt++;
            }
            map[now.r][now.c] -= cnt;
            isMelt[now.r][now.c] = map[now.r][now.c] <= 0;

            if(map[now.r][now.c] > 0) ice.push(now);
        }
    }

    int isOne()
    {
        int size = ice.size();

        if(size == 0) return -1;

        cod now, next;
        now = ice.front();

        queue<cod> que;
        que.push(now);

        int checkSize = 0;
        bool visit[302][302] = {false};
        visit[now.r][now.c] = true;

        while(que.size())
        {
            now = que.front();
            que.pop();

            checkSize++;

            for(int d = 0; d < 4; d++)
            {
                next.r = now.r + dr[d];
                next.c = now.c + dc[d];

                if(map[next.r][next.c] > 0 && !visit[next.r][next.c])
                {
                    visit[next.r][next.c] = true;
                    que.push(next);
                }
            }
        }

        return checkSize == size;
    }
} info;

int IceMountain()
{
    info.init();

    int time = 0;
    int check;
    while((check = info.isOne()) == 1)
    {
        time++;
        info.melt();
    }
    cout << (check == -1 ? 0 : time) << '\n'; 
    return 0;
}