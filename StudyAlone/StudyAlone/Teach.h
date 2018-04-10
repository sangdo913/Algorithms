#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

struct Teach_Info
{
    const static int length = 'Z' - 'A' + 1;
    bool words[50][length];
    bool teach[length];
    int n; int k;
    int max;

    bool init()
    {
        memset(teach,false,sizeof(teach));
        teach['a'-'a'] = teach['n'-'a'] = teach['t' - 'a'] = teach['i' - 'a'] = teach['c' - 'a'] = true;
        scanf("%d %d\n", &n, &k);

        max = 0;
        if(k < 5)
        {
            printf("0\n");
            return false;
        }

        for(int i = 0; i < n; i++)
        {
            char str[16];
            scanf("%s\n", str);
            int index = 0;

            while(str[index])
            {
                words[i][str[index++]-'a'] = true;
            }
        }

        return true;
    }

    int getMax(int i1, int i2)
    {
        return i1 < i2 ? i2 : i1;
    }

    int checkWords()
    {
        int cnt = 0;
        for(int i = 0; i < n; i++)
        {
            bool canRead = true;
            for(int j = 0; j < length; j++)
            {
                canRead &= !words[i][j] || (words[i][j] && teach[j]);
            }

            cnt = canRead ? ++cnt : cnt;
        }

        return cnt;
    }

    void setTeaches(int index, int num)
    {
        if(index == length + 1) return;

        if(num == k - 5)
        {
            max = getMax(max, checkWords());
            return;
        }

        if(!teach[index])
        {
            teach[index] = true;
            setTeaches(index + 1, num + 1);
            teach[index] = false;
        }

        setTeaches(index + 1, num);
    }
} info;
#include<algorithm>
int teach()
{
    if(!info.init())
    {
        return 0;
    }
    
    info.setTeaches(0,0);
    printf("%d\n",info.max);
    return 0;
}