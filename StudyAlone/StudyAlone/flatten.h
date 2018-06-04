#include<cstdio>
    
void mv(int* blocks, int &from, int &to, int num)
{
    int cnt = num;
    while(num && from - to > 1)
    {
        cnt = blocks[from] > blocks[to] ? blocks[to] : blocks[from];
        cnt = cnt > num ? num : cnt;

        blocks[from] -= cnt;
        blocks[from - 1] += cnt;
        from = blocks[from] == 0 ? --from : from;

        blocks[to] -= cnt;
        blocks[to + 1] += cnt;
        to = blocks[to] == 0 ? ++to : to;

        num -= cnt;
    }
}

int Flatten()
{

    int cnt;
    for(int tc = 1; tc <= 10; tc++)
    {
        int blocks[101] = { 0 }, in, max = 0, min = 100;
        scanf("%d\n", &cnt);
        
        for(int i = 0; i < 100; i++)
        {
            scanf("%d \n", &in);
            blocks[in]++;

            max = in > max ? in : max;
            min = in < min ? in : min;
        }

        mv(blocks, max, min, cnt);

        printf("#%d %d\n", tc, max - min);
    }
    return 0;
}