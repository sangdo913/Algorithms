#include<iostream>
#include<cstdio>
#include<queue>

using namespace std;

int Heap()
{
    typedef long long ll;
    int t, n, comm;
    ll num;
    scanf("%d\n", &t);

    for(int tc = 1 ; tc <= t; tc++)
    {
        scanf("%d\n", &n);
        priority_queue<ll> pq;

        printf("#%d", tc);
        while(n--)
        {
            scanf("%d\n ", &comm);
            switch(comm)
            {
                case 1:
                scanf("%lld\n", &num);
                pq.push(num);
                break;

                case 2:
                if(pq.empty()) num = -1;
                else 
                {
                    num = pq.top();
                    pq.pop();
                }

                printf(" %lld", num);
                break;
            }
        }
        printf("\n");
    }
    return 0;
}