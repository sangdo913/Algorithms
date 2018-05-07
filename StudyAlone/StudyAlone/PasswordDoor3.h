#include<iostream>
#include<cstdio>
#include<list>

using namespace std;

struct PasswordDoor3
{
    list<int> li;

    void init()
    {
        int n, input;

        li.clear();
        li.resize(0);
        scanf("%d ", &n);

        while(n--)
        {
            scanf("%d \n", &input);
            li.push_back(input);
        }

        return;
    }

    int insert(int x, int y)
    {
        int n, input;

        list<int> add;
        while(y--)
        {
            scanf("%d ", &input);
            add.push_back(input);
        }
        
        auto it  = li.begin();
        while(x--) it++;
        li.insert(it, add.begin(), add.end());
    }

    int del(int x, int y)
    {
        auto st = li.begin();
        while(x--) st++;
        auto ed = st;
        while(y--) ed++; 
        li.erase(st, ed);
    }
    
    int ass()
    {
        int n,input;
        scanf("%d ", &n);

        while(n--)
        {
            scanf("%d ", &input);
            li.push_back(input);
        }
    }

    void print()
    {
        auto it = li.begin();
        for(int i = 0; i < 10; i++, it++)
        {
            printf("%d ", *it);
        }
    }
    void setPassword()
    {
        int n; char comm;
        scanf("%d\n", &n);
        
        while(n--)
        {
            scanf("%c \n", &comm);
            
            int x, y;

            switch(comm)
            {
                case 'A':
                ass();
                break;

                case 'I':
                scanf("%d %d \n", &x, &y);
                insert(x, y);
                break;

                case 'D':
                scanf("%d %d \n", &x, &y);
                del(x, y);
                break;
            }
        }
    }

} info;

int PasswordDoor3()
{
    for(int t = 1; t <= 10; t++)
    {
        info.init();
        info.setPassword();
        printf("#%d ", t); info.print(); printf("\n");
    }
    return 0;
}