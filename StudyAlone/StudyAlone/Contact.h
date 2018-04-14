#include<iostream>
#include<queue>
#include<cstring>
#include<vector>

using namespace std;

struct Info
{
    vector<int> node [101];
    bool visit[101];
    int n, st;
    
    void init()
    {
        cin >> n >> st;
        n >>= 1;
        int from, to;
        memset(visit,false,sizeof(visit));
        for(int i = 0 ; i < 101; i++)
        {
            node[i].clear();
            node[i].resize(0);
        }

        visit[st] = true;
        
        while(n--)
        {
            cin >> from >> to;
            node[from].push_back(to);
        }
    }

    int getLastNum()
    {
        queue<int> que;
        int size = 1;
        que.push(st);

        int max = st;
        int now, next;
        while(true)
        {
            now = que.front();
            que.pop();

            max = max < now ? now : max;

            for(int i = 0 ; i < node[now].size(); i++)
            {
                next = node[now][i];

                if(visit[next]) continue;

                visit[next] = true;
                que.push(next);
            }

            size--;
            if(size == 0)
            {
                if(que.empty()) return max;
                size = que.size();
                max = 0;
            }
        }        
        return 0;
    }
} info;

int Contact()
{
    int t = 10;
    for(int tc = 1; tc <= t; tc++)
    {
        info.init();
        int res = info.getLastNum();
        cout << '#' << tc << ' ' << res << '\n';
    }
    return 0;
}