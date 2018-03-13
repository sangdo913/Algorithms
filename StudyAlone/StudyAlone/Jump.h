#pragma once
#include<iostream>
#include<algorithm>
#include<deque>
#include<cstdio>

using namespace std;

int ChangeJump_height[10000];

int ChangeJump()
{
    int T,N;
    cin >> T;
    int (*max)(int i1, int i2) = [](int i1, int i2)->int{return i1 > i2 ? i1 : i2;};
    int (*abs)(int i1) = [](int i1)->int{return i1 > 0 ? i1 : -i1;};
    
    for(int tc = 1 ; tc<=T;tc++)
    {
        cin >> N;
        for(int i = 0 ; i<N;i++)
        {
            cin >> ChangeJump_height[i];
        }
        sort(ChangeJump_height, ChangeJump_height + N);
        
        
        deque<int> dq;
        bool front = true;
        int index = 0;
        dq.push_back(ChangeJump_height[index++]);

        int diff = 0;

        while(index<N)
        {
            if(front)
            {
                diff = max(ChangeJump_height[index]-dq[0], diff);
                dq.push_front(ChangeJump_height[index++]);
            }
            else
            {
                diff = max(diff,ChangeJump_height[index]-dq[dq.size()-1]) ;
                dq.push_back(ChangeJump_height[index++]);
            }
            front = !front;
        }
        diff = max(diff,abs(dq.front() - dq.back()));

        printf("#%d %d\n", tc, diff);
    }
    return 0;
}