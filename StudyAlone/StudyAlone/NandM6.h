#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>

using namespace std;

int arr[8];

void print(int select)
{
    int index = 0;
    while(select)
    {
        if(select&1)
        {
            cout << arr[index] << ' ';
        }
        index++;
        select >>= 1;
    }
    cout << '\n';
}

void combination(int n, int r, int length, int select)
{
    if(n == r || r == 0)
    {
        int remain = (1<<r)-1;
        select |= remain << length;

        print(select);

        return;
    }

    select |= 1 << length;
    combination(n-1,r-1, length+1, select);
    select ^= 1 << length;

    combination(n-1,r,length + 1, select);
}

int NandM6()
{
    priority_queue<int,vector<int>, greater<int> > que;

    int n, m;
    cin >> n >> m;

    for(int i = 0 ; i  < n; i ++)
    {
        cin >> arr[i];
        que.push(arr[i]);
    }

    for(int i = 0 ; i < n ; i++)
    {
        arr[i] = que.top();
        que.pop();
    }

    combination(n,m,0,0);

    return 0;
}