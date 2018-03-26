#include<iostream>
using namespace std;
#include<queue>
#include<algorithm>

int CarRepairShop_customer[3000];
int CarRepairShop_result[2][1001];

struct CarRepairShop_Repair
{
    static queue<int> wait;
    int time;
    int remain;
    int index;
    void init(int i,int t)
    {
        time = t;
        index = i;
        remain = 0;
    }
    void process()
    {
        remain--;
        remain = remain < 0 ? 0 : remain;
        if(remain == 0)
        {
            if(!wait.empty())
            {
                int num = wait.front();
                wait.pop();
                remain = time;
                
                CarRepairShop_result[1][num] = index;
            }
        }
    }
};
struct CarRepairShop_Reception
{
    static priority_queue<int,vector<int>, greater<int>> wait;
    int time;
    int remain;
    int index;
    int num;
    void init(int i,int t)
    {
        num = -1;
        index = i;
        time = t;
        remain = 0;
    }
    
    void process()
    {
        remain--;
        remain = remain < 0 ? 0 : remain;
        if(remain == 0)
        {
            if(num > 0)
            {
                CarRepairShop_Repair::wait.push(num);
            }

            if(!wait.empty())
            {
                num = wait.top();
                wait.pop();
                remain = time;
                
                CarRepairShop_result[0][num] = index;
            }
            else num = -1;
        }
    }
};
queue<int> CarRepairShop_Repair::wait = queue<int>();
priority_queue<int,vector<int>,greater<int> > CarRepairShop_Reception::wait = priority_queue<int,vector<int>,greater<int> >();

 
int CarRepairShop()
{
    int T;
    cin >> T;
    int n,m, k,a,b;
    int num, in;
    typedef CarRepairShop_Repair rep;
    typedef CarRepairShop_Reception rec;
    CarRepairShop_Repair repair[21];
    CarRepairShop_Reception reception[21];
    for(int tc=1 ;tc<=T;tc++)
    {
        num = 1;
        cin >> n >> m >> k >> a >> b;
        for(int i = 1; i<=n;i++)
        {
            cin >> in;
            reception[i].init(i,in);
        }

        for(int i = 1; i<=m;i++)
        {
            cin >>in;
            repair[i].init(i,in);
        }

        for(int i = k;i--;)
        {
            cin >> in;
            CarRepairShop_customer[in]++;
        }
        int time = 0;
        int cnt=1;
        while(true)
        {
            bool empty = true;
            for(int i = 1;i<=n;i++)
            {
                empty &= reception[i].remain == 0;  
            }
            for(int i = 1; i<=m;i++) empty &= repair[i].remain ==0;
            if(k==0 && empty) break;
            while(CarRepairShop_customer[time])
            {
                CarRepairShop_customer[time]--;
                rec::wait.push(cnt++);
                k--;
            }
            
            for(int i = 1; i<=n;i++) reception[i].process();
            for(int i = 1; i<=m;i++) repair[i].process();
            time++;
        }
        int res = 0;
        for(int i = 1; i<cnt;i++)
        {
            if(CarRepairShop_result[0][i] == a && CarRepairShop_result[1][i] == b) res+= i;
        }
        
        res = res == 0 ? -1 : res;
        printf("#%d %d\n", tc, res);
    }
    return 0;
}