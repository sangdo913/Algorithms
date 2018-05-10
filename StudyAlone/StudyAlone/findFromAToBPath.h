#include<iostream>
#include<queue>
#include<cstdio>

using namespace std;

struct FindPathInfo
{
    int adj[100][3];
    
    void init()
    {
        int m, from, to;
        scanf("%d\n", &m);

        for(int i = 0; i < 100; i++) adj[i][2] = 0;

        while(m--)
        {
            scanf("%d %d \n", &from, &to);
            adj[from][adj[from][2]++] = to;
        }
    }

    bool findPath()
    {
        queue<int> que;

        for(int i = 0; i < adj[0][2]; i++)
        {
            que.push(adj[0][i]);
        }

        while(que.size())
        {
            int now = que.front();
            que.pop();

            for(int i = 0; i < adj[now][2]; i++)
            {
                if(adj[now][i] == 99) return true;
                que.push(adj[now][i]);
            }
        }
        return false;
    }
} info;

int findFromAToBPath()
{
    int t = 10, tc;
    while(t--)
    {
        scanf("%d \n", &tc);
        info.init();
        printf("#%d %d\n", tc, info.findPath());
    }
    return 0;
}