#include<stdio.h>

int returnToMyRoom()
{
    int t, n;
    scanf("%d\n", &t);

    int room[401], cnt[401];
    for(int tc = 1; tc <= t; tc++)
    {
        scanf("%d\n", &n);
        int from, to, idx = 0;


        for(int i = 1; i < 401; i++) cnt[i] = 0;

        for(int i = 0; i < n; i++)
        {
            scanf("%d %d\n", &from, &to);

            if(from > to)
            {
                int temp = from;
                from = to;
                to = temp;
            }

            room[from] = to;
            cnt[from]++;
        }

        int t = -1, corrider = 1;
        bool isEnd = false;
        while(!isEnd)
        {
            isEnd = true;
            
            while(corrider <= 400)
            {
                if(cnt[corrider])
                {
                    cnt[corrider]--;
                    corrider = room[corrider] + (room[corrider] & 1) + 1;
                    isEnd = false;
                    continue;
                }
                else
                {
                    corrider++;
                }
            }

            t++;
            corrider = 1;
        }


        printf("#%d %d\n", tc, t);
    }
    return 0;
}