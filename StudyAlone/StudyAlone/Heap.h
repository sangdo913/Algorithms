#include<iostream>
#include<cstdio>
#include<queue>

using namespace std;

int Heap()
{
    priority_queue<int> pq;
    int t, n, comm, num;
    scanf("%d\n", &t);

    for(int tc = 1 ; tc <= t; t++)
    {
        scanf("%d", &n);

        printf("#%d ", tc);
        while(n--)
        {
            scanf("%d\n ", &comm);
            switch(comm)
            {
                case 1:
                scanf("%d \n", &num);
                pq.push(num);
                break;

                case 2:
                if(pq.empty()) num = -1;
                else 
                {
                    num = pq.top();
                    pq.pop();
                }

                printf(" %d", num);
                break;
            }
        }
    }
    return 0;
}