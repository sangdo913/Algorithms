#include<iostream>
#include<cstdio>
#include<stack>

using namespace std;

struct make_pair
{
    typedef enum parentheses {so = ')', mid = '}', big = ']', GGeock = '>'} Parentheses;
    
    bool isValid()
    {
        int n;
        char braket;
        stack<char> brakets;
        char pair[255];
        bool res = true;

        pair[so] = '(';
        pair[mid] = '{';
        pair[big] = '[';
        pair[GGeock] = '<';

        scanf("%d\n", &n);
        while(n--)
        {
            scanf("%c", &braket);
            switch(braket)
            {
                case ')':
                case '}':
                case '>':
                case ']':
                if(brakets.empty() || brakets.top() != pair[braket]) 
                {
                    while(n--) scanf("%c", &braket);
                    return false;
                }
                brakets.pop();
                break;
                default:
                brakets.push(braket);
                break;
            }
        }
        return true;
    }
} info;

int MakePair_GwalHo()
{
    int t = 10;
    for(int tc = 1; tc <= t; tc++)
    {
        printf("#%d %d\n", tc, info.isValid());
    }
}