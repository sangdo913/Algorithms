#include<iostream>
#include<queue>
using namespace std;

    
typedef struct 
{
    int x;
    int y;
} pos;


int GetOuter()
{

    bool visit[52][52];
    int map[52][52];
    int t,n,m,l;
    int time;
    cin >>t;


    pos enter;

    const int dx[4] = {0,1,0,-1};
    const int dy[4] = {-1,0,1,0};
    const int streetType[8] = {0, 0b1111, 0b0101, 0b1010,0b0011,0b0110,0b1100,0b1001};
    for(int tc=1;tc<=t;tc++)
    {
        scanf("%d %d %d %d %d",&n,&m,&enter.y,&enter.x,&l);
        enter.y++;
        enter.x++;
        queue<pos> que;
        int res;
        int cnt,check;

        for(int i =0; i<=n+1; i++)
        {
            for(int j = 0;j<=m+1;j++)
            {
                map[i][j] = 0;
                visit[i][j] = false;
            }
        }

        for(int i =1;i<=n;i++)
        {
            for(int j = 1; j<=m;j++)
            {
                scanf("%d", &map[i][j]);
            }
        }
        
        time = 1;
        check = 1;
        res = 1;
        que.push(enter);
        pos next;
        pos now;
        int strType;
        visit[enter.y][enter.x] = true;
        check = 1;
        while((time != l) && !que.empty())
        {
            now = que.front();
            que.pop();
            
            strType = streetType[map[now.y][now.x]];

            for(int i = 0; i<4;i++)
            {
                if((strType>>i)&1)
                {
                    next.x = now.x+dx[i];
                    next.y = now.y+dy[i];
                    
                    if((visit[next.y][next.x] == false) && ((streetType[map[next.y][next.x]] >>((i+2)%4))&1))
                    {
                        visit[next.y][next.x] = true;
                        que.push(next);
                    }
                }
            }

            check--;

            if(check == 0)
            {
                check = que.size();
                time++;
                res+= que.size();
            }
        }
        printf("#%d %d\n",tc, res);
    }
    return 0;
}