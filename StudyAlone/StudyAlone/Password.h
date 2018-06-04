#include<deque>
#include<cstdio>
#include<iostream>

using namespace std;

struct PASSWORD
{
    deque<char> de;
    void init()
    {
        de.clear();
        de.resize(0);
    }
    void getPassword()
    {  
        int n;
        char c;
        scanf("%d ", &n);

        while(n--)
        {
            scanf("%c", &c);

            if(de.size())
            {
                if(de.back() == c) 
                {
                    de.pop_back();
                    continue;
                }
            }
            
            de.push_back(c);
        }
    }

    void print()
    {
        for(int i = 0 ; i < de.size(); i++)
        {
            printf("%c", de[i]);
        }
        printf("\n");
    }
} info;

int Password()
{
    int t;
    scanf("%d\n", &t);
    for(int tc = 1; tc <= t; tc++)
    {
        info.init();
        info.getPassword();
        printf("#%d ",tc);
        info.print();
    }
    return 0;
}