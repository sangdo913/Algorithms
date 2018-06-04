#include<algorithm>
#include<cstdio>
#include<iostream>
#include<cstring>

using namespace std;

char str[801];
int group[800];
int newGroup[400], cnt, tree[400];
int reverseTree[400];
int LCP[400], len;
int getLength(char* str);

void makeLCP()
{
    for(int i = 0; i < len; i++)
    {
        reverseTree[tree[i]] = i;
    }

    int cnt = 0;
    LCP[0] = 0;
    for(int i = 0 ; i < len; i++)
    {
        int rev = reverseTree[i];
        if(rev == 0) 
        {
            cnt = 0;
            continue;
        }
        int revPrev = tree[rev - 1];

        while(str[i + cnt] == str[revPrev + cnt]) cnt++;
        LCP[rev] = cnt--;
        cnt = cnt < 0 ? 0 : cnt;
    }
}

void print(int pos)
{
    int cnt = 0;
    for(int i = 0; i < len; i++)
    {
        int lenth = getLength(str + tree[i]);

        cnt += lenth - LCP[i];
        if(pos <= cnt)
        {
            cnt -= lenth - LCP[i];
            pos -= cnt;
            str[tree[i] + pos + LCP[i]] = 0;
            printf("%s", str + tree[i]);
            return;
        }
    }

    printf("none");
}

struct Order
{
    bool operator()(int i1, int i2)
    {
        if(group[i1] == group[i2])
        {
            return group[i1 + cnt] < group[i2 + cnt];
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

int findKthstring()
{
    int t;
    scanf("%d\n", &t);

    for(int tc = 1; tc <= t; tc++)
    {
        memset(group, 0, sizeof(group));

        int pos;
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
                if(order(tree[i-1], tree[i]))
                {
                    newGroup[tree[i]] = newGroup[tree[i - 1]] + 1;
                }
                else
                {
                    newGroup[tree[i]] = newGroup[tree[i - 1]];
                }
            }

            for(int i = 0; i < len; i++) group[i] = newGroup[i];
            cnt <<= 1;
        } 

        makeLCP();

        printf("#%d ", tc);
        print(pos);
        printf("\n");
    }

    return 0;
}