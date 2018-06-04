#include<iostream>
#include<queue>
#include<vector>

using namespace std;

int SourtNumber()
{
    int t;
    cin >> t;

    for(int tc = 1; tc <= t; tc++)
    {
        priority_queue<int,vector<int>, greater<int> > pq;
        int n;
        cin >> n;
        while(n--)
        {
            int in;
            cin >> in; 
            pq.push(in);
        }


        cout << '#' << tc ;
        while(pq.size())
        {
            cout << ' ' << pq.top();
            pq.pop();
        }
        cout << '\n';
    }
    return 0;
}