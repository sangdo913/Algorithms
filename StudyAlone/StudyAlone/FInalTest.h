#include<cstdio>
#include<cstring>
#include<algorithm>
#include<functional>

using namespace std;

struct TestInfo
{
    typedef struct NODE
    {
        int r, c;
    } NODE;

    const int dr[4] = {-1,1,0,0};
    const int dc[4] = {0,0,-1,1};
    int rScore[20000];
    int B[20000];
    int C[5000];
    int rNum;

    int abs(int i1)
    {
        return i1 < 0 ? -i1 : i1;
    }

    int GCD(int r, int c)
    {
        if(r < c)
        {
            int temp = r;
            r = c;
            c = temp;
        }

        int remain;
        while(c != 0)
        {
            remain = r % c;
            r = c;
            c = remain;
        }

        return r;
    }

    NODE nodes[5000];
    int n, k, size;
    bool map[1001][1001];
    int check[2001][2001];
    int first, second;
    void init()
    {
        n = 0;
        int  num;
        memset(map, false, sizeof(map));

        scanf("%d %d %d", &size, &num, &k);
        int r, c;
        while(num--)
        {
            scanf("%d %d\n", &r, &c);
            nodes[n].r = r;
            nodes[n++].c = c;
            map[r][c] = true;
        }
    }

    int setFirst()
    {
        first = 0;
        memset(check, -1, sizeof(check));

        for(int i = 0; i < n; i++)
        {
            int cnt = n - 1;
            for(int j = 0; j < n; j++)
            {
                if(nodes[j].r == nodes[i].r || nodes[i].c == nodes[j].c) continue;

                int r = nodes[i].r - nodes[j].r;
                int c = nodes[i].c - nodes[j].c;

                int g = GCD(abs(r), abs(c));

                if(check[r/g + 1000][c/g + 1000] != i)
                {
                    check[r/g + 1000][c/g + 1000] = i;
                }
                else cnt--;
            }
            rScore[i] = cnt;
        }

        int check;

        for(int i = 0; i < n; i++)
        {
            check = -1;
            for(int d = 0; d < 4; d++)
            {
                int nextR = nodes[i].r + dr[d]; int nextC = nodes[i].c + dc[d];
                while(nextR <= size && nextR >= 1 && nextC <= size && nextC >= 1)
                {
                    if(map[nextR][nextC])
                    {
                        if(check != d)
                        {
                            check = d; 
                            nextR += dr[d];
                            nextC += dc[d];
                            continue;
                        }

                        rScore[i]--;
                    }

                    nextR += dr[d];
                    nextC += dc[d];
                }                           
            }
        }

        for(int i = 0; i < n; i++)
        {
            first += rScore[i];
        }
        return first;
    }

    int getSecond()
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                rScore[j] = ((rScore[j] * k + j + 1) % n) + 1;
                rScore[n + j] =((rScore[j] * (j + 1) + k) % n) + 1;
            }

            sort(rScore, rScore + (n << 1), less<int>());

            B[0] = 1;
            for(int j = 1; j <= (n << 1); j++)
            {
                B[j] = ((B[j - 1] * rScore[j - 1] + j) % n) + 1;
            }
            C[i] = B[n << 1];
        }

        int res = 0;
        for(int i = 0; i < n; i++) res += C[i];
        return res;
    }
} info;

int FinalTest()
{
    int t;
    scanf("%d" , &t);
    for(int tc = 1; tc <= t; tc++)
    {
        info.init();
        printf("#%d %d %d\n", tc, info.setFirst(), info.getSecond());
    }
    return 0;
}