#include<iostream>
#include<unordered_map>
#include<cstdio>
#include<string>
#include<algorithm>

using namespace std;

int StringSubSet()
{
    int t, n, m;
    string in;
    
    scanf("%d\n", &t);

    for(int tc = 1; tc <= t; tc++)
    {
        unordered_map<string,int> se[2];
    
        scanf("%d %d\n", &n, &m);
        while(n--)
        {
            cin >> in;

            se[0].insert(make_pair(in,0));
        }

        while(m--)
        {
            cin >> in;
            se[1].insert(make_pair(in,0));
        }

        int res = 0;
        for(auto it = se[1].begin(); it != se[1].end(); it++)
        {
            res += se[0].find(it->first) != se[0].end();
        }

        printf("#%d %d\n", tc, res);
    }

    return 0;
}