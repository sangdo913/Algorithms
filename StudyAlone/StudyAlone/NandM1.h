#include<iostream>

using namespace std;
void rightR(int, int);
void leftR(int, int);

int arr[8] = {1,2,3,4,5,6,7,8};

void print(int n)
{
    for(int i = 0 ; i < n; i++)
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
        return ;
    }

    for(int i = length; i < n; i++)
    {
       rightR(length,i);
       permutation(n, r, length + 1);
       leftR(length, i); 
    }  
}

void rightR(int st, int end)
{
    int temp = arr[end];
    for(int i = end; i > st; i--)
    {
        arr[i] = arr[i-1];
    } 
    arr[st] = temp;
    return;
}
void leftR(int st, int end)
{
    int temp = arr[st];
    for(int i = st; i < end; i++)
    {
        arr[i] = arr[i+1];
    } 
    arr[end] = temp;
    return;
}

int NandM1()
{
    int n,r;
    cin >> n >> r;
    permutation(n,r,0);
    return 0;
}