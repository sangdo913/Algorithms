#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>

using namespace std;

struct FINDMATRIXINFO
{
    typedef struct MAT
    {
        int r, c;
    } MAT;

    typedef struct MATVALUE
    {
        bool operator()(MAT a, MAT b)
        {
            return a.r * a.c > b.r * b.c; 
        }
    } MATVALUE;

    MAT matrixes[10000];
    MATVALUE bigger;

    char map[101][101];
    bool check[101][101];
    int size;
    int matNumber;
    int matInfo[10000];

    void init()
    {
        memset(map, '0', sizeof(map));
        memset(check, false, sizeof(check));

        scanf("%d\n", & size);
        matNumber = 0;
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                scanf("%c \n", &map[i][j]);
            }
        }
    }

    int getValue()
    {
        int row, col, store;
        for(int i = 0 ; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                if(map[i][j] != '0' && check[i][j] == false)
                {
                    store = i;
                    row = i; col = j;
                    while(map[row][j] != '0') j++;
                    while(map[i][col] != '0') i++;
                    matrixes[matNumber].r = (i - row);
                    matrixes[matNumber++].c = (j - col);
                    for(int r = row; r < i; r++)
                    {
                        for(int c = col; c < j; c++)
                        {
                            check[r][c] = true;
                        }
                    }
                    i = row;
                }
            }
        }
        return matNumber;
    }

    void print()
    {
        sort(matrixes, matrixes + matNumber, bigger);
        for(int i = 0; i < matNumber; i++)
            printf("%d %d ", matrixes[i].r, matrixes[i].c);
    }
}info ;


int FindMatrix()
{
    int t;
    scanf("%d\n", &t);
    for(int tc = 1; tc <= t; tc++)
    {
        info.init();
        printf("#%d ", tc);
        info.getValue();
        info.print();
        printf("\n");
    }
    return 0;
}