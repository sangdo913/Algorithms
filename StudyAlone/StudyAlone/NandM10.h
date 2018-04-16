#include<iostream>
#include<queue>
#include<vector>

using namespace std;

int arr[8];
int nums[10001] = {0,};
int selected[8];

void print(int n)
{
    for(int i = 0 ; i < n; i++)
    {
        cout << arr[selected[i]] << ' ';
    }
    cout << '\n';
}

void combination(int n, int r, int length,int index)
{
    if(index == n) return;

    if(r == length)
    {
        print(r);
        return;
    }

    if(nums[arr[index]])
    {
        selected[length] = index;
        nums[arr[index]]--;
        combination(n,r,length + 1,index);
        nums[arr[index]]++;
    }

    combination(n,r,length, index+1);
}

int NandM10()
{
    int n, r, index =0;
    priority_queue<int, vector<int>, greater<int> > que;

    cin >> n >> r;

    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
        que.push(arr[i]);
    }

    while(que.size())
    {
        int num = que.top();
        que.pop();

        if(nums[num] == 0)
        {
            arr[index++] = num;
        }  
        nums[num]++;
    }
    combination(index,r,0,0);
    return 0;
}