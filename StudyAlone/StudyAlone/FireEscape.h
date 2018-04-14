#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

struct Info
{
    typedef struct Cod{int r, c;} cod;
    int n,m;
    cod st;
    char map[1002][1002];
    bool visit[1002][1002];
    queue<cod> fire;
    const int dr[4] = {-1,1,0,0};
    const int dc[4] = {0,0,-1,1};

    void init()
    {
        memset(map,0,sizeof(map));
        memset(visit,false,sizeof(visit));
        cin >> m >> n;

        while(fire.size()) fire.pop();

        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= m; j++)
            {
                cin >> map[i][j];
                if(map[i][j] == '@')
                {
                    map[i][j] = '.';
                    st.r = i;
                    st.c = j;
                }
                else if(map[i][j] == '*')
                {
                    cod f;
                    f.r = i; f.c = j;
                    fire.push(f);
                }
            }
        }
    }


    void spreadFire()
    {
        int size = fire.size();
        cod now, next;

        while(size--)
        {
            now = fire.front();
            fire.pop();

            for(int d = 0 ; d < 4; d++)
            {
                next.r = now.r + dr[d];
                next.c = now.c + dc[d];

                if(map[next.r][next.c] == '.')
                {
                    map[next.r][next.c] = '*';
                    fire.push(next);
                }
            }    
        }
    }

    int escape()
    {
        int t = 0;
        int size = 1;
        queue<cod> que;
        que.push(st);

        cod now, next;
        while(que.size())
        {
            now = que.front();
            que.pop();
            if(map[now.r][now.c] == 0) return t;

            if(map[now.r][now.c] != '*')
            {
                for(int d = 0; d < 4; d++)
                {
                    next.r = now.r + dr[d]; next.c = now.c + dc[d];
                    
                    if((map[next.r][next.c] == '.' || map[next.r][next.c] ==0) && !visit[next.r][next.c])
                    {
                        visit[next.r][next.c] = true;
                        que.push(next);
                    }
                }
            }

            size--;
            if(size == 0)
            {
                size = que.size();
                t++;
                spreadFire();
            }
        }
        return 0;
    }
} info;

int FireEscape()
{
    const char res[12] = "IMPOSSIBLE\n";
    int t;
    cin >> t;
    while(t--)
    {
        info.init();
        int result = info.escape();

        if(result) cout << result << '\n';
        else cout << res;
    }
    return 0;
}