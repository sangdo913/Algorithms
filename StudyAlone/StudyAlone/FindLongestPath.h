#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

struct LongestPath
{
    int n, m;
    vector<int> adj[11];

    void init()
    {
        for(int i = 1; i <= 10; i++)
        {
            adj[i].clear();
            adj[i].resize(0);
        }

        scanf("%d %d\b", &n, &m);

        int from, to;
        while(m--)
        {
            scanf("%d %d\n", &from, &to);
            adj[from].push_back(to);
            adj[to].push_back(from);   
        }
    }

    int max(int i1, int i2)
    {
        return i1 > i2 ? i1 : i2;
    }

    int findLongest()
    {
        int len = 1;
        for(int i = 1; i <= n; i++)
        {
            bool visit[11] = {false};
            visit[i] = true;
            len = max(len, length(i, visit));
        }
        return len;
    }
    
    int length(int n, bool visit[11])
    {
        int ren = 0;
        for(int i = 0; i < adj[n].size(); i++)
        {
            int next = adj[n][i];
            if(visit[next]) continue;
            
            visit[next] = true;
            ren = max(ren, length(next, visit));
            visit[next] = false;
        }

        return ++ren;
    }

} info;

int FindLongestPath()
{
    int t;
    scanf("%d\n", &t);

    for(int tc = 1; tc <= t; tc++)
    {
        info.init();
        printf("#%d %d\n", tc, info.findLongest());
    }
    return 0;
}