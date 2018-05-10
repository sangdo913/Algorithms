#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;

struct Maze1
{
    typedef struct COD {int r, c;} COD;
    COD st, dt;
    char map[100][100];
    const int size = 100;

    const int dr[4] = {-1,1,0,0};
    const int dc[4] = {0,0,-1,1};
    
    void init()
    {
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                scanf("%c \n", & map[i][j]);
                if(map[i][j] == '2')
                {
                    st.r = i; st.c = j;
                }
                else if(map[i][j] == '3')
                {
                    dt.r = i; dt.c = j;
                }
            }
        }    
    }

    bool canEscape()
    {
        queue<COD> que;
        
        que.push(st);
        
        map[st.r][st.c] = '1';

        COD now, next;

        while(que.size())
        {
            now = que.front();
            que.pop();

            for(int d = 0; d < 4; d++)
            {
                next.r = now.r + dr[d];
                next.c = now.c + dc[d];

                if(map[next.r][next.c] == '1') continue;
                else if (next.r == dt.r && next.c == dt.c) return true;
                
                map[next.r][next.c] = '1';
                que.push(next);
            }
        }

        return false;
    }

} info;

int Maze1()
{
    int tc = 10, t;
    while(tc--)
    {
        scanf("%d\n", &t);
        info.init();
        printf("#%d %d\n", t, info.canEscape());
    }
    return 0;   
}