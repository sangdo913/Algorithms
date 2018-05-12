#include<cstdio>
#include<deque>
#include<cstring>
#include<iostream>

using namespace std;

struct ChemicalInfo
{
    int map[102][102];
    int indexes[101][2];
    int boxes[10000][2];
    int size, bNum, dNum;
    bool checkBox[10000];
    int d[10000], matMulDP[102][102];
    bool check[100][100];
    void init()
    {
        memset(map,0,sizeof(map));

        scanf("%d",& size);
        dNum = bNum = 0;

        for(int i = 1; i <= size; i++)
        {
            for(int j = 1; j <= size; j++)
            {
                scanf("%d \n", &map[i][j]);
            }
        }
    }

    void setBoxes()
    {
        memset(check,false, sizeof(check));
        memset(indexes, -1, sizeof(indexes));
        for(int i = 1; i <= size; i++)
        {
            for(int j = 1; j <= size; j++)
            {
                if(map[i][j] && !check[i][j])
                {
                    int row = i, col = j;
                    while(map[i][col]) col++;
                    while(map[row][j]) row++;

                    boxes[bNum][1] = col - j;
                    boxes[bNum][0] = row - i;
                    indexes[col - j][1] = bNum;
                    indexes[row - i][0] = bNum++;

                    for(int r = i; r <row; r++)
                    {
                        for(int c = j; c < col; c++)
                        {
                            check[r][c] = true;
                        }
                    }
                    j = col;
                }
            }
        }
    }

    int getMin(int i1, int i2)
    {
        return i1 < i2 ? i1 : i2;
    }
    int getRes()
    {
        deque<int> order;

        for(int i = 1; i <= 100; i++)
        {
            if(indexes[i][0] != -1)
            {
                order.push_back(indexes[i][0]);
                break;
            }
        }

        while(indexes[boxes[order[0]][0]][1] != -1)
        {
            order.push_front(indexes[boxes[order[0]][0]][1]);
        }
        while(indexes[boxes[order[order.size() -1]][1]][0] != -1)
        {
            order.push_back(indexes[boxes[order[order.size() -1]][1]][0]);
        }

        d[0] = boxes[order[0]][0];
        for(int i = 0; i < order.size(); i++ )
        {
            d[i + 1] = boxes[order[i]][1];
        }
        dNum = order.size() + 1;

        for(int cnt = 0; cnt < bNum; cnt++)
        {
            for(int i = 1; i <= bNum - cnt; i++)
            {
                int j = i + cnt;
                if(i == j)
                {
                    matMulDP[i][j] = 0; 
                    continue;
                }

                matMulDP[i][j] = 987654;
                for(int k = i; k < j; k++)
                {
                    matMulDP[i][j] = getMin(matMulDP[i][k] + matMulDP[k + 1][j] + d[i - 1] * d[k] * d[j], matMulDP[i][j]);
                }
            }
        }

        return matMulDP[1][bNum];
    }
} info;


int ChemicalThings2()
{
    int t;
    scanf("%d\n", &t);
    for(int tc = 1; tc <= t; tc++)
    {
        info.init();
        info.setBoxes();
        printf("#%d %d\n", tc, info.getRes());
    }
    return 0;
}