//Palindromic Paths
//https://www.acmicpc.net/problem/10767
#include<iostream>
#include<queue>
#include<set>
#include<string>

using namespace std;

set<string> se[2][20][20];
set<string> res;

char arr[18][19];
int dr[2] = {0,1};
int dc[2] = {1,0};
int n;

bool isout(int r, int c){
    return r < 0 || c < 0 || r >= n || c >= n;
}

void dfs(int r, int c,int sr, int sc, string s,int flag){
    if(r == 0 && c == 0){
        se[0][sr][sc].insert(s); return;
    }
    else if(r == n-1 && c ==n -1){
        se[1][sr][sc].insert(s); return;
    }

    for(int d= 0 ; d < 2; d++){
        int nr = r + flag*dr[d];
        int nc = c + flag*dc[d];
        
        string str;

        if(isout(nr,nc)) continue; 
        dfs(nr,nc,sr,sc,s + arr[nr][nc], flag);
    } 
}

int Do()
{
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    for(int i = 0; i < n; i++){
        int j = n - 1 - i;
        dfs(i,j,i,j,"",1);
        dfs(i,j,i,j,"",-1);
        for(auto a : se[1][i][j]){
            if(se[0][i][j].find(a) != se[0][i][j].end()) res.insert(string(a.rbegin(),a.rend()) + arr[i][j] + a);
        }
    }

    cout << res.size();
    return 0;
}