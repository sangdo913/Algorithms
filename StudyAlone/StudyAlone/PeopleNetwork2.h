#include<cstdio>
#define INF 0x7FFFFFFF
 int map[1000][1000], size;
int PeopleNetwork2()
{
    int t;
    scanf("%d\n", &t);
    for( int tc = 1; tc <= t; tc++)
    {
        scanf("%d ", &size);
        for( int i = 0; i < size; i++)
        {
            for( int j = 0; j < size; j++)
            {
                scanf("%d ", &map[i][j]);
                if(map[i][j] == 0) map[i][j] = 987654321;
            }
        }
        
        
         int sum;
        for( int k = 0; k < size; k++)
        {
            for( int i = 0; i < size; i++)
            {
                if(i == k) continue;
                for( int j = i + 1; j < size; j++)
                {
                    sum = map[i][k] + map[k][j];
                    if(sum < map[i][j])
                    {   
                        map[j][i] = map[i][j] = sum;
                    }
                }
            }
        }
        
        for( int i = 0; i < size; i++)
        {
            map[i][i] = 0;
        }
         int min = 987654321;
         int res;
        
        for( int i = 0; i < size; i++)
        {
            res = 0;
            for( int j = 0; j < size; j++)
            {
                res += map[i][j];
            }
            if(min > res) min = res;
        }

        printf("Test : %d\n", INF);
        
        printf("#%d %d\n", tc, min);
    }
    return 0;
}