#include<iostream>

using namespace std;

char arr[500][501];
int n, m, dr[4] = {-1,1,0,0}, dc[4] = {0,0,-1,1};

int main(){
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    
    for(int i = 0; i < n; i++) cin >> arr[i];
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(arr[i][j] == 'S'){
          
                for(int d = 0; d < 4; d++){                    
                    int nr = i +dr[d], nc = j +dc[d];
                    if(nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
                    if(arr[nr][nc] == 'W'){
                        return!(cout << 0);
                    }
                    else if(arr[nr][nc] == '.') arr[nr][nc] = 'D';
                }
            }
        }
    }
    cout << 1 <<'\n';
    for(int i = 0; i < n; i++) cout <<arr[i] << '\n';
    return 0;
}
