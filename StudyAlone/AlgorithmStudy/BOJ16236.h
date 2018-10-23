#include <iostream>
#include <queue>
#define N 11
using namespace std;

struct DATA
{
    int x, y, cnt;
} d;
int map[N][N];
int n, Sz, Time_, start_X, start_Y; bool clear;

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
bool cmp(DATA u, DATA t)
{
    if (u.cnt < t.cnt)
    {
        return true;
    }
    else if (u.cnt == t.cnt)
    {
        if (u.x < t.x)
        {
            return true;
        }
        else if (u.x == t.x)
        {
            if (u.y < t.y)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
bool bfs(int x, int y)
{
    bool vist[N][N] = {
        false,
    };
    queue<DATA> q;
    d.x = x; 
    d.y = y;
    d.cnt = 0;
    q.push(d); 
    vector<DATA> v; int s = 0; 
    while (!q.empty())
    {    
        s++; 
        int sz = q.size();
        for (int a = 0; a < sz; a++)
        {
            int xx = q.front().x;
            int yy = q.front().y;
            int cnt1 = q.front().cnt;
            q.pop();
            vist[xx][yy] = true;
            for (int i = 0; i < 4; i++){
                int nx = xx+dx[i]; int ny = yy+dy[i]; 
                if(nx < 0 || nx >= n || ny < 0 ||ny>= n) continue; 

                if(map[nx][ny] < Sz && !vist[nx][ny] && map[nx][ny]){
                    vist[nx][ny] = true;
                    d.x = nx; d.y = ny; d.cnt = cnt1+1;  
                    v.push_back(d);
                    clear = true;  
                } 
                else if(map[nx][ny] == Sz && !vist[nx][ny]){
                    vist[nx][ny] = true; 
                    d.x = nx;
                    d.y = ny;
                    d.cnt = cnt1 + 1;
                    q.push(d); 
                }
                else if(!map[nx][ny] && !vist[nx][ny]){
                    vist[nx][ny] = true; 
                    d.x = nx;
                    d.y = ny;
                    d.cnt = cnt1 + 1;
                    q.push(d); 
                }
            }
        }
         if(v.size() > 0){
             break; 
         }
    }
    sort(v.begin(), v.end(), cmp);
     if(clear){
         start_X = v[0].x; start_Y = v[0].y;
         map[start_X][start_Y]= 0;  
         Time_ += s; 
         clear = false; 
         return true; 
     }
     else{
         return false; 
     }
}

int BOJ16236()
{
    cin >> n;   Sz =2; 
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == 9)
            {
                start_X = i;
                start_Y = j;
                map[i][j] = 0;
            }
        }
    }
    int fish = 0; 
    while(1){
        if(bfs(start_X, start_Y)){
            fish++; 
            if(fish == Sz){
                Sz+=1; fish= 0; 
            }
        }
        else{
            break; 
        }
    }
    cout << Time_ ;

    return 0;
}