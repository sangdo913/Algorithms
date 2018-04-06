#include<iostream>
#include<cstdio>
#include<string.h>
using namespace std;

struct Easy2048_Info
{
    int map[22][22];
    bool isPlus[22][22];
    int n;
    const int dx[4] = {0,0,-1,1};
    const int dy[4] = {-1,1,0,0};

    void init()
    {
        scanf("%d",&n);
        memset(map,-1,sizeof(map));
        memset(isPlus,false,sizeof(isPlus));
        for(int i = 1;i <= n;i++)
        {
            for(int j = 1; j <= n; j++)
            {
                scanf("%d", &map[i][j]);
            }
            scanf("\n");
        }
    }

    void go(int r, int c, int d)
    {
        if(map[r][c] == 0) return;

        while(true)
        {
            int nextR = r+dy[d];
            int nextC = c+dx[d];
            
            if(map[nextR][nextC]== -1) break;
            else if(map[nextR][nextC] == 0)
            {
                map[nextR][nextC] = map[r][c];
                map[r][c] = 0;
                r = nextR;
                c = nextC;
            }
            else if(map[nextR][nextC] == map[r][c])
            {
                if(isPlus[nextR][nextC]) break;
                else
                {
                    isPlus[nextR][nextC] = true;
                    map[nextR][nextC] += map[r][c];
                    map[r][c] = 0;
                    break;
                }
            }
            else break;
        }
    }

    void Move(int d)
    {
        int start,flag;
        memset(isPlus,false,sizeof(isPlus));

        //하 or 우 오른쪽 아래에서부터 시작
        if(d&1)
        {
            start = n;
            flag = -1;
        }
        
        //상 or 좌 왼쪽 위에서 시작
        else
        {
            start = 1;
            flag = 1;
        }

        int r = start,c = start;
        
        for(r = start; map[r][start] != -1 ;r+= flag)
            for(c= start; map[r][c]!= -1; c+=flag)
                go(r,c,d);
    }
    
    int getMax()
    {
        int max = 0;
        for(int i =1;i<=n;i++)
        {
            for(int j =1 ; j<=n;j++)
                max = max < map[i][j] ? map[i][j] : max;
        }
        return max;
    }

    int max(int i1, int i2)
    {
        return i1 > i2 ? i1 : i2;
    }
} Easy2048_info;

int Easy2048()
{
    int temp[22][22];
    int res = 0;
    Easy2048_info.init();

    memcpy(temp,Easy2048_info.map,sizeof(Easy2048_info.map));
    for(int i = 0; i<4;i++)
        for(int j = 0 ; j<4;j++)
            for(int k = 0 ; k<4; k++)
                for(int l = 0 ; l<4;l++)
                    for(int m = 0; m<4;m++)
                    {
                        Easy2048_info.Move(i);
                        Easy2048_info.Move(j);
                        Easy2048_info.Move(k);
                        Easy2048_info.Move(l);
                        Easy2048_info.Move(m);
                        res = Easy2048_info.max(Easy2048_info.getMax(),res);
                        memcpy(Easy2048_info.map,temp,sizeof(Easy2048_info.map));
                    }

    printf("%d\n",res);
    return 0;
}