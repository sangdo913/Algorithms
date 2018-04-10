#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

struct TraumaInfo
{
    char name[10][10];
    const static int length = 'Z'-'A' + 1;

    typedef enum {LENGTH = 0, PRICE = 1, SIZE} type;

    int num[10];
    int des[length];
    
    int info[2][10];
    int n;

    void init()
    {
        scanf("%d", &n);
        for(int i = 0 ; i < n; i++)
        {
            scanf("%d\n", &info[LENGTH][i]);
            for(int j = 0; j < info[LENGTH][i]; j++) scanf("%c ",&name[i][j]);
            scanf("\n");
            scanf("%d\n", &info[PRICE][i]);
        }
    }

    int isComplete(int selected)
    {
        int temp[length];
        memcpy(temp, des, sizeof(des));
        
        int index = 0;
        int res = 0;

        while(selected)
        {
            if(selected & 1)
            {
                res += info[PRICE][index];

                for(int i = 0 ; i < info[LENGTH][index]; i++)
                {
                    temp[name[index][i]-'A']--;                    
                }
            }
            selected >>= 1;
            index++;
        }

        for(int i = 0 ; i < length; i++)
        {
            if(temp[i] > 0) return -1;
        }

        return res;
    }

    int select()
    {
        int min = 100000;
        int value;

        for(int i = 1; i < (1 << n); i++)
        {
            value = isComplete(i);
            if(value != -1)
            {
                min = min > value ? value : min;  
            }
        }
        
        return min == 100000 ? -1 : min;
    }
} info;

int TraumaOfSamSung()
{
    const char* name = "SAMSUNG";

    for(int i = 0 ; name[i]; i++)
    {
        info.des[name[i]-'A']++;
    }

    int t;
    scanf("%d",&t);

    for(int tc = 1; tc <= t; tc ++)
    {
        info.init();
        int res = info.select();
        printf("#%d %d\n", tc, res);
    }
    
    return 0;
}