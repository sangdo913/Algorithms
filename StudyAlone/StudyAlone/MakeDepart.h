#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>

using namespace std;

struct MakeDepart
{
    typedef enum {EMPLOYEE = 0, DEPARTMENT = 1, SIZE, EMPTY = -1} type;
    
    int favorList[2][51][50];
    bool visit[51][50];
    int departmentNum[51];
    int selected[51];
    int n;

    void init()
    {
        scanf("%d", &n);
        memset(selected, -1, sizeof(selected));
        memset(visit, false, sizeof(visit));

        for(int k = 0; k < SIZE; k++)
            for(int i = 1; i <= n; i++)
            {
                for(int j = 0 ; j < n ; j ++)
                {
                    scanf("%d", &favorList[k][i][j]);
                }
            }
    }

    int kick(int department, int employee)
    {
        int eSelected , eWantToIn;

        for(int i = 0 ; i < n; i++)
        {
            if(selected[department] == favorList[DEPARTMENT][department][i])
            {
                eSelected = i;
            }
            else if(employee == favorList[DEPARTMENT][department][i])
            {
                eWantToIn = i;
            }
        }

        if(eSelected > eWantToIn)
        {
            eSelected = selected[department];
            selected[department] = employee;
            departmentNum[employee] = department;
            return eSelected;
        }

        return employee;
    }

    void choose(int employee)
    {
        for(int i = 0 ; i < n; i++)
        {
            if(visit[employee][i]) continue;

            visit[employee][i] = true;

            int favor = favorList[EMPLOYEE][employee][i];

            if(selected[favor] == EMPTY)
            {
                selected[favor] = employee;
                departmentNum[employee] = favor;
            }

            else
            {
                int kicked = kick(favor,employee);
                if(kicked == employee) continue;
                else
                {
                    choose(kicked);
                }
            }
            break;
        }
    }

    void print()
    {  
        for(int i = 1 ; i <= n; i++)
            printf("%d\n", departmentNum[i]);
    }
} info;

int MakeDepart()
{
    int t;
    scanf("%d",&t);
    for(int tc = 1; tc <= t; tc++)
    {
        info.init();
        for(int i = 1 ; i <= info.n; i++)
        {
            info.choose(i);
        }
        printf("#%d\n", tc);
        info.print();
    }
    return 0;
}