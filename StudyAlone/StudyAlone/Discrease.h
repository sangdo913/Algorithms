#include<stdio.h>

struct Info
{
    typedef struct edge
    {
        int parent;
        int child;
    } edge;

    int p[100001];
    edge e[100000];

    long long pathDP[100001];
    long long numOfChild[100001];

    int eNum;
    int n, k;

    void init()
    {
        scanf("%d %d\n", &n, &k);
        int parent, child;

        p[1] = 0;
        eNum = 0;

        for(int i = 0; i <= n; i++) numOfChild[i] = pathDP[i] = 0;

        for(int i = 1; i < n; i++)
        {
            scanf("%d %d\n", &parent, &child);

            p[child] = parent;
            e[eNum].parent = parent;
            e[eNum++].child = child;
        }

        for(int i = n; i > 1 ; i--)
        {
            numOfChild[p[i]] += numOfChild[i] + 1;
        }

        for(int i = 0 ; i < eNum; i++)
        {
            child = e[i].child;
            parent = e[i].parent;

            pathDP[child] += (numOfChild[child] + 1)*(n - 1 - numOfChild[child]) + pathDP[parent];
        }

        for(int i = 0 ; i < k; i++)
        {
            long long res = 0;
            scanf("%d %d\n", &parent, &child);
            printf("%lld ",(pathDP[child] - pathDP[parent])  << 1);
        }
        printf("\n");
    }
} info;

int DisCrease()
{
    int t;
    scanf("%d\n", &t);
    for(int tc = 1; tc <= t; tc ++)
    {
        printf("#%d ",tc);
        info.init();
    }
    return 0;
}