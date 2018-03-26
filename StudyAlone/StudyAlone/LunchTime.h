#include<iostream>
#include<stack>
#include<cstring>

using namespace std;

struct LunchTime_People
{
    int x; int y;
    int time;
};

struct LunchTime_Stair
{
    typedef LunchTime_People people;
    people down[3];
    int time;
    int x, y;
    int wait;
    int size;
    void init()
    {
        for(int i = 0 ; i<3;i++)down[i].time = -1;
    }
    void insertPeople()
    {
        if(size == 3) return;

        while(size < 3)
        {   
            if(wait == 0) break;
            wait--;
            for(int i = 0 ; i<3;i++)
            {
                if(down[i].time <=0)
                {
                    down[i].time = time;
                    size++;
                    break;
                }
            }
        }
    }
    void arrivePeople(int num)
    {
        wait+=num;
    }
    void goDown()
    {
        for(int i = 0 ; i<3;i++)
        {
            down[i].time--;
            if(down[i].time ==0)
            {
                size--;
            } 
        }
    }
};

int Lunch_ArriveTime[2][1000];
LunchTime_People Lunch_people[10];
inline int Lunch_Min(int i1, int i2)
{
    return i1 < i2 ? i1 : i2;
}
int Lunch_abs(int x)
{
    return x > 0 ? x : -x;
}

void Lunch_SetTime(int info,int n, LunchTime_Stair &s1, LunchTime_Stair &s2)
{
    int next = info;

    memset(Lunch_ArriveTime,0,sizeof(Lunch_ArriveTime));

    int t;
    for(int i = 0; i<n; i++)
    {
        if(next & 1)
        {
            t = abs(Lunch_people[i].x - s1.x) + abs(Lunch_people[i].y - s1.y);
            Lunch_ArriveTime[0][t]++;
        }
        else
        {
            t = abs(Lunch_people[i].x - s2.x) + abs(Lunch_people[i].y - s2.y);
            Lunch_ArriveTime[1][t]++;
        }
        next>>=1;
    }
}

int Lunch_Process(int n, LunchTime_Stair &s1, LunchTime_Stair &s2)
{
    int time = 0;
    
    s1.wait = 0; s2.wait = 0;
    s1.size = s2.size= 0;
    s1.init();
    s2.init();

    while(n!= 0 || (s1.size + s1.wait != 0) || s2.size + s2.wait !=0)
    {
        s1.goDown();
        s1.insertPeople();
        s1.wait+= Lunch_ArriveTime[0][time];

        s2.goDown();
        s2.insertPeople();
        s2.wait+= Lunch_ArriveTime[1][time];
        
        n-= Lunch_ArriveTime[0][time] + Lunch_ArriveTime[1][time];
        time++;
    }
    return time-1;
}


int LunchTime()
{
    typedef LunchTime_Stair stair;
    stair s1, s2;
    
    int T,n,info,cnt,sCnt;
    cin >>T;
    for(int tc= 1; tc<=T;tc++)
    {
        int resTime = 1000000;
        sCnt = cnt =0;
        cin >> n;
        for(int i = 0 ; i<n;i++)
        {
            for(int j = 0 ; j<n;j++)
            {
                cin >> info;
                if(info == 1)
                {
                    Lunch_people[cnt].x = j;
                    Lunch_people[cnt].y = i;
                    cnt++; 
                }
                else if(info > 1)
                {
                    if(sCnt ==0 )
                    {
                        s1.x = j;
                        s1.y = i;
                        s1.time = info;
                        sCnt++;
                    } 
                    else
                    {
                        s2.x = j;
                        s2.y = i;
                        s2.time = info;
                    }
                }
            }
        }


        for(int i = 0; i<(1<<cnt); i++)
        {
            Lunch_SetTime(i,cnt,s1,s2);
            resTime = Lunch_Min(resTime, Lunch_Process(cnt,s1,s2));
        }

        printf("#%d %d\n",tc, resTime);
    }


    return 0;
}