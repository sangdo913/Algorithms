#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<queue>

using namespace std;
struct LaserComm_Cod
{
    int r,c, direct;
};

struct LaserComm_Info
{
    char map[102][102];
    bool check[2][102][102];
    const int dr[4] = {-1,1,0,0};
    const int dc[4] = {0,0,-1,1};
    int n, m;
    LaserComm_Cod cod[2];
    //0 : 좌우로 1 : 상하로
    const int construct[2][2] = {{2,3},{0,1}};
    void init()
    {
        scanf("%d %d\n",&m,&n);
        int index = 0;
        for(int r = 0 ; r <= n + 1; r++)
        {
            for(int c = 0 ; c<= m + 1; c++)
            {
                map[r][c] = '*';
                check[0][r][c] = false;
                check[1][r][c] = false;
            }
        }
        for(int r = 1; r <= n; r++)
        {
            for(int c = 1; c <= m; c++)
            {
                scanf("%c",&map[r][c]);
                if(map[r][c] == 'C')
                {
                    cod[index].r = r;
                    cod[index++].c = c;
                }
            }
            scanf("\n");
        }
    }

    void mark(LaserComm_Cod now)
    {
        while(map[now.r][now.c] != '*')
        {
            check[!(now.direct & 0b10)][now.r][now.c] = true;
            now.r += dr[now.direct];
            now.c += dc[now.direct];
        }
    }
    bool shoot(const LaserComm_Cod &now ,const int& direct, queue<LaserComm_Cod>& que)
    {
        LaserComm_Cod next;

        check[!(direct & 0b10)][now.r][now.c] = true;

        next.r = now.r + dr[direct];
        next.c = now.c + dc[direct];
        next.direct = direct;

        while(map[next.r][next.c] != '*')
        {
            if(map[next.r][next.c] == 'C') return true;
            check[!(direct & 0b10)][next.r][next.c] = true;
            next.r += dr[direct]; next.c += dc[direct];
        }
        
        next.r = now.r + dr[direct];
        next.c = now.c + dc[direct];
        while(map[next.r][next.c] != '*')
        {
            if(!check[(direct & 0b10)>>1][next.r][next.c]) 
            {
                next.direct = construct[(direct & 0b10)>>1][0];
                que.push(next);
                mark(next);

                next.direct = construct[(direct & 0b10)>>1][1];
                que.push(next);
                mark(next);
            }

            next.r += dr[direct];
            next.c += dc[direct];
        }
        return false;
    }
    int getMin()
    {
        typedef LaserComm_Cod Cod;
        queue<LaserComm_Cod> que;
        Cod now, next;
        int size = 4;
        int constr = 0;
        for(int d = 0; d < 4; d++)
        {
            cod[0].direct = d;
            que.push(cod[0]);
        }
        bool end = false;
        while(true)
        {
            now = que.front();
            que.pop();

            end = shoot(now,now.direct,que);

            if(end) return constr;

            size--;
            if(size == 0)
            {
                constr++;
                size = que.size();
            }
        }

        return -1;
    }
} LaserComm_info;

int LaserCommunication()
{
    LaserComm_info.init();
    int res = LaserComm_info.getMin();
    printf("%d\n", res);
    return 0;
}