#include<iostream>
using namespace std;

int n, m,k;
int stickers[100][10][10][4];
int R[100][4];
int C[100][4];

void rotate(int id){
    for(int d = 1; d < 4; ++d){
        int r = C[id][d-1];
        int c = R[id][d-1];
        for(int i = 0; i < r; ++i){
            for(int j = 0; j < c; ++j){
                stickers[id][i][j][d] = stickers[id][c-1-j][i][d-1];
            }
        }
        
        R[id][d] = r;
        C[id][d] = c;
    }
}

int mymap[40][40];
int main() {
    freopen("0Text.txt", "r", stdin);
    cin >> n >> m >> k;

    for(int id = 0; id < k; ++id){
        cin >> R[id][0] >> C[id][0];
        for(int i = 0; i < R[id][0]; ++i){
            for(int j = 0; j < C[id][0]; ++j){
                cin >> stickers[id][i][j][0];
            }
        }
        rotate(id);
    }
    int res = 0;
    for(int id = 0; id < k; ++id){
            for(int d = 0; d < 4; ++d){
        for(int i = 0; i < n; ++i){
            for(int j = 0;j < m; ++j){
                    int r = R[id][d];
                    int c = C[id][d];
                    for(int ii = 0; ii < r; ++ii){
                        for(int jj = 0; jj < c; ++jj){
                            int nr = ii + i, nc = jj + j;
                            if(stickers[id][ii][jj][d] == 0) continue;
                            if(ii + i >= n || jj + j >= m) goto FAIL;
                            if(mymap[nr][nc] == 1) goto FAIL;
                        }
                    }
                    for(int ii = 0; ii < r; ++ii){
                        for(int jj = 0; jj < c; ++jj){
                            int nr = ii + i, nc = jj + j;
                            if(stickers[id][ii][jj][d] == 1) mymap[nr][nc] = 1, res++;
                        }
                    }
                    goto NEXT;
                    FAIL:
                    int x = 1;
                }
            }
        }
        NEXT:
        int x = 1;
    }
    cout << res;
    return 0;
}