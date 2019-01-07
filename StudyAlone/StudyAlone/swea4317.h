//Ä¨ »ý»ê
//https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWL21nCaM8wDFAUE
#include<iostream>

using namespace std;

int dp[30][1<<13];
int n, m, info[20][30];

bool check(int r, int c){
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            if(r + i > n || c + j > m) return false;
            if(info[r+i][c+j]) return false;
        }
    }
    return true;
}

void paint(int r, int c, int num){
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            info[r+i][c+j] = num;
        }
    }
}

int MAX(int a, int b){return a < b ? b : a;}

int func(int r, int c, int cnt){
    if(c == m+1){
        return cnt;
    }

    if(c > 1 && r == 1){
        int bit = 0;
        for(int i = 1; i <= n; i++){
            bit |= info[i][c] << i;
        }
        if(dp[c][bit] >= cnt) return 0;

        dp[c][bit] = cnt;
    }

    int np[2] = {r+1, c};
    if(np[0] == n+1){
        np[1]++;
        np[0] = 1;
    }
    
    int res = cnt;

    if(check(r,c)) {
        paint(r,c,1);
        res = MAX(res, func(np[0],np[1],cnt+1));
        paint(r,c,0);
    }

    res = MAX(res, func(np[0],np[1], cnt));

    return res;
}

int Do(){
    int tc;
    cin >> tc;
    for(int t = 1; t <= tc; t++){
        cin >> n >> m;
        for(int i = 1; i <= n+1; i++) for(int j = 1; j <= m+1; j++) {
            info[i][j] = 0;
        }

        for(int i = 0; i <= n+1; i++) for(int b = 0 ; b < (1 << (n+1)); b++) dp[i][b] = -1;
        
        for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) cin >> info[i][j];

        cout << '#' << t << ' ' << func(1,1,0) << '\n';
    }
    return 0;
}