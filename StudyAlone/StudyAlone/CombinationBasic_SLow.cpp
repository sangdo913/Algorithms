#include<iostream>
#include<cstring>

int arr[5] = {9,3,1,5,8};

using namespace std;

int getBitNum(int n)
{
    int bitCnt = 0;
    while(n)
    {
        bitCnt += n & 1;
        n >>= 1;
    }
    return bitCnt;
}

int res = 0;

void func(int visit, int n)
{
    for(int i = 0; i < n; i++)
    {
        if(visit & 1) 
        {
            cout << arr[i] << ' ';
        }

        visit >>= 1;
    }
    cout << '\n';
}

int main()
{
    // n : 데이터 개수, k : 선택할 개수
    int n = 5;
    int k = 3;

    for(int i = 0 ; i < (1 << n); i++)
    {
        if(getBitNum(i) == k) 
        {
            res++;
            func(i,n);
        }
    }

    cout << "res : " << res<< '\n';
    return 0;
}