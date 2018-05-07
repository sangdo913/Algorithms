#include<cstdio>

struct Palindrome
{
    char map[100][101];
    typedef struct cod {int r, c;} c;

    const int dr[2] = {0,1};
    const int dc[2] = {1,0};

    void init()
    {
        int t;
        scanf("%d\n", & t);
        for(int i = 0; i < 100; i++)
            scanf("%s\n", map[i]);
    }

    bool check(int i, int j, int len, bool row)
    {
        cod st, dt;
        st.r = i; st.c = j;
        
        if(row)
        {
            dt.r = i + len - 1; dt.c = j; 
        }
        else
        {
            dt.r = i; dt.c = j + len - 1; 
        }

        int cnt = len >> 1;
        while(cnt--)
        {
            if(map[st.r][st.c] != map[dt.r][dt.c]) return false;
            st.r += dr[row];
            st.c += dc[row];

            dt.r -= dr[row];
            dt.c -= dc[row];   
        }

        return true;
    }

    int getLongest()
    {
        int longest = 1;

        for(int i = 0; i < 100; i++)
        {
            for(int j = 0; j < 100; j++)
            {
                for(int len = longest + 1; i + len <= 100 || j + len <= 100; len++)
                {
                    if(i + len <= 100)
                    {
                        if(check(i, j, len, true))
                        {
                            longest = len;
                            continue;
                        }
                    }

                    if(j + len <= 100)
                    {
                        if(check(i, j, len, false))
                        {
                            longest = len;
                            continue;
                        }
                    }
                }
            }
        }
        return longest;
    }
} info;

int palindrome()
{
    int t;
    for(int tc = 1; tc <= 10; tc++)
    {
        scanf("%d\n", &t);
        info.init();
        printf("#%d %d\n", t, info.getLongest());
    }
    return 0;
}