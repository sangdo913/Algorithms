#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

int map[10][10]= {0};
bool blossom[10][10] = { false };

int n, minCost = 10000;
const int dr[4] = {-1,1,0,0};
const int dc[4] = {0,0,-1,1};

bool seedCheck(int r, int c)
{
    bool res = true;
    for(int d = 0; d < 4; d++)
    {
        int nextR = r + dr[d];
        int nextC = c + dc[d];

        if(blossom[nextR][nextC])
        {
            res = false;
            break;
        }
    }
    return res;
}

void uncheck(int r, int c)
{
    blossom[r][c] = false;
    for(int d = 0 ; d < 4; d++)
    {
        int nextR = r + dr[d]; int nextC = c + dc[d];
        blossom[nextR][nextC] = false;
    }
}

int seed(int r, int c)
{
    if(!seedCheck(r,c)) return -1;
    int res = map[r][c];

    blossom[r][c] = true;    
    for(int d = 0; d < 4; d++)
    {
        int nextR = r + dr[d];
        int nextC = c + dc[d];
        blossom[nextR][nextC] = true;

        res += map[nextR][nextC];
    }
    return res;
}

void getMinCost(int r, int c, int depth, int cost)
{
    int nextCost = seed(r,c);
    int nextC, nextR;

    if(c + 1 == n - 1)
    {
        nextR = r + 1;
        nextC = 1;
    }
    else
    {
        nextR = r;
        nextC = c + 1;
    }

    if(nextCost != -1)
    {
        if(depth == 2)
        {
            minCost = minCost > cost + nextCost ? cost + nextCost : minCost;
        }
        else if(minCost > cost + nextCost && nextR < n -1 && nextC < n - 1)
        {
            getMinCost(nextR,nextC,depth+1,cost+nextCost);
        }
        uncheck(r,c);
    }

    if(nextR < n -1 && nextC < n - 1) getMinCost(nextR, nextC, depth,cost);
}

int FlowerRoad()
{
    memset(map,-1,sizeof(map));
    scanf("%d\n", &n);
    for(int r = 0; r < n; r++)
    {
        for(int c = 0; c < n; c++)
        {
            scanf("%d", &map[r][c]);
        }
    }

    getMinCost(1,1,0,0);
    printf("%d\n", minCost);
    return 0;
}