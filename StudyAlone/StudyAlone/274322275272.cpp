#include<iostream>
#include<cstdio>
#include<string.h>

using namespace std;

int map[102][102];
bool build[102][102];
int x;
const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};
const int inv[4] = {1,0,3,2};

bool construct(int r, int c, int d, int height)
{
    r += dy[d];
    c += dx[d];
    int sr = r, sc = c;
    for(int i = 0; i<x;i++)
    {
        if(build[r][c]) return false;
        if(map[r][c] != height || map[r][c] == -1)  return false;
        r += dy[d];
        c += dx[d];
    }

    r = sr; c = sc;
    for(int i = 0 ; i<x;i++)
    {
        build[r][c] = true;
        r += dy[d];
        c += dx[d];
    }
    return true;
}
bool canBuild(int r,int c,int d)
{
    memset(build,false,sizeof(build));

    int prevC = c-dx[d];
    int prevR = r-dy[d];

    while(map[r][c] != -1)
    {
        int height = map[r][c];
        prevC = c-dx[d];
        prevR = r-dy[d];
        if(map[prevR][prevC] != -1)
        {
            if(height - 1 == map[prevR][prevC])
            {
                if(!construct(r,c,inv[d],height-1)) return false;
            }
            else if( height -1 > map[prevR][prevC])
            {
                return false;
            }
        }
        int nextC = c+dx[d];
        int nextR = r+dy[d];

        if(map[nextR][nextC] != -1)
        {
            if(height - 1 == map[nextR][nextC])
            {
                if(!construct(r,c,d,height-1)) return false;
                r = r+ dy[d]*x;
                c = c + dx[d]*x;
                continue;
            }
            else if( height -1 > map[nextR][nextC])
            {
                return false;
            }
        }

        r += dy[d];
        c += dx[d];
    }

    return true;
}

int main()
{
    int t,n,input;
    memset(map,-1,sizeof(map));
    
        scanf("%d %d\n",&n,&x);
        for(int i = 1;i<=n;i++)
            for(int j = 1; j<= n; j++)
            {
                scanf("%d",&map[i][j]);
            }
        int res = 0;
        for(int i =1; i <= n; i++)
        {
            res += canBuild(1,i,1);
            res += canBuild(i,1,3);
        }
        printf("%d\n",res);
    
    return 0;
}