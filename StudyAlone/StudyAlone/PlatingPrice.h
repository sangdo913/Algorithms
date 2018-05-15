#include<cstdio>
#include<cstring>

struct PlatingInfo
{
    typedef struct MAX{ int r, c, blorNum;} MAX;
    MAX max;
    int size, maxRange;
    bool map[102][102];
    int blored[101][101];
    int prices[101];
    int Q[10000][3], fr, re, num;
    const int mask[5][5] = {{1,4,7,4,1},{4,16,26,16,4},{7,26,50,26,7},{4,16,26,16,4},{1,4,7,4,1}}, std = 60;

    void blor()
    {
        memset(blored, 0 , sizeof(blored));

        for(int i = 1; i <= size; i++)
        {
            for(int j = 1; j <= size; j++)
            {
                bool can = map[i-1][j] + map[i+1][j] + map[i][j+1] + map[i][j-1] >= 3; 
                if(map[i][j] || can)
                {
                    for(int r = -2; r <= 2; r++)
                    {
                        for(int c = -2; c <= 2; c++)
                        {
                            if(i + r >= 1 && i + r <= size && j + c <= size && j + c >= 1)
                            {
                                blored[i+r][j+c]+= mask[r + 2][ c + 2];
                            }
                        }
                    }
                }
            }
        }
    }

    void init()
    {
        int n;
        memset(map,0,sizeof(map));
        scanf("%d\n", &size);
        scanf("%d\n", &n);
        num = n;
        maxRange = size;

        while(n--)
        {
            int r, c;
            scanf("%d %d \n", &r, &c);
            map[r][c] = true;
        }
    }

    void setPrice()
    {
        for(int i = 1; i <= 100; i++)
        {
            prices[i] = (float)(i*i) / 2.f + (float)(i*2) / 3.f + 1;
        }
    }

    bool setMax(int range)
    {
        MAX temp;
        temp.blorNum  = -1;
        for(int i = 1; i + range - 1<= size; i++)
        {
            for(int j = 1; j + range - 1 <= size; j++)
            {
                int num = checkEdge(i,j,range);
                if(num == -1) continue;

                if(temp.blorNum < num)
                {
                    temp.r = i;
                    temp.c = j;
                    temp.blorNum = num;
                }
            }
        }

        if(temp.blorNum != -1)
        {
            max.r = temp.r;
            max.c = temp.c;
            max.blorNum = temp.blorNum;
            return true;
        }

        return false;
    }
    
    void plant(int r, int c, int range)
    {
        for(int i = 0; i < range; i++)
        {
            for(int j = 0; j < range; j++)
            {
                map[i + r][j + c] = false;
            }
        }
    }

    void setRes()
    {
        fr = re = 0;

        int l, r, m;
        
        while(maxRange > 4)
        {
            max.blorNum = -1;
            blor();
            l = 4; r = maxRange;
            while(l <= r)
            {
                m = (l + r) / 2;
                if(setMax(m))
                {
                    l = m + 1;
                }
                else
                {
                    r = m - 1;
                }
            }

            if(max.blorNum == -1) break;

            Q[re][0] = max.r;
            Q[re][1] = max.c;
            Q[re++][2] = r;

            plant(max.r,max.c, r);
            maxRange = r;
        }

        for(l = 2; l >= 1; l--)
        {
            for(int s = (l+1)*(l+1); s >=  l*l + 1; s--)
            {
                for(int i = 1; i + l <= size; i++)
                {
                    for(int j = 1; j + l <= size; j++)
                    {
                        int cnt = 0;
                        for(int r = 0; r < l + 1; r++)
                        {
                            for(int c = 0; c < l + 1 ; c++)
                            {
                                cnt += map[i + r][j + c];
                            }
                        }
                        if(cnt == s)
                        {
                            Q[re][0] = i;
                            Q[re][1] = j;
                            Q[re++][2] = l + 1;
                            
                            for(int r = 0; r < l + 1; r++)
                            {
                                for(int c = 0; c < l + 1 ; c++)
                                {
                                    map[i + r][j + c] = false;
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
                    Q[re][0] = i;
                    Q[re][1] = j;
                    Q[re++][2] = 1;
                }
            }
        }
    }
    void printMap()
    {
        for(int i = 1; i <= size; i++)
        {
            for(int j = 1; j <= size; j++)
            {
                printf("%d ", map[i][j]);
            }
            printf("\n");
        }
    }

    int edgeSum(int r, int c, int range)
    {
        int res = 0, cnt = 0, bCnt = 0;
        for(int i = 0; i < range; i++)
        {
            for(int j = 0; j < range; j++)
            {
               res += blored[r + i][c + j]; 
               cnt+= map[r + i][ c + j];
               bCnt += blored[r + i][c + j] >= std;
            }
        }
        if(cnt < prices[range]) return -1;
        if(bCnt < (float)(range*range)*0.99f) return -1; 
        return res;
    }

    int checkEdge(int r, int c, int range)
    {
        int cnt = blored[r][c] >= std;

        for(int i = 1; i < range; i++)
        {
            cnt += blored[r + i][c] >= std;
            cnt += blored[r][c+i] >= std;
        }

        if(cnt < (float)(range * 2 - 1 )*0.965f) return -1;
        
        return edgeSum(r, c,range);
    }

    void print()
    {
        printf("%d ", re);
        while(fr < re)
        {
            printf("%d %d %d ", Q[fr][0], Q[fr][1], Q[fr][2]);
            fr++;
        }
    }
} info;

int PlatingPrice()
{
    int t; 
    scanf("%d\n", &t);
    info.setPrice();
    for(int tc = 1; tc <= t; tc++)
    {
        info.init();
        info.setRes();
        printf("#%d ", tc); info.print(); printf("\n");
    }
    return 0;
}