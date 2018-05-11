#include<algorithm>
#include<cstdio>
#include<iostream>

using namespace std;

char str[801];
int group[400];
int newGroup[400], cnt, tree[400];

struct Order
{
    bool operator()(int i1, int i2)
    {
        if(group[i1] == group[i2])
        {
            return str[i1 + cnt] < str[i2 + cnt];
        }

        return group[i1] < group[i2];
    }
} order;

int getLength(char* str)
{
    int res = 0;
    while(*str)
    {
        str++;
        res++;
    }
    return res;
}

int findKthStr()
{
    int t;
    scanf("%d\n", &t);

    for(int tc = 1; tc <= t; tc++)
    {
        memset(group, 0, sizeof(group));

        int pos, len;
        scanf("%d\n %s\n", &pos, str);
        len = getLength(str);

        for(int i = 0; i < len; i++) 
        {
            tree[i] = i;
            group[i] = str[i];
        }

        cnt = 1;
        
        while(cnt <= len)
        {
            sort(tree, tree + len, order);
            
            newGroup[tree[0]] = 1;
            for(int i = 1; i < len; i++)
            {
                if(!order(tree[i-1], tree[i]))
                {
                    newGroup[tree[i]] = newGroup[tree[i - 1]];
                }
                else
                {
                    newGroup[tree[i]] = newGroup[tree[i - 1]] + 1;
                }
            }

            for(int i = 0; i < len; i++) group[i] = newGroup[i];
            cnt <<= 1;
        } 
        printf("#%d %s\n", tc, &str[tree[pos - 1]]);
    }

    return 0;
}