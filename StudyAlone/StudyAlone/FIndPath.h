#include<iostream>

using namespace std;
int FindPath_map[101][101];

void FindPath_find(int node, bool visit[101],bool finish[101],const int n)
{

    for(int i = 1;i<=n;i++)
    {

        if(FindPath_map[node][i] == 0) continue;

        for(int j = 1;j<=n;j++)
        {
            if(visit[j]&& j)
            {
                for(int k = 1; k<=n;k++)
                {
                    if(FindPath_map[i][k])
                        FindPath_map[j][k] = 1;
                }
                if(j != i) FindPath_map[j][i] = 1;
            }
        }

        if(visit[i] || finish[i]) continue;
        

        visit[i] = true;
        FindPath_find(i,visit,finish,n);
        visit[i] = false;
    }

    finish[node] = true;
}

void FindPath2(int n)
{
    for(int k = 1; k<=n; k++)
        for(int i = 1; i<=n;i++)
        {
            for(int j = 1; j<=n; j++ )
            {
                if(FindPath_map[i][j] > FindPath_map[i][k]+FindPath_map[k][j])
                {
                    FindPath_map[i][j] = FindPath_map[i][k]+FindPath_map[k][j];
                }
            }
        }
}

int FindPath()
{
    int n;
    cin >> n;
    for(int i = 1; i<=n;i++)
    {
        for(int j =1;  j<=n; j++)
        {
            cin >> FindPath_map[i][j];
            
            FindPath_map[i][j] = FindPath_map[i][j] == 0 ? 100000 : 1;
        }
    }

    // bool finish[101] = {false};
    // bool visit[101] = {false};
    // for(int i = 1;i<=n;i++)
    // {
    //     for(int j = 1;j<=n;j++)visit[j] = false;      
    //     visit[i] = true;
    //     FindPath_find(i,visit,finish,n);
    // }
    FindPath2(n);
    for(int i = 1; i<=n;i++)
    {
        for(int j = 1; j<=n;j++)
        {
            cout << (FindPath_map[i][j] == 100000 ? 0 : 1) <<' ';
        }
        cout << '\n';
    }
    return 0;
}