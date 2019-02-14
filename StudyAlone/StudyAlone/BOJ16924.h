#include<iostream>

using namespace std;
char arr[100][101];
bool check[100][100];
int n, m;

int dr[4] = {-1,1,0,0}, dc[4] = {0,0,-1,1};
int info[1000000][3];
int fr, re;

int Do(){
    cin >> n>> m;
    for(int i = 0 ; i < n; i++) cin >> arr[i];
    int res = 0;

    for(int i = 1; i < n-1; i++){
        for(int j = 1; j < m-1; j++){
            int len[4] = {};

            for(int d = 0; d  < 4; d++){
                int r = i, c = j;
                
                while(0 <= r && r < n && 0 <= c && c < m && arr[r][c] == '*'){
                    len[d]++;
                    r+= dr[d], c += dc[d];
                }
            }

            int l = 0x3f3f3f3f;
            
            for(int d = 0; d < 4; d++){
                l = l < len[d] ? l : len[d];
            }

            if(l <=1) continue;
            
            for(int d = 0; d  < 4; d++){
                int r = i, c = j;
                check[r][c] = true;
                
                for(int len = 1; len<l; len++){
                    r = i + dr[d]*len;
                    c = j + dc[d]*len;
                    check[r][c] = true;
                }
            }
            l--;

            while(l){
                info[re][0] = i+1, info[re][1] = j+1, info[re++][2] = l--;
            }
        }
    }

    bool canmake = true;

    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < m; j++){
            if(arr[i][j] == '*' && !check[i][j]) {
                canmake = false; break;
            }
        }
    }

    if(!canmake) return!(cout<<-1);
    else cout << re<<'\n';

    while(fr != re){
        cout << info[fr][0] << ' ' << info[fr][1] << ' ' << info[fr++][2] << '\n';
    }

    return 0;
}