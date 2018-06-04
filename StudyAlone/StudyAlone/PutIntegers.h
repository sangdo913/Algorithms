#include<cstdio>
#include<cstring>


using namespace std;
int PutInteger()
{
    int t;
    scanf("%d\n", &t);
    
    for(int tc = 1; tc <= t; tc++)
    {
        int n;
        bool check[100000] = {false};
        int nums[1000];
        scanf("%d\n", &n);
        for(int i = 0; i < n; i++)
        {
            scanf("%d \n", &nums[i]);
        }
        
        for(int sz = 0; sz < n && sz < 5; sz++)
        {
            for(int st = 0; st + sz < n; st++)
            {
                int num = 0;
                for(int i = 0 ; i <= sz; i++)
                {
                    num *= 10;
                    num += nums[st + i];
                    check[num] = true;
                }
            }          
        }

        int i = 0;
        while(check[i])
        {
            i++;
        }
        printf("#%d %d\n", tc, i);

    }
    return 0;
}