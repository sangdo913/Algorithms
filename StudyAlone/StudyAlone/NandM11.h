#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

int arr[7];
bool nums[10001] = {false,}; 
int selected[7];

void print(int n)
{
    for(int i = 0; i < n; i++)
    {
        cout << arr[selected[i]] << ' ' ;
    }
    cout << '\n';
}

void permutation(int n, int r, int length)
{
    if(r == length)
    {
        print(r);
        return;
    }

    for(int i = 0; i < n; i++)
    {
        selected[length] = i;
        permutation(n,r,length + 1);
    }
}

int NandM11()
{
    int n, r, index = 0;
    
    priority_queue<int, vector<int>, greater<int> > que;

    cin >> n >> r;

    for(int i =0; i < n; i++)
    {
        int num;
        cin >> num;
        if(nums[num]) continue;
        index++;
        nums[num] = true;
        que.push(num);
    }

    for(int i = 0; i < index; i ++)
    {
        arr[i] = que.top();
        que.pop();
    }


    permutation(index,r,0);
    return 0;
}