#include<iostream>
#include<cstdio>
#include<string.h>
#include<vector>
using namespace std;

int group[100001];
int size[100001];
bool hasGroup[100001];
int groupNum;
int groupSize;
int find(int x);


int find(int x)
{
    int p = group[x];
    if(p> 0)
    {
        p = find(p);
    }
    return p;
}

int Union(int x, int y)
{
    int px = find(x);
    int py = find(y);

    if(!hasGroup[-x] && !hasGroup[-py])
    {
        hasGroup[-px] = true;
        group[-px] = -groupNum;
        groupNum++;
        group[-py] = px;
        size[-px]++;
        groupSize++;
    }
    else if(px != py)
    {
        int temp;
        if(size[-px] < size[-py]) 
        {
            temp = px;
            px = py;
            py = temp;
        }

        if(hasGroup[-px] && hasGroup[-py] ) groupSize--;
        //px 많음
        size[-px] += size[-py];
        group[-py] = px;
        hasGroup[-px] = true;
    }
}
int KaKao()
{
    int n,p1,p2;
    scanf("%d",&n);
    groupNum=1;
    groupSize =0;   
    for(int i = 1; i<100001;i++) 
    {
        hasGroup[i] = false;
        group[i] = -i;
        size[i]  = 1;
    }
    for(int cnt=1;cnt<=n;cnt++)
    {

        scanf("%d %d\n",&p1,&p2);
        Union(p1,p2);
    }

    printf("%d\n",groupSize);
    return 0;
}