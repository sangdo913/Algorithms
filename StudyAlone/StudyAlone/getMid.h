#include<iostream>
#include<queue>

using namespace std;

int getMid()
{
    int t,input;
    priority_queue<int> que;
    cin >> t;
    for(int i = 0; i < t; i++)
    {
        int input;
        cin >> input;
        que.push(input);
    }

    int res;
    for(int i = 0; i < (t >> 1); i++)
    {
        que.pop();
    }
    cout << que.top() << endl;
    return 0;
}