#include<stdio.h>

int AllPrimeNum()
{
    bool nums[1000001] = {false};
    int i, j;
    for(i = 3; i <= 33333; i += 2)
    {
        if(nums[i]) continue;
        
        j = i + i + i;

        while(j <= 1000000)
        {
            nums[j] = true;
            j += i + i;
        }
    }

    printf("2 ");
    for(int i = 3; i < 1000000; i += 2)
    {
        if(!nums[i]) printf("%d ", i);
    }
    return 0;
}