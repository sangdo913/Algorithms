#include<iostream>
#include<cstring>
#include<string>
using namespace std;

struct Info
{
    int n;
    char map[52][52];
    const int dr[4] = {-1,1,0,0,};
    const int dc[4] = {0,0,-1,1};

    void init()
    {
        cin >> n;
        memset(map,0,sizeof(map));
        for(int r = 1; r <= n; r++)
        {
            cin >> (char*)(map[r]+1);
        }
    }

    void swap(char &a, char &b)
    {
        char temp;
        temp = a;
        a = b;
        b = temp;
    }

    int check()
    {
        int max = -1;
        int res = 0;
        char first;
        for(int i = 1; i <= n; i++)
        {
            res = 1;
            first = map[i][1];
            
            for(int j = 2; j <= n; j++)
            {
                if(first == map[i][j]) res++;
                else
                {
                    first = map[i][j];
                    max = max < res? res : max;
                    res = 1;
                }
            }
            max = max < res? res : max;
        }


        for(int i = 1; i <= n; i++)
        {
            res = 1;
            int tempMax = 0;
            first = map[1][i];
            
            for(int j = 2; j <= n; j++)
            {
                if(first == map[j][i]) res++;
                else
                {
                    first = map[j][i];
                    max = max < res? res : max;
                    res = 1;
                }
            }
            max = max < res? res : max;
        }

        return max;
    }
    int getMax(int i1, int i2)
    {
        return i1 > i2 ? i1 : i2;
    }

    int change()
    {
        int nextR, nextC, max = check();

        for(int r = 1; r <= n; r++)
        {
            for(int c = 1; c <= n; c++)
            {
                for(int d = 0 ; d < 4; d++)
                {
                    nextR = r + dr[d];
                    nextC = c + dc[d];
                    if(map[nextR][nextC] == 0) continue;
                    if(map[nextR][nextC] == map[r][c]) continue;
                
                    swap(map[r][c], map[nextR][nextC]);
                    max = getMax(max,check());
                    swap(map[r][c],map[nextR][nextC]);
                }
            }
        }

        return max;
    }
} info;

int EatCandy()
{
    info.init();
    int res = info.change();
    cout << res << '\n';
    return 0;
}