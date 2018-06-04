#include<stdio.h>
#include<string.h>

struct Info{
   int ch, n, m, res;
   int friends[10][10];
   int fNum[10];
   int isPair[10];

   void swap(int &i, int &j)
   {
       int temp;
       temp = i;
       i = j;
       j = temp;
   }

   void init(int tc)
   {
        res = 0;
        ch = tc;
        scanf("%d\n", &n);
        scanf("%d\n", &m);

        memset(fNum, 0, sizeof(fNum));
        memset(isPair, -1, sizeof(isPair));

        int p1, p2;

        while(m--)
        {
            scanf("%d %d\n", &p1, &p2);

            if(p1 > p2)
            {
                swap(p1, p2);
            }

            friends[p1][fNum[p1]++] = p2;
        }
   }

   void findPair(int num)
   {
       if(isPair[num] == ch)
       {
           findPair(num + 1);
           return;
       }
       
       if(num == n)
       {
           res++;
           return;
       }

        for(int i = 0; i < fNum[num]; i++)
        {
            int pair = friends[num][i];

            if(isPair[pair] != ch)
            {
                isPair[pair] = ch;
                isPair[num] = ch;

                findPair(num + 1);

                isPair[pair] = -1;
                isPair[num] = -1;
            }
        }
   }
} info;

int Picnic()
{
    int tc; 
    
    scanf("%d\n", &tc);

    while(tc--)
    {
        info.init(tc);
        info.findPair(0);

        printf("%d\n", info.res);
    }
    return 0;
}

