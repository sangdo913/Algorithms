#include <string>
#include<iostream>
#include <vector>

using namespace std;
int chk[4][300][300];
int dr[4] = {-1,0,1,0};
int dc[4] = {0,1,0,-1};

bool isblock(vector<vector<int>> &maze, int r, int c){
    if(r < 0 || c < 0 || r == maze.size() || c == maze[0].size()) return true;
    if(maze[r][c] == 1) return true;
}

int solution(vector<vector<int>> maze) {
	int n = maze.size();
    int m = maze[0].size();
    int nowd = 2;
    if(maze[0][1] == 1){
        nowd = 2;
    }
    else nowd = 1;
    int r = 0, c = 0;
    int t = 0;
    int cnt = 0;
    while(true){
       // if(cnt++ == 10) break;
        cout << r << ' ' << c << ' ' << nowd << endl;
        if(r == n -1 && c == m-1) return t;
        int lr = r + dr[(3+nowd)%4];
        int lc = c + dc[(3+nowd)%4];
        int nr = r + dr[nowd];
        int nc = c + dc[nowd];
        
       if(!isblock(maze,lr,lc)){
           nowd = (nowd+3)%4;
           lr = r + dr[(3+nowd)%4];
           lc = c + dc[(3+nowd)%4];
           nr = r + dr[nowd];
           nc = c + dc[nowd];
       } 
       while(isblock(maze,nr,nc)){
           nowd = (nowd+1)%4;
           lr = r + dr[(3+nowd)%4];
           lc = c + dc[(3+nowd)%4];
           nr = r + dr[nowd];
           nc = c + dc[nowd];
       }
       r = nr, c = nc;
        ++t;
    }
    
    int answer = 0;
    return answer;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> mymap(n, vector<int>(m));
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j) cin >> mymap[i][j];
    }
    cout << solution(mymap) << endl;
    return 0;
}