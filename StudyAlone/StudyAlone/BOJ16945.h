#include<iostream>

using namespace std;

int table[8][3][2] = {
    {{0,0},{0,1},{0,2}},
    {{1,0},{1,1},{1,2}},
    {{2,0},{2,1},{2,2}},
    {{0,0},{1,0},{2,0}},
    {{0,1},{1,1},{2,1}},
    {{0,2},{1,2},{2,2}},
    {{0,0},{1,1},{2,2}},
    {{2,0},{1,1},{0,2}},
};
int arr[3][3], res = 10000;
int temp[3][3];

bool check(int x){
    bool chk[10] = {};
    for(int i = 0; i < 3; i++) for(int j = 0 ; j< 3; j++){
        if(chk[temp[i][j]]) return false;
        chk[temp[i][j]] = true;
    }
    
    for(int i = 0; i < 8; i++){
        int t = 0;
        for(int j = 0; j < 3; j++){
            int r = table[i][j][0];
            int c = table[i][j][1];
            t += temp[r][c];
        }
        if(x != t) return false;
    }
    return true;
}

#define ABS(x) ((x)> (0) ? (x) : -(x))

bool isvalid(int x){
    return 0 < x && x < 10;
}

void dfs(int r, int c){
    if(r == 2){
        for(int i = 1; i <= 9; i++) {
            temp[0][2] = i;
            int cmp = temp[0][0] + temp[0][1] + temp[0][2];
            temp[1][2] = cmp - temp[1][0] - temp[1][1];
            temp[2][0] = cmp - temp[0][0] - temp[1][0];
            temp[2][1] = cmp - temp[0][1] - temp[1][1];
            temp[2][2] = cmp - temp[2][0] - temp[2][1];

            if(isvalid(temp[1][2])&& isvalid(temp[2][0]) && isvalid(temp[2][1]) && isvalid(temp[2][2])){
                if(check(cmp)){
                    int x = 0;
                    for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) x += ABS(arr[i][j] - temp[i][j]);
                    res = res > x ? x : res;
                }
            } 
        }
        
        return;
    }
    int nr = r, nc = c +1;
    if(nc == 2) nr++ ,nc = 0;

    for(int i = 1; i < 10; i++) temp[r][c] = i, dfs(nr,nc);
}

int Do(){
    for(int i = 0; i<3; i++) for(int j = 0; j < 3; j++) cin >>arr[i][j];
    dfs(0,0);
    cout << res;
    return 0;
}