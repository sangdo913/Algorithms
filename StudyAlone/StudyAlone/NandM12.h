#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

int arr[8];
bool nums[10001] = {false,};
int selected[8];

struct Cod {int r, c;};

void print(int n)
{
    for (int i = 0; i< n; i++)
    {
        cout << arr[selected[i]] << ' ';
    }

    cout << '\n';
}

void combination(int n, int r, int length, int index)
{
    if(index == n) return;
    if(r == length)
    {
        print(r);
        return;
    }

    for(int i = index; i < n; i++)
    {
        selected[length] = i;
        combination(n,r,length+1,i);
    }
}

int NandM12()
{
    int n,r,index = 0;

    cin >> n >> r;
    priority_queue<int, vector<int>, greater<int> > que;
    for(int i = 0; i < n; i++)
    {
        int num;
        cin >> num;
        if(nums[num]) continue;
        
        nums[num] = true;
        que.push(num);
        index++;
    }

    for(int i  = 0; i < index; i++)
    {
        arr[i] = que.top();
        que.pop();
    }
    combination(index,r,0,0);
    return 0;
}

void getNExt()
{

    for(int i = 0; i < 4; i++)
    {
        const int dr[4] = {-1,1,0,0};
        const int dc[4] = {0,0,-1,1};
        typedef cod{int r,c;} c;
        c now, next;

        next.r = now.r + dr[d];
        next.c = now.c + dc[d];
    }
}