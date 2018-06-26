#include <cstdio>
#include <algorithm>
using namespace std;
pair<int, int>  p[400000];

int bSize, arr[200000];
int c;
int tc, k;

int GETBUS()
{
    int t;
    scanf("%d\n", &t);
    for(tc = 1; tc <= t; tc++)
    {
        int n;
        scanf("%d %d\n", &n, &k);

        bSize = 0;
        int in;

        for(int i = 0; i < n; i++)
        {
            scanf("%d \n", &in);
            p[i] = make_pair(in, 1);
            p[i + n] = make_pair(in + k + 1, -1);
        }   

        sort(p, p + n*2);
        
        int num = 0;
        for(int i = 0; i < 2*n; i++)
        {
            num += p[i].second;
            bSize = bSize > num ? bSize : num;       
        }

        printf("Case #%d\n%d\n", tc, bSize);
    }
    return 0;
}