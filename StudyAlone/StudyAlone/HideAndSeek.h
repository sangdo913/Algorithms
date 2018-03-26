#include<iostream>
#include<queue>
using namespace std;
bool HideAndSeek_IsBound(int x)
{
    return x >=0 && x<=100000;
}
int HideAndSeek_visit[1000001] = {false};
int HideAndSeek()
{
    int position1;
    int position2;
    queue<int> que;
    int t = -1;
    int remain;
    cin >> position1 >> position2;
    remain = 1;
    que.push(position1);
    bool end = false;
    while(!que.empty() && !end)
    {
        remain = que.size();
    
        while(remain)
        {            
            position1 = que.front();
            que.pop();
            
            remain--;
            if(end = (position1 == position2))break;
            
            if(HideAndSeek_visit[position1]) continue;
            HideAndSeek_visit[position1] = true;

            if(HideAndSeek_IsBound(position1+1)) que.push(position1+1);
            if(HideAndSeek_IsBound(position1-1)) que.push(position1-1);
            if(HideAndSeek_IsBound(position1<<1)) que.push(position1<<1); 
        }        
        t++;
    }

    printf("%d\n",t);

    return 0;
}
