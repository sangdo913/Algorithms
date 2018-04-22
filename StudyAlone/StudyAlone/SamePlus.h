#include<iostream>
#include<stdio.h>

using namespace std;

struct SamePlusInfo
{
    typedef long long type;

    type prev[100000];
    type now[100000];

    type res;

    int n, k;

    type getSum(type a)
    {
        if(a <= 0) return 0;

        return (a*(a+1) >> 1LL);
    }

    void getNums()
    {
        scanf("%d %d\n", &n, &k);

        int pSize = 0, nSize = 0;
        int i  = 1, input;
        scanf("%d", &input);
        prev[pSize++] = input;

        for(; i < n; i++)
        {
            scanf("%d ", &input);
            if(prev[i - 1] > input)
            {
                now[nSize++] = (input);
                i++;
                break;
            }

            prev[pSize++] = (input);
        }

        res = getSum(pSize - k + 1);

        for(; i < n; i++)
        {
            scanf("%d", &input);
            if(now[nSize-1] > input)
            {
                int pFinal = prev[pSize - 1];
                int dt = 1;

                for(;dt < nSize && pFinal < now[dt]; dt++ );

                for(int l = 1 ; l <= pSize; l++)
                {
                    for(int j = 1 ; j <= dt; j++)
                    {
                        if(l + j >= k)
                        {
                            res ++;
                        }
                    }
                }

                res += getSum(nSize - k + 1);

                for(int l = 0 ; l < nSize; l++) prev[l] = now[l];
                pSize = nSize;
                nSize = 0;
            }

            now[nSize++] = input;
        }


        if(nSize > 0)
        {
            int pFinal = prev[pSize - 1];
            int dt = 1;

            for(;dt < nSize && pFinal < now[dt]; dt++ );

            for(int l = 1 ; l <= pSize; l++)
            {
                for(int j = 1 ; j <= dt; j++)
                {
                    if(l + j >= k)
                    {
                        res++;
                    }
                }
            }

             res += getSum(nSize - k + 1);
        }
    }
} info;

int SamePlus()
{
    int t;
    scanf("%d\n", &t);


    for(int tc = 1; tc <= t; tc++)
    {
        info.getNums();
        printf("#%d %lld\n", tc, info.res);
    }
    return 0;
}