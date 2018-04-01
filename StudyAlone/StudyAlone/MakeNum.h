#include<iostream>
#include<cstdio>
using namespace std;

struct MakeNum_Info
{
    enum OP {PLUS=0,MINUS,MUL,DIV};
    int op[4];
    int nums[12];
    int max , min;
    int n;
    int cal[11];
    void init()
    {
        max = -100000000;
        min = 100000000;
        scanf("%d",&n);
        for(int i = 0 ; i < 4 ; i++)
        {
            scanf("%d", &op[i]);
        }
        for(int i = 0; i < n; i++)
        {
            scanf("%d", &nums[i]);
        }
    }
    int result()
    {
        return max - min;
    }
    int calcul()
    {
        int res = nums[0];
        for(int i = 0 ; i<n-1;i++)
        {
            switch(cal[i])
            {
                case 0:
                res+= nums[i+1];
                break;
                case 1:
                res -= nums[i+1];
                break;
                case 2:
                res *= nums[i+1];
                break;
                case 3:
                res /= nums[i+1];
            }
        }
        return res;
    }

    void setEquals(int cnt)
    {
        if(cnt == n - 1)
        {
            int num = calcul();
            max = max < num ? num : max;
            min = min > num ? num : min;
            return;
        }
        for(int i = 0 ; i < 4;i++)
        {
            if(op[i] > 0) 
            {
                cal[cnt] = i;
                op[i]--;
                setEquals(cnt+1);
                op[i]++;
            }
        }
    }  
}MakeNum_info;

int MakeNum()
{
    int t;
    scanf("%d",&t);
    for(int tc = 1; tc <= t; tc++)
    {
        MakeNum_info.init();
        MakeNum_info.setEquals(0);
        printf("#%d %d\n", tc, MakeNum_info.result());
    }
    return 0;
}