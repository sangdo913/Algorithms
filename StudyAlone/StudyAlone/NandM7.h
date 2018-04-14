#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>

using namespace std;

int arr[8];
int selected[8];

int print(int n)
{
    for(int i = 0; i < n; i++)
    {
        cout << arr[selected[i]] << ' ';
    }
    cout << '\n';
}

void foldPermutation(int n, int r, int length)
{
    if(length == r)
    {
        print(r);
        return;
    }

    for(int i = 0; i < n; i++)
    {
        selected[length] = i;
        foldPermutation(n,r,length+1);
    }
}

int NandM7()
{
    priority_queue<int, vector<int>, greater<int> > que;
    int n, r;
    cin >> n >> r;
    for(int i = 0 ; i < n; i++)
    {
        cin >> arr[i];
        que.push(arr[i]);
    }

    for(int i = 0 ; i < n; i++)
    {
        arr[i] = que.top();
        que.pop();
    }

    foldPermutation(n,r,0);

    return 0;
}