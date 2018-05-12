 #include<cstdio>
#include<cstring>

using namespace std;

struct MetalPlaiting
{
    int out[10000][3];
    int map[101][101];
    int size, resNum;

    void init()
    {
        resNum = 0;        
        memset(map, 0 ,sizeof(map));
        scanf("%d\n", &size);
        int num;
        scanf("%d\n", &num);
        
        int r, c;
        while(num--)
        {
            scanf("%d %d ", &r  , &c );
            map[r][c] = 1;
        }
    }

    void setRes()
    {
        for(int k = 2; k >= 1; k--)
        {
            for(int blocks = (k + 1) * (k + 1); blocks >= k*k + 1; blocks--)
            {
                for(int i = 1; i + k <= size; i++)
                {
                    for(int j = 1; j + k <= size; j++)
                    {
                        int cnt = 0;            
                        for(int r = i; r <= i + k; r++)
                        {
                            for(int c = j; c <= j + k; c++)
                            {
                                cnt += map[r][c];                    
                            }
                        }
                        if(cnt == blocks)
                        {
                            out[resNum][0] = i; out[resNum][1] = j; out[resNum++][2] = k + 1;
                            for(int r = i; r <= i + k; r++)
                            {
                                for(int c = j; c <= j + k; c++)
                                {
                                    map[r][c] = 0;
                                }
                            }
                        }
                    }
                }
            }
        }

        for(int i = 1; i <= size; i++)
        {
            for(int j = 1; j <= size; j++)
            {
                if(map[i][j])
                {
                    out[resNum][0] = i; out[resNum][1] = j; out[resNum++][2] = 1;
                }
            }
        }
    }
    void printRes()
    {
        printf("%d ", resNum);
        for(int i = 0; i < resNum; i++)
        {
            printf("%d %d %d ", out[i][0], out[i][1], out[i][2]);
        }
    }
} info;

int MetalPlanting()
{
    int t;
    scanf("%d\n", &t);

    for(int tc = 1; tc <= t; tc++)
    {
        info.init();

        printf("#%d ", tc);
        info.setRes();
        info.printRes();
        printf("\n");
    }
    return 0;
}