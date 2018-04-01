#include<iostream>
#include<cstdio>
#include<stdbool.h>
using namespace std;

struct Magnetic
{
    bool magnetic[8];
    int up;
    bool getLeft()
    {
        return magnetic[(up+6)%8];
    }
    bool getRight()
    {
        return magnetic[(up+2)%8];
    }
    bool getUp()
    {
        return magnetic[up];
    }
    void roll(int n)
    {
        up += -n + 8;
        up %= 8;
    }
    void init()
    {
        up = 0;
        for(int i = 0 ; i<8;i++)
        {
            scanf("%d", &magnetic[i]);
        }
    }
};

int StrangeMagnet()
{
    int t,k;
    scanf("%d",&t);
    for(int tc = 1; tc <= t; tc++)
    {
        Magnetic m[5];
        bool spin[5];
        scanf("%d", &k);
        for(int i = 1; i < 5;i++)
        {
            m[i].init();
        }
        int rotate, number;
        int direct[5];
        bool prev;
        for(int cnt = 0 ; cnt < k ; cnt++)
        {
            scanf("%d %d\n", &number, &rotate);
            
            prev = m[number].getLeft();
            direct[number] = rotate;
            for(int i = number; i > 1; i-- )
            {
                if(m[i-1].getRight() != prev)
                {
                    prev = m[i-1].getLeft();
                    direct[i-1] = -direct[i];
                    m[i-1].roll(direct[i-1]);                    
                }
                else break;
            }
            prev = m[number].getRight();
            for(int i = number; i < 4; i++)
            {
                if( m[i+1].getLeft() != prev)
                {
                    prev = m[i+1].getRight();
                    direct[i+1] = -direct[i];
                    m[i+1].roll(direct[i+1]);
                }
                else break;
            }

            m[number].roll(rotate);
        }
        int res = 0;
        for(int i = 4;i >= 1;i--)
        {
            res <<= 1;
            res += m[i].getUp();
        }
        printf("#%d %d\n", tc, res);
    }
    return 0;
}