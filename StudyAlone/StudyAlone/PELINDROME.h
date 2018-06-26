#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int getDigit(int n)
{
    int ret = 0;
    while(n)
    {
        ret++;
        n /= 10;
    }
    return ret;
}

int digitToI(int n)
{
   int ret = 1;

   while(--n)
   {
       ret *= 10;
   }
   return ret;
}

bool isPelin(int n)
{
    int digit = getDigit(n);
    if(digit == 1) return true;

    int h = digitToI(digit);    
    int cnt = digit/2;
    for(int i = 0; i< cnt; i++)
    {
        h = digitToI(digit- i);
        if((n/h)%10 != n%10) return false;
        n /= 10;
        digit--;
    }
    return true;
}

int pelindrome[100001] = {-1};
int pelin[4][100001] = {0};
int pSize[4] = {0};
int toPelin[100001][3];
int canPelin[100001];

int PELINDROME()
{
    
    int t;

    scanf("%d\n", &t);
    for(int i = 1; i < 10000; i++)
    {
        if(isPelin(i))
        {
            canPelin[i] = 1;
            pelin[1][pSize[1]++] = i;
            toPelin[i][0] = i;
        }
    }

    for(int j = 0; j < pSize[1]; j++)
    {
        for(int k = j; k <pSize[1]; k++ )
            if(canPelin[pelin[1][j] + pelin[1][k]] == 0)
            {
                canPelin[pelin[1][j] + pelin[1][k]] = 2;
                pelin[2][pSize[2]++] = pelin[1][j] + pelin[1][k]; 
                toPelin[pelin[1][j] + pelin[1][k]][1] = pelin[1][j];
                toPelin[pelin[1][j] + pelin[1][k]][0] = pelin[1][k];
            }
    }

    for(int i = 0; i < pSize[1]; i++)
    {
        for(int j = 0; j < pSize[2]; i++)
        {
            int num = pelin[1][i] + pelin[2][j];

            if(num > 10000) break;
            if(canPelin[pelin[1][i] + pelin[2][j]] == 0)
            {
                canPelin[num] = 3;
                toPelin[num][0] = pelin[1][i];
                toPelin[num][1] = toPelin[pelin[2][j]][0];
                toPelin[num][2]= toPelin[pelin[2][j]][1];
                sort(toPelin[num], toPelin[num] + 3, greater<int>());
            } 
        }
    }

    for(int tc = 1 ; tc <= t; tc++)
    {
        int n;
        scanf("%d\n", &n);
        printf("Case #%d\n%d", tc, canPelin[n]);
        
            for(int i = 0; i < canPelin[n]; i++)
            {
                printf(" %d", toPelin[n][i]);
            }
            printf("\n");
    

    }   
    return 0;
}