#include<cstring>
#include<cstdio>

void check(bool nums[10], int num)
{
    while(num)
    {
        nums[num % 10] = true;
        num /= 10;
    }
}

bool isEnd(bool nums[10])
{
    for(int i = 0; i < 10; i++) if(!nums[i]) return false;
    
    return true;
}
int NewCantSleepRemedu()
{
    int t;
    int n, now;
    
    scanf("%d\n", &t);
    for(int tc = 1; tc <= t; tc++)
    {
        scanf("%d\n", &n);

        bool nums[10] = {false};
        now = n;
        while(!isEnd(nums))
        {
            check(nums,now);
            now += n;
        }

        printf("#%d %d\n", tc, now - n);
    }

    return 0;
}