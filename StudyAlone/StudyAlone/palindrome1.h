#include<cstdio>

struct Plain
{
    char str[8][9];
    char comp[8];
    int n;
    
    void init()
    {
        scanf("%d\n", &n);
        for(int i = 0; i < 8; i++)
        {
            scanf("%s\n", str[i]);
        }
    }

    int getPalindrome()
    {
        int res = 0;
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if(j + n <= 8)
                {
                    for(int cnt = 0 ; cnt < n; cnt++)
                    {
                        comp[cnt] = str[i][j + cnt];
                    }
                    res += getNum();
                }

                if(i + n <= 8)
                {
                    for(int cnt = 0; cnt < n; cnt++)
                    {
                        comp[cnt] = str[i + cnt][j];
                    }
                    res += getNum();
                }
            }
        }
        return res;
    }
    int getNum()
    {
        int st = 0, dt = n - 1, cnt = n >> 1;
        while(cnt--)
        {
            if(comp[st] != comp[dt]) return 0;
            st++; dt--;
        }
        return 1;
    }
} info;

int plaindrome1()
{
    int t;

    for(int tc = 1; tc <= 10; tc++)
    {
        info.init();
        printf("#%d %d\n", tc, info.getPalindrome());
    }
    return 0;
}