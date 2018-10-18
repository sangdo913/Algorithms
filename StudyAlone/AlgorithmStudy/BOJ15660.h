#include<iostream>

using namespace std;

int arr[1000][1000];
bool check[1000][1000];
int blocks[19][3][2]={
    {{0,1},{0,2}, {0,3}},
    {{1,0}, {2,0}, {3,0}},
    {{0,1},{1,0},{1,1}},
    {{1,0},{2,0},{2,1}},
    { {1,0},{0,1},{0,2}},
    {{0,1},{1,1},{2,1}},
    {{1,0},{2,0},{2,-1}},
    { {1,0},{1,1},{1,2} },
    {{0,1},{1,0},{2,0}},
    {{1,0},{1,-1},{1,-2}},
    {{1,0},{2,0},{2,1}},
    {{1,0},{1,-1},{2-1}},
    {{0,1},{1,1},{1,2}},
    {{1,0},{1,1},{2,1}},
    {{0,1},{1,0},{1,-1}},
    {{-1,1},{0,1},{1,1}},
    {{-1,-1},{0,-1},{1,-1}},
    {{-1,-1},{-1,0},{-1,1}},
    { {1,-1},{1,0},{1,1} }
};

int MAX(int i1, int i2){return i1 < i2 ? i2 : i1;}

int canmake(int r, int c, int r2, int c2, int b1, int b2){
    check[r][c] = true;
    int res = 0;
    for(int i = 0; i < 3; i++){
        int d[2] = {blocks[b1][i][0], blocks[b1][i][1]};
        check[r + d[0]][c+d[1]] = true;
        res += arr[r+d[0]][c+d[1]];
    }
    res+= arr[r][c] + arr[r2][c2];

    bool ch = !check[r2][c2];
    
    for(int i = 0; i < 3; i++){
        int d[2] = {blocks[b2][i][0], blocks[b2][i][1]};
        ch &= !check[r2 + d[0]][c2 + d[1]];
        res += arr[r2+d[0]][c2+d[1]];
    }

    check[r][c] = false;
    for(int i = 0; i < 3; i++){
        int d[2] = {blocks[b1][i][0], blocks[b1][i][1]};
        check[r + d[0]][c+d[1]] = false;
    }

    return ch ? res : -1;
}

int BOJ15660(){
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n,m; 
    cin >> n >> m;

    for(int i = 0; i < 1000;i ++){
        for(int j = 0; j < 1000; j++)
            arr[i][j]  = -1000000;
    }
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++) cin >> arr[i+5][j+5];
    }
    
    int res = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            int j2 = j+1;
            for(int i2 = i; i2< n; i2++){
                for(; j2 < m; j2++){
                    for(int b1 = 0; b1< 19; b1++){
                        for(int b2 = 0; b2 < 19; b2++){
                            res =  MAX(res, canmake(5 + i, 5 + j, 5 + i2, 5 + j2,b1,b2 ));
                        }
                    }
                    int x = 0;
                }
                j2 = 0;
            }
        }
    }
    cout << res;
    return 0;
}