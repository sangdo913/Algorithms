#include<iostream>
#include<cstring>

using namespace std;

int nums[7] = {1,2,3,4,5,6,7};
int selected[4];
void foldPermutation(int n, int r, int length)
{
    if(r == length)
    {
        for(int i = 0; i < r; i++)
        {
            cout << selected[i] << ' ';
        }
        cout << '\n';
        return;
    }
    for(int i = 0; i < n; i++)
    {
        selected[length] = nums[i];
        foldPermutation(n,r,length + 1);
    }
}

int NandM3()
{
    int n, r;
    cin >> n >> r;
    foldPermutation(n,r,0);
    return 0;
}