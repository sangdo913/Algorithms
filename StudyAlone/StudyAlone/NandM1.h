#include<iostream>

using namespace std;

int arr[8] = {1,2,3,4,5,6,7,8};

void print(int select, int n)
{
    for(int i = 0 ; i < n; i++)
    {
        if(select & 1) cout << arr[i] << ' ';
        select >>= 1; 
    }
    cout << '\n';
}

void combination(int r, int c, int length, int select)
{
    if(r == c || c == 0)
    {
       int sel = (1 << c) -1;
       sel <<= length - r;
       select |= sel;
       print(select, length);
       return;
    }

    select |= (1 << (length - r));
    combination(r-1,c-1,length, select);
    select ^= (1 << (length - r));

    combination(r-1,c,length, select);
}
int NandM1()
{
    int n,r;
    cin >> n >> r;
    combination(n,r,n,0);
    return 0;
}