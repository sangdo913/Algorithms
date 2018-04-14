#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

int arr[8];
int selected[8];

void print(int l)
{
    for(int i = 0; i < l; i++)
    {
        cout << arr[selected[i]] << ' ';
    }
    cout << '\n';
}

void foldCombination(int n, int r,  int length, int index)
{
    if(length == r)
    {
        print(r);
        return; 
    }

    for(int i = index; i < n; i++)
    {
        selected[length] = i;
        foldCombination(n,r,length + 1, i);
    }
}
int NandM8()
{
    priority_queue<int,vector<int>, greater<int> > que;
    int n, r;

    cin >> n >> r;
    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
        que.push(arr[i]);
    }
    for(int i = 0; i < n; i++)
    {
        arr[i] = que.top();
        que.pop();
    }

    foldCombination(n,r,0,0);
    return 0;
}