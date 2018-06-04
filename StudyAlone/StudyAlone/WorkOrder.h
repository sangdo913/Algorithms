#include<cstring>
#include<cstdio>

struct WorkInfo
{
    int inDegree[1001];
    int adj[1001][1001];
    int adjNum[1001], Q[1000];
    int n, e, fr, re, idx;
    int order[1000];
    void init()
    {
        scanf("%d %d\n", &n , &e);
        memset(adjNum, 0, sizeof(adjNum));
        memset(inDegree, 0 , sizeof(inDegree));

        int from, to;
        while(e--)
        {
            scanf("%d %d ", &from, &to);
            adj[from][adjNum[from]++] = to;
            inDegree[to]++;
        }
    }

    void setOrder()
    {
        fr = 0; re = 0, idx = 0;
        for(int i = 1; i <= n; i++)
        {
            if(inDegree[i] == 0)
            {
                Q[re++] = i;
            }
        }   

        int now;
        while(fr < re)
        {
            now = Q[fr++];
            order[idx++] = now;
            
            for(int i = 0; i < adjNum[now]; i++)
            {
                if(--inDegree[adj[now][i]] == 0)
                {
                    Q[re++] = adj[now][i];
                }
            }
        }
    }

    void print()
    {
        for(int i = 0; i < idx; i++)
        {
            printf("%d ", order[i]);
        }
    }
} info;

int WorkOrder()
{
    int t = 10;

    for(int tc = 1; tc <= t; tc++)
    {
        info.init();
        info.setOrder();
        printf("#%d ", tc); info.print(); printf("\n");
    }
    return 0;
}