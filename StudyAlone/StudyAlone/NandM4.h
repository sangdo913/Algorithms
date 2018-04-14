#include<iostream>
#include<cstring>
using namespace std;

int arr[8] = {1,2,3,4,5,6,7,8};
int selected[8];

void foldCombination(int n, int r, int length,int select)
{
    if(length == r)
    {
        for(int i = 0 ; i < r; i++)
        {
            cout << selected[i] << ' ';
        }
        cout << '\n';
        return;
    }

    for(int i = select; i < n; i++)
    {
        selected[length] = arr[i];
        foldCombination(n,r,length + 1,i);
    }
}

int NandM4()
{
    int n , m;
    cin >> n >> m;

    foldCombination(n,m,0,0);
    return 0;
}