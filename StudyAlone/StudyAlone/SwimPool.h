#include<iostream>

using namespace std;

struct SwimPool
{
    int month[13];
    int price[4];
    const int day = 0;
    const int mon = 1;
    const int threeMonth = 2;
    const int year = 3;
    void init()
    {
        for(int i = 0 ; i<4;i++) cin >> price[i];
        for(int i = 1 ;i <13;i++) cin >> month[i];
    }

    int min(int i1, int i2)
    {
            return i1 < i2?  i1 : i2;
    }
} SwimPool_info;



int getMaxPrice(int month,int money)
{
    if(month >12) return money;
    int *price = SwimPool_info.price;
    int *mon = SwimPool_info.month;

    int nextPrice = 1000000;

    nextPrice = SwimPool_info.min(nextPrice, getMaxPrice(month+1, money +price[0]*mon[month]));
    nextPrice = SwimPool_info.min(nextPrice, getMaxPrice(month+1, money +price[1]));
    nextPrice = SwimPool_info.min(nextPrice, getMaxPrice(month+3, money +price[2]));
    nextPrice = SwimPool_info.min(nextPrice, getMaxPrice(month+12, money +price[3]));

    return nextPrice;
}

int Swimpool()
{

    int T,res;
    cin >> T;
    for(int tc = 1 ; tc<=T; tc++)
    {
        SwimPool_info.init();

        res = getMaxPrice(1,0);
        cout << '#'<< tc << ' ' << res << '\n';
    }
    return 0;
}