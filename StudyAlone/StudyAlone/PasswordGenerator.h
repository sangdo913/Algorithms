#include<cstdio>

int PasswordGenerator()
{
    int password[8], t;


    for(int tc = 1; tc <= 10; tc++)
    {
        scanf("%d\n", &t);    
        for(int i = 0; i < 8; i++)
        {
            scanf("%d ", password + i);
        }

        bool isEnd = false;
        int cnt = 0, st;

        while(!isEnd)
        {
            for(int i = 0; i < 8; i++)
            {
                password[i] -= (cnt++ % 5) + 1;
                if(password[i] <= 0)
                {
                    isEnd = true;
                    password[i] = 0;
                    st = (i + 1) % 8;
                    break;
                }
            }
        }

        printf("#%d ", tc);
        for(int i = 0; i < 8; i++)
        {
            printf("%d ", password[(st + i) % 8]);
        }
        printf("\n");
    }
    return 0;
}