#include<iostream>
#include<cstring>

using namespace std;

struct Info
{
    int nums[20];
    int n,k, res;

    void init()
    {
        cin >> n >> k;
        res = 0;
        for(int i = 0 ; i < n; i++)
        {
            cin >> nums[i];
        }
    }

    int getSum(int visit)
    {
        int sum = 0;
        int index = 0;
        while(visit)
        {
            if(visit & 1)
            {
                sum += nums[index];
                if(sum > k) return sum;
            }   
            index++;
            visit >>= 1;
        }
        return sum;
    }
    int getMax()
    {
        int sum;
        for(int i = 1; i < (1 << n); i++)
        {
            res += k == getSum(i);
        }
        return res;
    }
} info;
int ParSum()
{
    int t;
    cin >> t;
    for(int tc = 1; tc <= t; tc++)
    {
        info.init();
        cout << '#' << tc << ' ' << info.getMax() << '\n';
    }
    return 0;
}