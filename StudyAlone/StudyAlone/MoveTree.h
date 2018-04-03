#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;

char map[52][52];
bool visit[2][52][52] = {false};
int n;
// 통나무가 세로인 경우 0을 r에 더해주고 1을 c에 더해준다. (1~8까지)
// 통나무가 가로인 경우 1을 r에 더해주고 0을 c에 더해준다. (1~8까지)
// 통나무 가로 기준 : [행,열] [위 아래 왼쪽 오른쪽 회전]
// 통나무 세로 기준 : [열,행] [왼쪽 오른쪽 위 아래 회전]
const int check[2][5][8] = 
{
    {{-1,-1,-1,0,0,0,0,0},{1,1,1,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}, {-1,-1,-1,1,1,1,0, 0}},
    {{-1,0,1,0,0,0,0,0},{-1,0,1,0,0,0,0,0},{-2,0,0,0,0,0,0,0},{2,0,0,0,0,0,0},{ -1, 0, 1, -1, 0, 1,1,-1}}
};
// 통나무가 가로인 경우는 위에 check[][이 부분][] 인덱스를 그대로 가져가면 된다.
// 통나무가 세로인 경우는 '이 부분' 인덱스가 바뀌어야한다. (위로 갈 수 있는지 보려면 -2를 봐야한다.)
const int change[2][5] = {{0,1,2,3,4},{2,3,0,1,4}};

const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, -1, 1};
struct cod
{
    int r,c;
    bool row;
};

cod pos[2];

bool canMove(const cod& pos, const int& direct)
{
    cod nextPos;
    bool canMove = true;
    int i = 0;
    while(canMove && i < 8)
    {
        canMove = map[pos.r + check[!pos.row][change[!pos.row][direct]][i]][pos.c+check[pos.row][change[!pos.row][direct]][i]] != '1';
        i++;
    }
    return canMove;
}

inline void setPos(const cod info[2][3])
{
    pos[0].r = info[0][1].r;
    pos[0].c = info[0][1].c;
    pos[0].row = info[0][1].r == info[0][0].r;
    
    pos[1].r = info[1][1].r;
    pos[1].c = info[1][1].c;
    pos[1].row = info[1][1].r == info[1][0].r;
}

int getMin()
{
    int t = 0;
    int size = 1;
    queue<cod> que;
    que.push(pos[0]);
    cod now, next;
    while(que.size())
    {
        now = que.front();
        que.pop();
        
        if(now.r == pos[1].r && now.c == pos[1].c && pos[1].row == now.row)
        {
            return t;
        }

        for(int d = 0; d < 4; d++)
        {
            next.r = now.r + dr[d];
            next.c = now.c + dc[d];
            next.row = now.row;
            if(map[next.r][next.c] == 1) continue;
            if(visit[next.row][next.r][next.c]) continue;
            visit[next.row][next.r][next.c] = true;
            if(canMove(now,d))
            {
                que.push(next);
            }
        }

        if(!visit[!now.row][now.r][now.c] && canMove(now,4))
        {
            now.row = ! now.row;
            que.push(now);
        }

        size--;
        if(size == 0 )
        {
            size = que.size();
            t++;
        }
    }
    return 0;
}
int MoveTree()
{
    scanf("%d\n", &n);
    memset(map,'1',sizeof(map));
    int st = 0 ,dt = 0;
    cod temp[2][3];   
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            scanf("%c", &map[i][j]);
            if(map[i][j] == 'B')
            {
                temp[0][st].r = i;
                temp[0][st++].c = j;
            }
            else if (map[i][j] == 'E')
            {
                temp[1][dt].r = i;
                temp[1][dt++].c = j;
            }
        }
        scanf("\n");
    }
    setPos(temp);

    int res = getMin();
    printf("%d\n", res);
    return 0;
}