#include<iostream>
#include<cstdio>
#include<cstring>
#include<deque>

using namespace std;

struct SankeInfo
{
    int map[102][102];
    int info[2][100];
    typedef struct COD{
        int r, c;
    } cod;

    deque<cod> snake;

    typedef enum {Time = 0, Direct = 1} type;
    typedef enum {UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3} direct;
    typedef enum {L = 0, D = 1} turnIndex;

    const int dr[4] = {-1,1,0,0};
    const int dc[4] = {0,0,-1,1};

    const int turn[4][2] = {{LEFT, RIGHT},{RIGHT,LEFT},{DOWN,UP},{UP,DOWN}};
    const int apple = 1;

    direct now;

    int l, k, n;

    void init()
    {
        scanf("%d\n", &n);
        now = RIGHT;
        cod head = {1,1};

        snake.push_back(head);

        memset(map, -1, sizeof(map));

        for(int r = 1; r <= n; r++)
            for(int c = 1; c <= n; c++)
                map[r][c] = 0;

        scanf("%d\n", &k);
        int r, c;

        while(k--)
        {
            scanf("%d %d\n", &r, &c);
            map[r][c] = apple;
        }

        map[1][1] = -1;

        scanf("%d\n",&l);
        char temp;
        for(int i = 0 ; i < l; i++)
        {
            scanf("%d ", &info[Time][i]);
            scanf("%c\n", &temp);
            info[Direct][i] = temp;
        }
    }

    int getTime()
    {
        int time = 0;
        int index = 0;
        cod next;
        
        while(true)
        {
            time++;
            next.r = snake.front().r + dr[now];
            next.c = snake.front().c + dc[now];
            int pos = map[next.r][next.c];
            if(pos == -1)
            {
                return time;
            }
            else if(pos != apple)
            {
                map[snake.back().r][snake.back().c] = 0;
                snake.pop_back();
            }

            snake.push_front(next);

            map[next.r][next.c] = -1;

            if(time == info[Time][index])
            {
                if(info[Direct][index++] == 'D')
                {
                    now = (direct)turn[now][D];
                }
                else
                {
                    now = (direct)turn[now][L];
                }
            }
        }
        return time;
    }

}info;

int SnakeApple()
{
    info.init();
    int res = info.getTime();
    printf("%d\n", res);
    return 0;
}
