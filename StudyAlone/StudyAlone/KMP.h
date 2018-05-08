#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

struct KMP_Info
{
    string p, s;
    int kmp[1001];

    void init()
    {
        cin >> p;
        cin >> s;
    }

    int find()
    {
        int num = 0;
        int pSize = p.size(), sSize = s.size();
        int index = 0;

        for(int i = 0; i < sSize; i++)
        {
            while(index != -1 && p[index] != s[i]) index = kmp[index];
            index++;

            if(index == pSize)
            {
                index = kmp[index];
                num++;
            }
        }

        return num;
    }
    
    void makeKMP()
    {
        int pSize = p.size();
        
        int index = -1;
        for(int i = 0; i <= pSize; i++)
        {
            kmp[i] = index;

            while(index != -1 && p[i] != p[index]) index = kmp[index];
            
            index++;
        }
    }
} info;

int KMP()
{
    int t, tc = 10;
    
    while(tc--)
    {
        scanf("%d\n", & t);
        info.init();
        info.makeKMP();
        printf("#%d %d\n", t, info.find());
    }
    return 0;
}