#include<cstdio>

int boats[5000];
int bNum;

int InComming()
{
    int t, n;
    bool find = false;

    scanf("%d\n", &t);
    for(int tc = 1; tc <= t; tc++)
    {
        bNum = 0;
        scanf("%d\n", &n);

        int in, res = 0;
        scanf("%d\n", &in);

        while(--n)
        {
            find = false;
            scanf("%d\n", &in);
            in--;
            for(int i = 0; i < bNum; i++)
            {
                if(in % boats[i] == 0) 
                {
                    find = true;
                    break;
                }
            }

            if(!find)
            {
                boats[bNum++] = in;
            }
        }
        printf("#%d %d\n", tc, bNum);
    }
    return 0;
}