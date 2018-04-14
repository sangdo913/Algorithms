#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

void rotateR(int,int);
void rotateL(int,int);

int arr[8];

void print(int n)
{
    for(int i = 0; i < n; i++)
    {
        cout << arr[i] << ' ';
    }
    cout << '\n';
}

void permutation(int n, int r, int length)
{
    if(length == r)
    {
        print(r);
    }

    for(int i = length; i < n; i++)
    {
        rotateR(length,i);
        permutation(n,r, length+1);
        rotateL(length,i);
    }
}

void rotateR(int st, int dt)
{
    int temp = arr[dt];
    for(int i = dt; i > st; i--)
    {
        arr[i] = arr[i-1];
    }
    arr[st] = temp;
}

void rotateL(int st, int dt)
{
    int temp = arr[st];
    for(int i = st; i < dt; i++)
    {
        arr[i] = arr[i+1];
    }
    arr[dt] = temp;
}

int NandM5()
{
    
    priority_queue<int, vector<int>, greater<int> > que;
    int n,r;
    cin >> n >> r;

    int in;
    
    for(int i = 0; i < n; i++)
    {
        cin >> in;
        que.push(in);
    }
    in = 0;

    while(que.size())
    {
        arr[in++] = que.top();
        que.pop();
    }

    permutation(n,r,0);

    return 0;
}